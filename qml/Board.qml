// Board.qml
import QtQuick

Item {
    width: borderRect.width
    height: borderRect.height

    property alias tileSize: minefield.tileSize

    Rectangle {
        id: borderRect
        anchors.centerIn: parent

        // outer size = board size and border on all sides
        width: minefield.width + 2 * border.width
        height: minefield.height + 2 * border.width

        color: "transparent"
        border.color: "black"
        border.width: 4 // this has to be even, otherwise there is sub-pixel positioning and rendering issues

        Rectangle {
            id: minefield
            anchors.centerIn: parent
            width: gridColumnsCount * tileSize
            height: gridRowsCount * tileSize

            color: "black"

            readonly property int gridRowsCount: tilesModel.rowsCount
            readonly property int gridColumnsCount: tilesModel.columnsCount

            readonly property int minimumTileSize: 20

            // dynamic tile size which always fits the available screen area but tile size is never smaller than 10 px
            property real tileSize: Math.floor(
                Math.max(minimumTileSize,
                    Math.min(gameArea.width / gridColumnsCount,
                        gameArea.height / gridRowsCount)
                )
            )

            property real tileGap: Math.max(1, Math.floor(tileSize * 0.05))

            GridView {
                id: gridView
                anchors.fill: parent
                model: tilesModel
                cellWidth: tileSize
                cellHeight: tileSize
                flow: GridView.FlowLeftToRight
                snapMode: GridView.NoSnap
                highlightFollowsCurrentItem: false
                interactive: false
                clip: true

                delegate: Tile {
                    tileSize: gridView.cellWidth
                    gap: minefield.tileGap
                }
            }
        }
    }
}
