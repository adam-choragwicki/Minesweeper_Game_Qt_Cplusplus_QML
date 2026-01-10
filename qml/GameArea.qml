// GameArea.qml
import QtQuick

Item {
    id: gameArea

    Board {
        id: board
        anchors.centerIn: parent
    }

    GameInput {
        anchors.fill: parent
    }
}
