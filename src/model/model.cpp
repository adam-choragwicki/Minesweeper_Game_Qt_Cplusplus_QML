#include "model/model.h"
#include "tiles_manager.h"

Model::Model(const GameConfig& gameConfig)
{
    qDebug() << "Initializing model";

    minefield_ = std::make_unique<Minefield>(gameConfig.getInitialMinefieldParameters());
    tilesModel_ = std::make_unique<TilesModel>(*minefield_);
}

void Model::resetMinefield()
{
    minefield_->reset();
}

void Model::generateNewMinefield(const MinefieldParameters& minefieldParameters)
{
    // 1. Create the new minefield first (the old minefield remains alive)
    auto newMinefield = std::make_unique<Minefield>(minefieldParameters);

    // 2. Switch to the new minefield pointer in TilesModel.
    // buildIndex() will safely disconnect from the old tilesOrdered_ because the old minefield is still alive at this point.
    tilesModel_->setMinefield(newMinefield.get());

    // 3. Replace the model's minefield; the old minefield is destroyed here.
    minefield_ = std::move(newMinefield);

    // TilesModel has already rebuilt its index and emitted notifications (resetModel), so nothing more needed here.
}
