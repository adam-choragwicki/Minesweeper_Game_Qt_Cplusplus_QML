#pragma once

#include "model/minefield.h"

class FieldsUncoverer
{
public:
    FieldsUncoverer() = delete;

    static void uncoverAdjacentEmptyFields(const Field& field, Minefield& minefield);
    [[maybe_unused]] static void debug_UncoverAllFields(const Minefield& minefield);
};
