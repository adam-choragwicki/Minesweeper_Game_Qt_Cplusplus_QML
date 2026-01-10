#include "tiles_manager.h"
#include "tile.h"
#include "coordinates_validator.h"
#include <ranges>

void TilesManager::assignAdjacentMinesCountToAllTiles(const Minefield& minefield)
{
    const int rowsCount = minefield.getRowsCount();
    const int columnsCount = minefield.getColumnsCount();
    const CoordinatesValidator validator(rowsCount, columnsCount);

    for (const auto& tile: minefield | std::views::values)
    {
        if (tile->isMinePresent())
        {
            tile->setAdjacentMineCount(std::nullopt);
            continue;
        }

        const Coordinates tileCoordinates = tile->getCoordinates();
        int adjacentMineCount = 0;

        for (const auto& offset: DIRECTIONAL_OFFSETS)
        {
            const int row = tileCoordinates.getRow() + offset.first;
            const int column = tileCoordinates.getColumn() + offset.second;

            if (!validator.validateCoordinates(row, column))
            {
                continue;
            }

            const Tile& otherTile = minefield.getTileAt(Coordinates(row, column));

            if (otherTile.isMinePresent())
            {
                ++adjacentMineCount;
            }
        }

        tile->setAdjacentMineCount(adjacentMineCount);
    }
}

std::vector<Tile*> TilesManager::getAdjacentTiles(const Coordinates& coordinates, Minefield& minefield)
{
    const int rowsCount = minefield.getRowsCount();
    const int columnsCount = minefield.getColumnsCount();
    const CoordinatesValidator validator(rowsCount, columnsCount);

    std::vector<Tile*> result;
    result.reserve(8);

    const int baseTileRow = coordinates.getRow();
    const int baseTileColumn = coordinates.getColumn();

    for (const auto& offset: DIRECTIONAL_OFFSETS)
    {
        const int candidateRow = baseTileRow + offset.first;
        const int candidateColumn = baseTileColumn + offset.second;

        if (!validator.validateCoordinates(candidateRow, candidateColumn))
        {
            continue;
        }

        result.push_back(&minefield.getTileAt(Coordinates(candidateRow, candidateColumn)));
    }

    return result;
}

int TilesManager::countRemainingCoveredTilesWithoutMine(const Minefield& minefield)
{
    int counter = 0;

    for (const auto& tile: minefield | std::views::values)
    {
        if (tile->getState() != Tile::State::UNCOVERED && !tile->isMinePresent()) ++counter;
    }

    return counter;
}

std::vector<Coordinates> TilesManager::generateAdjacentTilesCoordinates(const int rowsCount, const int columnsCount, const Coordinates& coordinates)
{
    std::vector<Coordinates> adjacentTilesCoordinates;

    const CoordinatesValidator coordinatesValidator(rowsCount, columnsCount);

    for (const auto& [rowOffset, columnOffset]: DIRECTIONAL_OFFSETS)
    {
        const int adjacentRow = coordinates.getRow() + rowOffset;
        const int adjacentColumn = coordinates.getColumn() + columnOffset;

        if (coordinatesValidator.validateCoordinates(adjacentRow, adjacentColumn))
        {
            adjacentTilesCoordinates.emplace_back(adjacentRow, adjacentColumn);
        }
    }

    return adjacentTilesCoordinates;
}
