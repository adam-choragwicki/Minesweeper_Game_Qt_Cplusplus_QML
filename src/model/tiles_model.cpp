#include "model/tiles_model.h"
#include <QDebug>

TilesModel::TilesModel(Minefield& minefield, QObject* parent) : QAbstractListModel(parent), minefield_(&minefield)
{
    buildIndex();
}

int TilesModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(tilesOrdered_.size());
}

QVariant TilesModel::data(const QModelIndex& index, const int role) const
{
    if (!index.isValid())
    {
        qFatal() << "TilesModel: invalid index";
        return {};
    }

    const int row = index.row();

    if (row < 0 || row >= static_cast<int>(tilesOrdered_.size()))
    {
        qFatal() << "TilesModel: invalid row";
        return {};
    }

    const Tile* tile = tilesOrdered_[row];

    if (!tile)
    {
        qFatal() << "TilesModel: invalid tile";
        return {};
    }

    switch (role)
    {
        case IdRole:
            return tile->getId();
        case XRole:
            return tile->getCoordinates().getColumn();
        case YRole:
            return tile->getCoordinates().getRow();
        case StateRole:
            return static_cast<int>(tile->getState());
        case AdjacentMinesCountRole:
            if (tile->getAdjacentMineCount().has_value())
            {
                return *tile->getAdjacentMineCount();
            }
            return QVariant(); // undefined in QML when std::nullopt
        case MinePresentRole:
            return tile->isMinePresent();
        default:
            return {};
    }
}

QHash<int, QByteArray> TilesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "idRole";
    roles[XRole] = "xRole";
    roles[YRole] = "yRole";
    roles[StateRole] = "stateRole";
    roles[AdjacentMinesCountRole] = "adjacentMinesCountRole";
    roles[MinePresentRole] = "minePresentRole";
    return roles;
}

void TilesModel::buildIndex()
{
    // Disconnect previous connections from tile signals to this (if any)
    for (const Tile* tile: tilesOrdered_)
    {
        if (tile)
        {
            // disconnect only the specific connection from a tile to this object
            disconnect(tile, nullptr, this, nullptr);
        }
    }

    tilesOrdered_.clear();

    const int rowsCount = minefield_->getRowsCount();
    const int columnsCount = minefield_->getColumnsCount();

    tilesOrdered_.reserve(rowsCount * columnsCount);

    // row-major ordering using Coordinates(row, column)
    for (int row = 1; row <= rowsCount; ++row)
    {
        for (int column = 1; column <= columnsCount; ++column)
        {
            const Coordinates coords(row, column);

            Tile& tile = minefield_->getTileAt(coords);
            tilesOrdered_.push_back(&tile);

            connect(&tile, &Tile::tileChanged, this, &TilesModel::onTileUpdated);
        }
    }
}

void TilesModel::resetModel()
{
    beginResetModel();
    buildIndex();
    endResetModel();

    emit boardSizeChanged();
}

int TilesModel::indexFromCoordinates(const Coordinates& coordinates) const
{
    const int row = coordinates.getRow();
    const int column = coordinates.getColumn();

    const int rowsCountValue = getRowsCount();
    const int columnsCountValue = getColumnsCount();

    if (row < 1 || row > rowsCountValue || column < 1 || column > columnsCountValue)
    {
        qFatal() << "TilesModel: invalid coordinates";
        return -1;
    }

    // row-major index
    return (row - 1) * columnsCountValue + (column - 1);
}

void TilesModel::onTileUpdated(const Tile& tile)
{
    const int index = indexFromCoordinates(tile.getCoordinates());

    if (index < 0)
    {
        qFatal() << "TilesModel: invalid index";
        return;
    }

    const QModelIndex qIndex = createIndex(index, 0);
    emit dataChanged(qIndex, qIndex, {IdRole, XRole, YRole, StateRole, AdjacentMinesCountRole, MinePresentRole});
}
