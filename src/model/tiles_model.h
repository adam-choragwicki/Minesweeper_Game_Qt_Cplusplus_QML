#pragma once

#include <QAbstractListModel>
#include <vector>
#include "minefield.h"
#include "tile.h"

class TilesModel : public QAbstractListModel
{
    Q_OBJECT

signals:
    void boardSizeChanged();

public:
    enum TileRoles
    {
        IdRole = Qt::UserRole + 1,
        XRole,
        YRole,
        StateRole,
        AdjacentMinesCountRole,
        MinePresentRole
    };

    explicit TilesModel(Minefield& minefield, QObject* parent = nullptr);

    // QAbstractItemModel overrides
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_PROPERTY(int rowsCount READ getRowsCount NOTIFY boardSizeChanged)
    int getRowsCount() const { return minefield_->getRowsCount(); }

    Q_PROPERTY(int columnsCount READ getColumnsCount NOTIFY boardSizeChanged)
    int getColumnsCount() const { return minefield_->getColumnsCount(); }

    void setMinefield(Minefield* newMinefield)
    {
        minefield_ = newMinefield;
        resetModel();
    }

public slots:
    void resetModel(); // rebuild index (call when minefield is reset/resized)

private slots:
    void onTileUpdated(const Tile& tile);

private:
    void buildIndex(); // create tilesOrdered_ in row-major order
    int indexFromCoordinates(const Coordinates& coordinates) const;

    Minefield* minefield_;
    std::vector<Tile*> tilesOrdered_; // linear view of tiles in row-major order (not owning)
};
