#pragma once

#include <QDebug>

enum class GameStateType
{
    Initialization, // App just started — loading assets, creating game board, placing mines etc.
    ReadyToStart, // Everything ready, waiting for the player's input to start.
    Running, // Game loop active.
    EscapeMenu, // Escape menu overlay is displayed.
    EndedVictory, // Game stopped because all empty tiles have been uncovered. The end game overlay is displayed.
    EndedDefeat, // Game stopped because a tile with mine has been uncovered. The end game overlay is displayed.
};

inline QDebug operator<<(QDebug debug, const GameStateType state)
{
    QDebugStateSaver saver(debug);
    debug.nospace();

    switch (state)
    {
        case GameStateType::Initialization: return debug << "Initialization";
        case GameStateType::ReadyToStart: return debug << "ReadyToStart";
        case GameStateType::Running: return debug << "Running";
        case GameStateType::EscapeMenu: return debug << "EscapeMenu";
        case GameStateType::EndedVictory: return debug << "EndedVictory";
        case GameStateType::EndedDefeat: return debug << "EndedDefeat";

        default:
            qFatal() << "Unknown game state";
    }
}
