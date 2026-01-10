#include "minefield.h"
#include "tile.h"
#include "mines_generator.h"
#include "tiles_manager.h"
#include <ranges>
#include <QDebug>

Minefield::Minefield(const MinefieldParameters& minefieldParameters) : Minefield(minefieldParameters, MineCoordinatesGenerator::generateMinesCoordinates(minefieldParameters))
{}

Minefield::Minefield(const MinefieldParameters& minefieldParameters, const std::set<Coordinates>& minesCoordinates) : rowsCount_(minefieldParameters.getRowsCount()),
                                                                                                                      columnsCount_(minefieldParameters.getColumnsCount()),
                                                                                                                      minePercentage_(minefieldParameters.getMinePercentage())
{
    for (const auto& mineCoordinates: minesCoordinates)
    {
        Q_ASSERT(mineCoordinates.getRow() >= 1 && mineCoordinates.getRow() <= rowsCount_);
        Q_ASSERT(mineCoordinates.getColumn() >= 1 && mineCoordinates.getColumn() <= columnsCount_);
    }

    initializeTiles();
    placeMines(minesCoordinates);
    TilesManager::assignAdjacentMinesCountToAllTiles(*this);

    qInfo().noquote() << QString("Created %1 x %2 minefield (%3 tiles)").arg(rowsCount_).arg(columnsCount_).arg(rowsCount_ * columnsCount_);

    const int minesCount = getMinesCount();
    const double minePercentage = (static_cast<double>(minesCount) / static_cast<double>(coordinatesToTilesMapping_.size())) * 100.0;
    qInfo().noquote() << QString("Placed %1 mines (%2%)").arg(minesCount).arg(minePercentage);
}

void Minefield::reset()
{
    for (const auto& tile: coordinatesToTilesMapping_ | std::views::values)
    {
        tile->reset();
    }

    const auto minesCoordinates = MineCoordinatesGenerator::generateMinesCoordinates(MinefieldParameters(rowsCount_, columnsCount_, minePercentage_));
    placeMines(minesCoordinates);

    TilesManager::assignAdjacentMinesCountToAllTiles(*this);

    qInfo().noquote() << QString("Created %1 x %2 minefield (%3 tiles)").arg(rowsCount_).arg(columnsCount_).arg(rowsCount_ * columnsCount_);

    const int minesCount = getMinesCount();
    const double minePercentage = (static_cast<double>(minesCount) / static_cast<double>(coordinatesToTilesMapping_.size())) * 100.0;
    qInfo().noquote() << QString("Placed %1 mines (%2%)").arg(minesCount).arg(minePercentage);
}

void Minefield::initializeTiles()
{
    for (int row = 1; row <= rowsCount_; ++row)
    {
        for (int column = 1; column <= columnsCount_; ++column)
        {
            const Coordinates coordinates(row, column);
            addTile(coordinates);
        }
    }
}

const Tile& Minefield::getTileAt(const Coordinates& coordinates) const
{
    const auto it = coordinatesToTilesMapping_.find(coordinates);

    if (it == coordinatesToTilesMapping_.end())
    {
        throw std::runtime_error(QString("Error, cannot get tile at coordinates %1, because it is not on the minefield").arg(coordinates).toStdString());
    }

    return *it->second;
}

Tile& Minefield::getTileAt(const Coordinates& coordinates)
{
    return const_cast<Tile&>(std::as_const(*this).getTileAt(coordinates));
}

int Minefield::getMinesCount() const
{
    const int counter = std::ranges::count_if(coordinatesToTilesMapping_, [](const auto& tile) { return tile.second->isMinePresent(); });
    return counter;
}

void Minefield::addTile(const Coordinates& coordinates)
{
    const auto& [_, inserted] = coordinatesToTilesMapping_.insert_or_assign(coordinates, std::make_unique<Tile>(coordinates));

    if (!inserted)
    {
        qFatal() << "Error, tile with given coordinates is already on the minefield";
    }
}

void Minefield::placeMines(const std::set<Coordinates>& minesCoordinates)
{
    for (const auto& coordinates: minesCoordinates)
    {
        placeMine(coordinates);
    }
}

void Minefield::placeMine(const Coordinates& coordinates)
{
    auto& tile = getTileAt(coordinates);

    if (tile.isMinePresent())
    {
        throw std::runtime_error("Cannot place mine on a tile already containing mine");
    }

    tile.setMine();
}
