#include "game_coordinator.h"
#include "tiles_manager.h"
#include "tiles_uncoverer.h"
#include <QTimer>
#include <ranges>

GameCoordinator::GameCoordinator(Model& model, QmlHelper& qmlHelper, IStateActions& stateActions, SoundPlayer& soundPlayer) : model_(model),
                                                                                                                              qmlHelper_(qmlHelper),
                                                                                                                              stateActions_(stateActions),
                                                                                                                              soundPlayer_(soundPlayer)
{
    stateActions_.setGameState(GameStateType::ReadyToStart);
}

void GameCoordinator::startGame()
{
    stateActions_.setGameState(GameStateType::Running);
}

void GameCoordinator::restartGameWithSameGameParameters()
{
    qInfo() << "Restarting game with same game parameters";
    model_.resetMinefield();

    finalizeGameRestart();
}

void GameCoordinator::restartGameWithNewGameParameters(const int rows, const int columns, const int minePercentage)
{
    qInfo() << "Restarting game with new game parameters: rows = " << rows << ", columns = " << columns << ", minePercentage = " << minePercentage;

    const MinefieldParameters minefieldParameters(rows, columns, minePercentage);
    model_.generateNewMinefield(minefieldParameters);

    finalizeGameRestart();
}

void GameCoordinator::finalizeGameRestart()
{
    stateActions_.setGameState(GameStateType::ReadyToStart);
    startGame();
}

void GameCoordinator::processTileClicked(const Qt::MouseButton button, const Coordinates& tileCoordinates)
{
    qDebug().noquote() << QString("Processing tile clicked: %1").arg(tileCoordinates);

    if (endGameCinematicInProgress_)
    {
        qDebug() << "Ignoring tile click because end-game cinematic is in progress";
        return;
    }

    Tile& tile = model_.getMinefield().getTileAt(tileCoordinates);

    if (button == Qt::MouseButton::LeftButton)
    {
        if (tile.getState() == Tile::State::COVERED)
        {
            if (tile.isMinePresent())
            {
                soundPlayer_.playMine();
                tile.setState(Tile::State::MINE_EXPLODED);
                scheduleShockwaveMineExplosion(tileCoordinates, GameResult::DEFEAT);
            }
            else
            {
                soundPlayer_.playUncoverTile();
                tile.uncover();

                if (tile.getAdjacentMineCount() == 0)
                {
                    // Only call flood-fill if the clicked tile has zero adjacent mines
                    TilesUncoverer::uncoverAdjacentEmptyTiles(tile, model_.getMinefield());
                }
            }

            if (TilesManager::countRemainingCoveredTilesWithoutMine(model_.getMinefield()) == 0)
            {
                endGame(GameResult::VICTORY);
            }
        }
    }
    else if (button == Qt::MouseButton::RightButton)
    {
        if (tile.getState() == Tile::State::COVERED)
        {
            soundPlayer_.playFlagPlace();
            tile.setState(Tile::State::FLAGGED);
        }
        else if (tile.getState() == Tile::State::FLAGGED)
        {
            soundPlayer_.playFlagPlace();
            tile.setState(Tile::State::COVERED);
        }
    }
}

