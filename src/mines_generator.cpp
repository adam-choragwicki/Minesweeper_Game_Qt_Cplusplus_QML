#include "mines_generator.h"
#include <algorithm>
#include <QRandomGenerator>

std::set<Coordinates> MineCoordinatesGenerator::generateMinesCoordinates(const MinefieldParameters& minefieldParameters) {
    const int rowsCount = minefieldParameters.getRowsCount();
    const int columnsCount = minefieldParameters.getColumnsCount();
    const int totalTilesCount = rowsCount * columnsCount;

    const int targetMinesCount = static_cast<size_t>(totalTilesCount * (static_cast<double>(minefieldParameters.getMinePercentage()) / 100.0));

    Q_ASSERT(targetMinesCount >= 0);
    Q_ASSERT(targetMinesCount <= totalTilesCount);

    // 1. Generate all possible coordinates
    std::vector<Coordinates> allPossibleCoordinates;
    allPossibleCoordinates.reserve(totalTilesCount);

    for (int row = 1; row <= rowsCount; ++row)
    {
        for (int col = 1; col <= columnsCount; ++col)
        {
            allPossibleCoordinates.emplace_back(row, col);
        }
    }

    // 2. Shuffle
    auto* rng = QRandomGenerator::global();
    std::ranges::shuffle(allPossibleCoordinates, *rng);

    // 3. Take first N
    std::set<Coordinates> result;
    for (int i = 0; i < targetMinesCount; ++i)
    {
        result.insert(allPossibleCoordinates[i]);
    }

    return result;
}
