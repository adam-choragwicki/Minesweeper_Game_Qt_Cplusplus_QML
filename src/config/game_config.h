#pragma once

#include "minefield_parameters.h"
#include <QVariantList>
#include <array>

class GameConfig : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantList rowsCountOptions READ getRowsCountOptions CONSTANT)
    Q_PROPERTY(QVariantList columnsCountOptions READ getColumnsCountOptions CONSTANT)
    Q_PROPERTY(QVariantList minePercentageOptions READ minePercentageOptions CONSTANT)

public:
    explicit GameConfig(QObject* parent = nullptr) : QObject(parent) {}

    QVariantList getRowsCountOptions() const { return toVariantList(rowsCountOptions_); }
    QVariantList getColumnsCountOptions() const { return toVariantList(columnsCountOptions_); }
    QVariantList minePercentageOptions() const { return toVariantList(minePercentageOptions_); }

    const MinefieldParameters& getInitialMinefieldParameters() const { return initialMinefieldParameters_; }

private:
    static QVariantList toVariantList(const std::array<int, 7>& values)
    {
        QVariantList list;

        for (const int value: values)
        {
            list.append(value);
        }

        return list;
    }

    const std::array<int, 7> rowsCountOptions_{10, 15, 20, 25, 30, 35, 40};
    const std::array<int, 7> columnsCountOptions_{10, 15, 20, 25, 30, 35, 40};
    const std::array<int, 7> minePercentageOptions_{10, 15, 20, 25, 30, 35, 40};

    MinefieldParameters initialMinefieldParameters_{25, 25, 10};
};
