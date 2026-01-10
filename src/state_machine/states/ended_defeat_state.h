#pragma once

#include "state_machine/abstract_state.h"

class EndedDefeatState : public AbstractState
{
public:
    EndedDefeatState(IStateActions& stateActions) : AbstractState("EndedDefeatState", GameStateType::EndedDefeat, stateActions)
    {}

    void entered() override
    {
        qDebug() << "Entered state: EndedDefeat";
        stateActions_.showEndGameOverlay(GameResult::DEFEAT);
    }

    void exited() override
    {
        qDebug() << "Exited state: EndedDefeat";
        stateActions_.hideEndGameOverlay();
    }

    void transitionTo(AbstractState* newState) override
    {
        switch (newState->type())
        {
            case GameStateType::ReadyToStart:
                break;

            default:
                handleIllegalTransition(newState);
        }

        printTransition(newState);
    }
};
