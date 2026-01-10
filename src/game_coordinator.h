#pragma once

#include "model/model.h"
#include "qml_helper.h"
#include "state_machine/game_state_manager.h"
#include "game_result.h"
#include "sound_player.h"

class GameCoordinator : public QObject
{
    Q_OBJECT

public:
    explicit GameCoordinator(Model& model, QmlHelper& qmlHelper, IStateActions& stateActions, SoundPlayer& soundPlayer);

    void startGame();
    void restartGameWithSameGameParameters();
    void restartGameWithNewGameParameters(int rows, int columns, int minePercentage);
    void processTileClicked(Qt::MouseButton button, const Coordinates& tileCoordinates);

    [[nodiscard]] bool isEndGameCinematicInProgress() const { return endGameCinematicInProgress_; }

private:
    void endGame(GameResult gameResult);
    void finalizeGameRestart();
    void scheduleShockwaveMineExplosion(const Coordinates& shockwaveOrigin, GameResult gameResult);

    Model& model_;
    QmlHelper& qmlHelper_;
    IStateActions& stateActions_;
    SoundPlayer& soundPlayer_;

    bool endGameCinematicInProgress_{};
};
