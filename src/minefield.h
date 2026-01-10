#pragma once

#include "config/minefield_parameters.h"
#include "coordinates.h"
#include "tile.h"
#include <map>
#include <set>

class Minefield
{
    using CoordinatesToTilesMapping = std::map<Coordinates, std::unique_ptr<Tile>>;

public:
    explicit Minefield(const MinefieldParameters& minefieldParameters);
    Minefield(const MinefieldParameters& minefieldParameters, const std::set<Coordinates>& minesCoordinates); // public for testing purposes

    void reset();

    void placeMine(const Coordinates& coordinates);

    [[nodiscard]] CoordinatesToTilesMapping::const_iterator begin() const { return coordinatesToTilesMapping_.cbegin(); }
    [[nodiscard]] CoordinatesToTilesMapping::const_iterator end() const { return coordinatesToTilesMapping_.cend(); }

    [[nodiscard]] const Tile& getTileAt(const Coordinates& coordinates) const;
    Tile& getTileAt(const Coordinates& coordinates);

    [[nodiscard]] int getRowsCount() const { return rowsCount_; }
    [[nodiscard]] int getColumnsCount() const { return columnsCount_; }

    [[nodiscard]] int getMinesCount() const;

private:
    void initializeTiles();
    void addTile(const Coordinates& coordinates);
    void placeMines(const std::set<Coordinates>& minesCoordinates);

    CoordinatesToTilesMapping coordinatesToTilesMapping_;

    const int rowsCount_;
    const int columnsCount_;
    const int minePercentage_;
};
