#pragma once

#include "coordinates.h"
#include "common.h"

#include <QObject>

enum class FieldState
{
    COVERED, UNCOVERED, FLAGGED, MINE_EXPLODED
};

class Field : public QObject
{
Q_OBJECT

signals:
    void fieldStateUpdatedEvent(const Field& field);

public:
    explicit Field(const Coordinates& coordinates);

    [[nodiscard]] const Coordinates& getCoordinates() const
    { return coordinates_; }

    [[nodiscard]] std::optional<int> getAdjacentMineCount() const
    { return adjacentMineCount_; }

    void setAdjacentMineCount(std::optional<int> adjacentMineCount)
    { adjacentMineCount_ = adjacentMineCount; }

    [[nodiscard]] bool isMinePresent() const
    { return mineIsPresent_; }

    [[nodiscard]] const FieldState& getState() const
    { return fieldState_; };

    void setState(FieldState newFieldState);
    void setMine();
    void placeMine();
    void reset();
    void uncover(bool safe = false);

private:
    const Coordinates coordinates_;
    FieldState fieldState_;
    std::optional<int> adjacentMineCount_{};
    bool mineIsPresent_;
};
