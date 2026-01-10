#pragma once

class CoordinatesValidator
{
public:
    CoordinatesValidator(const int rowsCount, const int columnsCount) : rowsCount_(rowsCount), columnsCount_(columnsCount)
    {}

    bool validateCoordinates(const int row, const int column) const
    {
        return row >= 1 && row <= rowsCount_ && column >= 1 && column <= columnsCount_;
    }

    bool validateCoordinates(const Coordinates& coordinates) const
    {
        return validateCoordinates(coordinates.getRow(), coordinates.getColumn());
    }

private:
    const int rowsCount_;
    const int columnsCount_;
};
