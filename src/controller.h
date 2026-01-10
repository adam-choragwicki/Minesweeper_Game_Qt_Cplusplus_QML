#pragma once

#include "input_handler.h"
#include "window_manager.h"
#include "model/model.h"
#include "state_machine/game_state_manager.h"
#include "overlay_manager.h"
#include "qml_helper.h"
#include "game_coordinator.h"
#include <QQmlApplicationEngine>

class Controller : public QObject, public IStateActions
{
    Q_OBJECT

signals:
    void applicationShutdownRequested();
    void gameStateChanged();

public slots:
    void onQmlEngineFullyInitialized();
    void onTileLeftClicked(int row, int column);
    void onTileRightClicked(int row, int column);
    void processKeyPress(int key);
    void onResumeClicked();
    void onRestartClicked();
    void onQuitClicked();
    void onPlayAgainClicked();
    void onChangeGameParametersClicked();

public:
    Controller(Model& model, QQmlApplicationEngine& view);

    // IStateActions implementation
    void showEscapeMenuOverlay() override;
    void hideEscapeMenuOverlay() override;
    void showEndGameOverlay(GameResult gameResult) override;
    void hideEndGameOverlay() override;

    void setGameState(GameStateType newGameState) override;
    void restorePreviousState() override;

    [[nodiscard]] GameStateManager& getStateManager() { return gameStateManager_; }

    Q_PROPERTY(bool gameRunning READ isGameRunning NOTIFY gameStateChanged)
    bool isGameRunning() const { return gameStateManager_.getCurrentGameStateType() == GameStateType::Running; }

    Q_INVOKABLE QString tileStateToString(int pieceState) const;

    Q_INVOKABLE void resizeGame(int rows, int columns, int minePercentage);

    [[nodiscard]] bool isStartInFullScreenEnabled() const { return windowManager_.isStartInFullScreenEnabled(); }
    Q_PROPERTY(bool startInFullScreenEnabled READ isStartInFullScreenEnabled CONSTANT)

private:
    Model& model_;
    QQmlApplicationEngine& view_;

    QmlHelper qmlHelper_{view_};
    GameStateManager gameStateManager_;
    WindowManager windowManager_;
    std::unique_ptr<OverlayManager> overlayManager_;
    std::unique_ptr<InputHandler> inputHandler_;
    std::unique_ptr<GameCoordinator> gameCoordinator_;

    SoundPlayer soundPlayer_;
};
