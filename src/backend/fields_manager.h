#pragma once

#include "common.h"
#include "model/minefield.h"

class FieldsManager
{
public:
    FieldsManager() = delete;

    static void assignAdjacentMinesCountToAllFields(const Minefield& minefield);
    [[nodiscard]] static std::vector<Field*> getAdjacentFields(const Coordinates& coordinates, const Minefield& minefield);
    [[nodiscard]] static int countRemainingCoveredFieldsWithoutMine(const Minefield& minefield);

private:
    [[nodiscard]] static std::vector<Coordinates> generateAdjacentFieldsCoordinates(const Coordinates& coordinates);

    inline static const std::vector<std::pair<int, int>> DIRECTIONAL_OFFSETS = {{-1, -1},
                                                                                {-1, 0},
                                                                                {-1, +1},
                                                                                {0,  -1},
                                                                                {0,  +1},
                                                                                {+1, -1},
                                                                                {+1, 0},
                                                                                {+1, +1}};
};
