#include "model/minefield.h"
#include "model/field.h"

Minefield::Minefield(MinefieldParameters minefieldParameters) : minefieldParameters_(minefieldParameters)
{
    for(int row = 1; row <= minefieldParameters.rowCount; ++row)
    {
        for(int column = 1; column <= minefieldParameters.columnCount; ++column)
        {
            const Coordinates coordinates(row, column);
            addField(coordinates);
        }
    }
}

void Minefield::resetFields()
{
    for(const auto&[coordinates, field] : coordinatesToFieldsMapping_)
    {
        field->reset();
    }
}

void Minefield::addField(const Coordinates& coordinates)
{
    const auto&[_, inserted] = coordinatesToFieldsMapping_.insert_or_assign(coordinates, std::make_unique<Field>(coordinates));

    if(!inserted)
    {
        throw std::runtime_error("Error, field with given coordinates is already on the minefield");
    }
}

void Minefield::setMine(const Coordinates& coordinates)
{
    coordinatesToFieldsMapping_.at(coordinates)->setMine();
}
