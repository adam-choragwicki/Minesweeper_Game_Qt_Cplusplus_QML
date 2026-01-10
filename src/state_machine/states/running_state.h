#pragma once

#include "state_machine/abstract_state.h"

class RunningState : public AbstractState
{
public:
    explicit RunningState(IStateActions& stateActions) : AbstractState("RunningState", GameStateType::Running, stateActions)
    {}

    void entered() override
    {
        qDebug() << "Entered state: Running";
    }

    void exited() override
    {
        qDebug() << "Exited state: Running";
    }

    void transitionTo(AbstractState* newState) override
    {
        switch (newState->type())
        {
            case GameStateType::EscapeMenu:
            case GameStateType::EndedVictory:
            case GameStateType::EndedDefeat:
                break;

            default:
                handleIllegalTransition(newState);
        }

        printTransition(newState);
    }

    void onKeyPress(const int key) override
    {
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
