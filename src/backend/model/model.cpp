#include "model/model.h"

void Model::resizeMinefield(const MinefieldParameters& minefieldParameters)
{
    minefield_ = std::make_unique<Minefield>(minefieldParameters);
    MineGenerator::generateMines(minefieldParameters, *minefield_);
    FieldsManager::assignAdjacentMinesCountToAllFields(*minefield_);
}

void Model::reset()
{
    minefield_->resetFields();
    MineGenerator::generateMines(minefield_->getMinefieldParameters(), *minefield_);
    FieldsManager::assignAdjacentMinesCountToAllFields(*minefield_);
}
