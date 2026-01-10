#pragma once

#include "minefield.h"

class TilesManager
{
public:
    static void assignAdjacentMinesCountToAllTiles(const Minefield& minefield);

    [[nodiscard]] static std::vector<Tile*> getAdjacentTiles(const Coordinates& coordinates, Minefield& minefield);

    [[nodiscard]] static int countRemainingCoveredTilesWithoutMine(const Minefield& minefield);

private:
    [[nodiscard]] static std::vector<Coordinates> generateAdjacentTilesCoordinates(int rowsCount, int columnsCount, const Coordinates& coordinates);

    static constexpr std::array<std::pair<int, int>, 8> DIRECTIONAL_OFFSETS =
    {
        std::make_pair(-1, -1),
        std::make_pair(-1, 0),
        std::make_pair(-1, +1),

        std::make_pair(0, -1),
        std::make_pair(0, +1),

        std::make_pair(+1, -1),
        std::make_pair(+1, 0),
        std::make_pair(+1, +1)
    };
};
