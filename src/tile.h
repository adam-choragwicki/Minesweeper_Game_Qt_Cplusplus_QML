#pragma once

#include "coordinates.h"
#include <QObject>

class Tile : public QObject
{
    Q_OBJECT

signals:
    void tileChanged(Tile& tile);

public:
    explicit Tile(const Coordinates& coordinates);
    void reset();

    [[nodiscard]] const Coordinates& getCoordinates() const { return coordinates_; }

    [[nodiscard]] std::optional<int> getAdjacentMineCount() const { return adjacentMineCount_; }

    void setAdjacentMineCount(const std::optional<int> adjacentMineCount) { adjacentMineCount_ = adjacentMineCount; }

    [[nodiscard]] bool isMinePresent() const { return mineIsPresent_; }

    enum class State
    {
        COVERED = 1, UNCOVERED = 2, FLAGGED = 3, MINE_EXPLODED = 4
    };

    Q_ENUM(State) // enables logging the state as string

    [[nodiscard]] const State& getState() const { return state_; };

    void setState(State newTileState);
    void setMine();

    void uncover(bool safe = false);

    [[nodiscard]] int getId() const { return id_; }

private:
    const Coordinates coordinates_;
    State state_;
    std::optional<int> adjacentMineCount_{};
    bool mineIsPresent_;

    inline static int instanceCounter_{};
    int id_{};
};
