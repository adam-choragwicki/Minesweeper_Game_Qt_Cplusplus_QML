#pragma once

#include "minefield.h"
#include "tiles_model.h"
#include "config/minefield_parameters.h"
#include "config/game_config.h"

class Model : public QObject
{
    Q_OBJECT

signals:
    void boardSizeChanged(int rows, int columns);

public:
    explicit Model(const GameConfig& gameConfig);

    void resetMinefield();
    void generateNewMinefield(const MinefieldParameters& minefieldParameters);

    [[nodiscard]] const Minefield& getMinefield() const { return *minefield_; }
    [[nodiscard]] Minefield& getMinefield() { return *minefield_; }

    [[nodiscard]] TilesModel& getTilesModel() const { return *tilesModel_; }

private:
    std::unique_ptr<Minefield> minefield_;
    std::unique_ptr<TilesModel> tilesModel_;
};
