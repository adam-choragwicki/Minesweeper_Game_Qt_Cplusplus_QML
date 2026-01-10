#pragma once

#include "tile.h"
#include <stdexcept>
#include <QMetaEnum>

class TileStateManager
{
public:
    static void validateTransition(const Tile::State currentTileState, const Tile::State newTileState)
    {
        using State = Tile::State;
        auto handleIllegalTransition = [](State currentState, State newState)
        {
            const QString message = QString("Illegal tile state transition from %1 to %2")
                    .arg(QMetaEnum::fromType<State>().valueToKey(static_cast<int>(currentState)))
                    .arg(QMetaEnum::fromType<State>().valueToKey(static_cast<int>(newState)));
            throw std::runtime_error(message.toStdString());
        };

        if (currentTileState == State::COVERED)
        {
            if (newTileState == State::COVERED)
            {
                handleIllegalTransition(currentTileState, newTileState);
            }

            // transition to other states allowed
        }
        else if (currentTileState == State::UNCOVERED)
        {
            // no transitions allowed
            handleIllegalTransition(currentTileState, newTileState);
        }
        else if (currentTileState == State::FLAGGED)
        {
            if (newTileState == State::COVERED)
            {
                return;
            }

            if (newTileState == State::UNCOVERED)
            {
                return; // permitted only during uncovering adjacent empty tiles
            }

            if (newTileState == State::MINE_EXPLODED)
            {
                return; // this happens during the end game shockwave
            }

            handleIllegalTransition(currentTileState, newTileState);
        }
        else if (currentTileState == State::MINE_EXPLODED)
        {
            // no transitions allowed
            handleIllegalTransition(currentTileState, newTileState);
        }
        else
        {
            throw std::runtime_error("Unsupported tile state");
        }
    }
};
