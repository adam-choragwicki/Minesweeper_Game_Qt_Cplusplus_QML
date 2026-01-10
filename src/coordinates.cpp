#include "coordinates.h"
#include <QDebug>

Coordinates::Coordinates(const int row, const int column) : row_(row), column_(column)
{}

Coordinates::operator QString() const
{
    return "[row:" % QString::number(row_) % ", column:" % QString::number(column_) % "]";
}

bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    if (coordinates1.getRow() < coordinates2.getRow())
    {
        return true;
    }

    if (coordinates1.getRow() > coordinates2.getRow())
    {
        return false;
    }

    if (coordinates1.getColumn() < coordinates2.getColumn())
    {
        return true;
    }

    return false;
}

bool operator==(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    return (coordinates1.getRow() == coordinates2.getRow()) && (coordinates1.getColumn() == coordinates2.getColumn());
}
