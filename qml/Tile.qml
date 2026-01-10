// Tile.qml
import QtQuick
import QtQuick.Controls // for tile tooltip
import TileStateEnum

Rectangle {
    required property int xRole
    required property int yRole
    required property int idRole
    required property int stateRole
    required property int adjacentMinesCountRole
    required property int minePresentRole
    required property real tileSize // initialized by GridView

    required property real gap // gap passed from Board.qml delegate (pixels)

    // GridView positions delegate automatically so not need to set x/y manually
    width: tileSize
    height: tileSize

    readonly property color coveredTileColor: "#3C3C3C"
    readonly property color zeroTileColor: "#F0F0F0" // tile with no adjacent mines
    readonly property color uncoveredTileColor: "#71D4DB" // tile with adjacent mines
    readonly property color mineExplodedTileColor: "red" // background color of mine with exploded tile

    property color tileColor: {
        if (stateRole === TileState.COVERED) return coveredTileColor
        if (stateRole === TileState.UNCOVERED)
            return adjacentMinesCountRole === 0 ? zeroTileColor : uncoveredTileColor
        if (stateRole === TileState.FLAGGED) return coveredTileColor // keep same color as covered tile
        if (stateRole === TileState.MINE_EXPLODED) return mineExplodedTileColor

        console.error("QML: Unknown tile state: " + stateRole)
    }

    color: "transparent" // root rectangle is transparent; tile drawing happens in tileBody

    onStateRoleChanged: {
        // console.log("QML: Tile " + idRole + " state changed to " + Controller.tileStateToString(stateRole))

        if (stateRole === TileState.MINE_EXPLODED) {
            explosionAnimation.restart()
        }
    }

    // onColorChanged: { console.log("QML: Tile " + idRole + " color changed to " + color)}

    // ================= Tile body (inset by gap) =================
    Rectangle {
        id: tileBody
        anchors.fill: parent
        anchors.margins: gap
        radius: Math.min(width, height) * 0.28
        color: tileColor

        // -------- Explosion animation (ONE SHOT) --------
        SequentialAnimation {
            id: explosionAnimation
            running: false

            ParallelAnimation {
                NumberAnimation {
                    target: mine
                    property: "scale"
                    from: mine.initialScale
                    to: mine.explodedScale
                    duration: 400
                    easing.type: Easing.OutBack
                }

                SequentialAnimation {
                    NumberAnimation {
                        target: flash; property: "opacity";
                        to: 0.9; duration: 90
                    }
                    PauseAnimation {
                        duration: 120
                    }
                    NumberAnimation {
                        target: flash; property: "opacity";
                        to: 0.0; duration: 140
                    }
                }
            }
        }

        // -------- Explosion flash effect overlay --------
        Rectangle {
            id: flash
            anchors.fill: parent
            color: "white"
            opacity: 0.0
            visible: opacity > 0
        }

        // -------- Hover highlight --------
        Rectangle {
            anchors.fill: parent
            radius: parent.radius
            visible: hover.hovered && stateRole === TileState.COVERED
            color: "white"
            opacity: 0.12
        }

        // -------- Flag --------
        Flag {
            visible: stateRole === TileState.FLAGGED
            anchors.centerIn: parent
            anchors.horizontalCenterOffset: parent.width * 0.10
            size: Math.min(parent.width, parent.height) * 0.72
        }

        // -------- Mine --------
        Mine {
            id: mine
            visible: stateRole === TileState.MINE_EXPLODED || (showDebugGlobal && showMine && minePresentRole)
            anchors.centerIn: parent
            size: Math.min(parent.width, parent.height) * 0.78
            readonly property real initialScale: 0.25
            readonly property real explodedScale: 1.0
            scale: initialScale
        }

        // -------- Adjacent mines count --------
        Text {
            visible: stateRole === TileState.UNCOVERED && adjacentMinesCountRole !== 0
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -parent.height * 0.06 // offset to center the number in the tile
            text: adjacentMinesCountRole
            font.bold: true
            font.pixelSize: Math.min(parent.width, parent.height)
            color: "black"
        }

        // debug texts inside the tile body (only visible when showDebugGlobal == true)
        readonly property real debugTextSize: Math.max(8, tileSize * 0.12)

        // display ID
        Text {
            visible: showDebugGlobal && showId
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.rightMargin: parent.width * 0.05
            anchors.bottomMargin: parent.height * 0.05
            text: idRole
            font.bold: true
            font.pixelSize: tileBody.debugTextSize
            color: "white"
        }

        // display tile state enum in string form
        Text {
            visible: showDebugGlobal && showState
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            text: Controller.tileStateToString(stateRole)
            font.bold: true
            font.pixelSize: tileBody.debugTextSize
            color: "white"
        }

        // display adjacent mines count (debug)
        Text {
            visible: showDebugGlobal && showAdjacentMinesCount
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            text: adjacentMinesCountRole
            font.bold: true
            font.pixelSize: tileBody.debugTextSize
            color: "yellow"
        }

        // display if mine is present (debug)
        Text {
            visible: showDebugGlobal && showMine && minePresentRole
            anchors.centerIn: parent
            anchors.verticalCenterOffset: -parent.height * 0.22
            text: "MINE"
            font.bold: true
            font.pixelSize: tileBody.debugTextSize
            color: "red"
        }
    }

    // ================================================Interaction (hover/tooltip)================================================

    // Interaction area: immediate onPressed behavior (no drag)
    MouseArea {
        anchors.fill: parent
        enabled: Controller.gameRunning
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        hoverEnabled: false

        onPressed: function (mouse) {
            if (mouse.button === Qt.LeftButton)
                Controller.onTileLeftClicked(yRole, xRole)
            else if (mouse.button === Qt.RightButton)
                Controller.onTileRightClicked(yRole, xRole)
        }
    }

    HoverHandler {
        id: hover
        enabled: Controller.gameRunning
    }

    ToolTip {
        visible: showDebugGlobal && showTooltip && hover.enabled && hover.hovered
        delay: 200
        text: yRole + "," + xRole
        x: hover.point.position.x + 12
        y: hover.point.position.y + 12
    }

    // Debug config
    readonly property bool showDebugGlobal: false
    readonly property bool showId: true
    readonly property bool showState: true
    readonly property bool showAdjacentMinesCount: true
    readonly property bool showMine: true
    readonly property bool showTooltip: true
}
