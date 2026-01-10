#pragma once

class MinefieldParameters
{
public:
    MinefieldParameters(const int rowsCount, const int columnsCount, const int minePercentage)
        : rowsCount_(rowsCount), columnsCount_(columnsCount), minePercentage_(minePercentage)
    {}

    [[nodiscard]] int getRowsCount() const { return rowsCount_; }
    [[nodiscard]] int getColumnsCount() const { return columnsCount_; }
    [[nodiscard]] int getMinePercentage() const { return minePercentage_; }

private:
    const int rowsCount_;
    const int columnsCount_;
    const int minePercentage_;
};
