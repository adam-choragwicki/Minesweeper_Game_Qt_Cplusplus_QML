#pragma once

#include "tile.h"
#include "minefield.h"

class TilesUncoverer
{
public:
    TilesUncoverer() = delete;

    static void uncoverAdjacentEmptyTiles(Tile& start, Minefield& field);
    [[maybe_unused]] static void debug_UncoverAllTiles(const Minefield& minefield);
};
