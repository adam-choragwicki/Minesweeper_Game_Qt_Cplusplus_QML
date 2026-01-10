#include "tile.h"
#include "tile_state_manager.h"

Tile::Tile(const Coordinates& coordinates) : coordinates_(coordinates)
{
    state_ = State::COVERED;
    mineIsPresent_ = false;

    id_ = instanceCounter_++;
}

void Tile::reset()
{
    // qDebug() << "Resetting tile" << id_;
    state_ = State::COVERED;
    mineIsPresent_ = false;
    adjacentMineCount_ = std::nullopt;

    emit tileChanged(*this);
}

void Tile::uncover(bool safe)
{
    // qDebug() << "Uncovering tile: " << coordinates_;

    if (mineIsPresent_)
    {
        qInfo() << "Mine exploded!: " << coordinates_;
        setState(State::MINE_EXPLODED);
    }
    else
    {
        // qDebug() << "No mine here";
        setState(State::UNCOVERED);
    }
}

void Tile::setMine()
{
    if (mineIsPresent_)
    {
        // defensive programming, it should have already been checked at this point
        throw std::runtime_error("Cannot place mine on a tile already containing mine");
    }

    mineIsPresent_ = true;
}

void Tile::setState(const State newTileState)
{
    TileStateManager::validateTransition(state_, newTileState);
    state_ = newTileState;
    emit tileChanged(*this);
}
