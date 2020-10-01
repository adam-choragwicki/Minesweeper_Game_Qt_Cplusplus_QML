#pragma once

#include "common.h"
#include "coordinates.h"

class Minefield
{
public:
    explicit Minefield(MinefieldParameters minefieldParameters);
    void resetFields();

    [[nodiscard]] const CoordinatesToFieldsMapping& getCoordinatesToFieldsMapping() const
    { return coordinatesToFieldsMapping_; }

    void setMine(const Coordinates& coordinates);

    [[nodiscard]] CoordinatesToFieldsMapping::const_iterator begin() const
    { return coordinatesToFieldsMapping_.cbegin(); }

    [[nodiscard]] CoordinatesToFieldsMapping::const_iterator end() const
    { return coordinatesToFieldsMapping_.cend(); }

    [[nodiscard]] const MinefieldParameters& getMinefieldParameters() const
    { return minefieldParameters_; }

private:
    void addField(const Coordinates& coordinates);

    CoordinatesToFieldsMapping coordinatesToFieldsMapping_;
    MinefieldParameters minefieldParameters_;
};
