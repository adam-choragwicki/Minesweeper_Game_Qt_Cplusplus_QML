#pragma once

#include "coordinates.h"
#include "field.h"
#include "common.h"
#include "minefield.h"
#include "fields_manager.h"
#include "mines_generator.h"
#include "fields_uncoverer.h"

class Model
{
public:
    void resizeMinefield(const MinefieldParameters& minefieldParameters);
    void reset();

    [[nodiscard]] const Minefield& getMinefield() const
    { return *minefield_; }

    [[nodiscard]] Minefield& getMinefield()
    { return *minefield_; }

private:
    std::unique_ptr<Minefield> minefield_;
};
