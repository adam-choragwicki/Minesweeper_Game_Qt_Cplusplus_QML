#pragma once

#include "state_machine/abstract_state.h"

class ReadyToStartState : public AbstractState
{
public:
    explicit ReadyToStartState(IStateActions& stateActions) : AbstractState("ReadyToStartState", GameStateType::ReadyToStart, stateActions)
    {}

    void entered() override
    {
        qDebug() << "Entered state: ReadyToStart";
    }

    void exited() override
    {
        qDebug() << "Exited state: ReadyToStart";
    }

    void transitionTo(AbstractState* newState) override
    {
        switch (newState->type())
        {
            case GameStateType::Running:
                qInfo() << "========================= GAME STARTED =========================";
                break;

            case GameStateType::EscapeMenu:
                break;

            default:
                handleIllegalTransition(newState);
        }

        printTransition(newState);
    }

    void onKeyPress(const int key) override
    {
        constexpr bool logKeyPressed = false;

        if constexpr (logKeyPressed)
        {
            qDebug() << "ReadyToStartState::onKeyPress:" << key;
        }

        switch (key)
        {
            case Qt::Key_Escape:
                stateActions_.setGameState(GameStateType::EscapeMenu);
                break;

            default:
                break;
        }
    }
};
