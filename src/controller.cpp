#include "controller.h"
#include <QQmlContext>

Controller::Controller(Model& model, QQmlApplicationEngine& view) : model_(model), view_(view), gameStateManager_(*this)
{
    qInfo() << "Initializing controller";

    inputHandler_ = std::make_unique<InputHandler>(*this, windowManager_);

    connect(&gameStateManager_, &GameStateManager::gameStateChanged, this, &Controller::gameStateChanged, Qt::UniqueConnection);
}

void Controller::onQmlEngineFullyInitialized()
{
    qDebug() << "QML engine fully initialized";

    windowManager_.setWindow(qmlHelper_.getMainWindow());
    overlayManager_ = std::make_unique<OverlayManager>(qmlHelper_);

    gameCoordinator_ = std::make_unique<GameCoordinator>(model_, qmlHelper_, *this, soundPlayer_);

    gameCoordinator_->startGame();
}

void Controller::onTileLeftClicked(const int row, const int column)
{
    const Coordinates clickedTileCoordinates(row, column);

    qDebug().noquote() << "C++: Tile clicked:" << clickedTileCoordinates;
    gameCoordinator_->processTileClicked(Qt::MouseButton::LeftButton, clickedTileCoordinates);
}

void Controller::onTileRightClicked(const int row, const int column)
{
    const Coordinates clickedTileCoordinates(row, column);

    qDebug().noquote() << "C++: Tile clicked:" << clickedTileCoordinates;
    gameCoordinator_->processTileClicked(Qt::MouseButton::RightButton, clickedTileCoordinates);
}

void Controller::showEscapeMenuOverlay()
{
    overlayManager_->showEscapeMenuOverlay();
}

void Controller::hideEscapeMenuOverlay()
{
    overlayManager_->hideEscapeMenuOverlay();
}

void Controller::showEndGameOverlay(GameResult gameResult)
{
    overlayManager_->showEndGameOverlay(gameResult);
}

void Controller::hideEndGameOverlay()
{
    overlayManager_->hideEndGameOverlay();
}

void Controller::setGameState(const GameStateType newGameState)
{
    gameStateManager_.setGameState(newGameState);
}

void Controller::restorePreviousState()
{
    gameStateManager_.restorePreviousGameState();
}

QString Controller::tileStateToString(const int pieceState) const
{
    const QMetaEnum metaEnum = QMetaEnum::fromType<Tile::State>();

    if (const char* key = metaEnum.valueToKey(pieceState))
    {
        return QString(key);
    }

    qFatal() << "Unknown tile state: " << pieceState;
    return "NULL";
}

void Controller::resizeGame(const int rows, const int columns, const int minePercentage)
{
    gameCoordinator_->restartGameWithNewGameParameters(rows, columns, minePercentage);
}

void Controller::processKeyPress(const int key)
{
    // qDebug() << "Key pressed:" << key;

    if (gameCoordinator_->isEndGameCinematicInProgress())
    {
        return;
    }

    inputHandler_->processKeyPress(key);
}

void Controller::onResumeClicked()
{
    qInfo() << "Resume button clicked";
    soundPlayer_.playMenuClick();
    gameStateManager_.restorePreviousGameState();
}

void Controller::onRestartClicked()
{
    qInfo() << "Restart button clicked";
    soundPlayer_.playMenuClick();
    gameCoordinator_->restartGameWithSameGameParameters();
}

void Controller::onQuitClicked()
{
    qInfo() << "Quit button clicked";
    soundPlayer_.playMenuClick();
    emit applicationShutdownRequested();
}

void Controller::onPlayAgainClicked()
{
    soundPlayer_.playMenuClick();
    gameCoordinator_->restartGameWithSameGameParameters();
}

void Controller::onChangeGameParametersClicked()
{
    soundPlayer_.playMenuClick();
    qDebug() << "Change game parameters button clicked";
}
