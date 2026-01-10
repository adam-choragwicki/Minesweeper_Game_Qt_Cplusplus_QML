#pragma once

#include "config/minefield_parameters.h"
#include "coordinates.h"
#include <set>

class MineCoordinatesGenerator
{
public:
    MineCoordinatesGenerator() = delete;

    static std::set<Coordinates> generateMinesCoordinates(const MinefieldParameters& minefieldParameters);
};
