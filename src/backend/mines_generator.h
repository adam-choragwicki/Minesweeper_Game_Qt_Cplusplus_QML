#pragma once

#include "common.h"
#include "model/minefield.h"

class MineGenerator
{
public:
    MineGenerator() = delete;

    static void generateMines(const MinefieldParameters& gameParameters, const Minefield& minefield);
};
