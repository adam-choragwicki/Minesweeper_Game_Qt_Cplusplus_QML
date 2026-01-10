#pragma once

#include <QString>

class Coordinates
{
public:
    Coordinates(int row, int column);

    [[nodiscard]] int getRow() const { return row_; }
    [[nodiscard]] int getColumn() const { return column_; }

    operator QString() const;

private:
    int row_;
    int column_;
};

bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2);
bool operator==(const Coordinates& coordinates1, const Coordinates& coordinates2);
