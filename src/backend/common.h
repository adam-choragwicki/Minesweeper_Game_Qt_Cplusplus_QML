#pragma once

#include <map>
#include <memory>
#include <vector>

class Coordinates;

class Field;

using CoordinatesToFieldsMapping = std::map<Coordinates, std::unique_ptr<Field>>;

enum class GameResult
{
    WIN, LOSE
};

struct MinefieldParameters
{
    MinefieldParameters() = default;

    MinefieldParameters(int rowCount, int columnCount, int minePercentage) : rowCount(rowCount), columnCount(columnCount), minePercentage(minePercentage)
    {}

    int rowCount{};
    int columnCount{};
    int minePercentage{};
};

namespace GameParametersLimits
{
    const int MIN_ROW_COUNT = 10;
    const int MAX_ROW_COUNT = 30;
    const int MIN_COLUMN_COUNT = 10;
    const int MAX_COLUMN_COUNT = 30;

    const std::vector<int> MINE_PERCENTAGE_OPTIONS{10, 20, 30};
}