void GameCoordinator::scheduleShockwaveMineExplosion(const Coordinates& shockwaveOrigin, const GameResult gameResult)
{
    // Delay between explosion "rings" (batch interval)
    constexpr int ringDelayMs = 100;

    endGameCinematicInProgress_ = true;

    Minefield& minefield = model_.getMinefield();

    // Group mines by Chebyshev distance (ring index). Each ring will be exploded together.
    // minesByRing[ring] -> vector of Tile* in that ring
    std::map<int, std::vector<Tile*>> minesByRing; // group mines by distance ring

    for (const auto& tile: minefield | std::views::values)
    {
        if (!tile->isMinePresent())
        {
            continue;
        }

        const Coordinates& tileCoordinates = tile->getCoordinates();

        // Chebyshev distance (max of row and column delta) gives square-ish shockwave rings
        const int ring = std::max(
            std::abs(tileCoordinates.getRow() - shockwaveOrigin.getRow()),
            std::abs(tileCoordinates.getColumn() - shockwaveOrigin.getColumn()));

        minesByRing[ring].push_back(tile.get());
    }

    // Transform the map into an ordered vector of batches (each batch is one ring). This is easier to index with an integer batch counter when driving the QTimer.
    const auto explosionBatches = std::make_shared<std::vector<std::vector<Tile*>>>();

    for (auto& tiles: minesByRing | std::views::values)
    {
        explosionBatches->push_back(tiles);
    }

    // currentBatchIndex tracks which batch (ring) we are about to explode.
    // We allocate it on the heap (shared_ptr) because the lambda connected to the QTimer will outlive the local scope of this function. Using a shared_ptr<int> keeps the
    // integer alive and shared between the caller and the lambda safely.
    //
    // Capturing a raw int by reference into a lambda that is invoked asynchronously would be unsafe (dangling reference). Capturing a local int by value would not be mutable
    // across timer ticks. Using a shared_ptr gives us a mutable, heap-backed counter that is lifetime-extended for as long as the lambda holds a copy.
    const auto currentBatchIndex = std::make_shared<int>(0);

    // Create a QTimer to drive batches. I use QPointer to help static analyzers understand that the pointer is Qt-parented and not an actual leak.
    // The timer is parented to 'this' (GameCoordinator) so Qt will delete it when the parent is destroyed.
    //
    // Note: QPointer is non-owning; Qt ownership is still given to the parent. Using QPointer typically quiets memory leak warnings because it shows the pointer is
    // managed (and can become null if the QObject is deleted).
    const QPointer timer = new QTimer(this);
    timer->setInterval(ringDelayMs);

    // Connect timer -> lambda. The lambda captures copies of:
    //  - explosionBatches (shared_ptr) to keep the batch data alive
    //  - currentBatchIndex (shared_ptr) to keep and update the batch counter
    //  - timer (QPointer) so it can be stopped and deleted safely
    connect(timer, &QTimer::timeout, this, [=, this]()
    {
        // If we've processed all batches, stop and schedule endGame.
        if (*currentBatchIndex >= static_cast<int>(explosionBatches->size()))
        {
            if (timer)
            {
                timer->stop();
                // deleteLater is safe even if the parent deletes it; calling it ensures timely cleanup
                timer->deleteLater();
            }

            constexpr int showEndGameOverlayDelayMs = 300;

            // Give a small pause after the last ring before showing overlay
            QTimer::singleShot(showEndGameOverlayDelayMs, this, [this, gameResult]()
            {
                endGame(gameResult);
                endGameCinematicInProgress_ = false;
            });

            return;
        }

        // Play a sound for this batch. Volume attenuates with the batch index (closer rings louder).
        // Clamp volume: ensure it stays within a reasonable audible range.
        const double volume = std::clamp(1.0 - (*currentBatchIndex * 0.25), 0.1, 1.0);
        soundPlayer_.playMine(volume);

        // Explode every mine in the current batch.
        for (Tile* tile: (*explosionBatches)[*currentBatchIndex])
        {
            if (tile->getState() != Tile::State::MINE_EXPLODED)
            {
                tile->setState(Tile::State::MINE_EXPLODED);
            }
        }

        // Move to the next batch (next ring)
        ++*currentBatchIndex;
    });

    // Start the repeating timer to drive ring-by-ring explosions.
    timer->start();
}

void GameCoordinator::endGame(const GameResult gameResult)
{
    if (gameResult == GameResult::VICTORY)
    {
        qDebug() << "Game over, result: Victory";
        stateActions_.setGameState(GameStateType::EndedVictory);
    }
    else if (gameResult == GameResult::DEFEAT)
    {
        qDebug() << "Game over, result: Defeat";
        stateActions_.setGameState(GameStateType::EndedDefeat);
    }
    else
    {
        Q_UNREACHABLE();
    }
}
