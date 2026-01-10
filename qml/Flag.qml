// Flag.qml
import QtQuick

Item {
    id: root
    required property real size

    width: size
    height: size

    // ================= Pole =================
    Rectangle {
        id: pole
        width: size * 0.12
        height: size * 0.85
        radius: width / 2
        color: "#bdbdbd"
        anchors.left: parent.left
        anchors.leftMargin: size * 0.12
        anchors.verticalCenter: parent.verticalCenter
    }

    // Pole top knob
    Rectangle {
        width: size * 0.18
        height: width
        radius: width / 2
        color: "#9e9e9e"
        anchors.horizontalCenter: pole.horizontalCenter
        anchors.bottom: pole.top
        anchors.bottomMargin: -height * 0.25
    }

    // ================= Flag body =================
    Rectangle {
        id: flagBody
        width: size * 0.58
        height: size * 0.38
        radius: size * 0.04
        color: "#ff2a1a"

        anchors.left: pole.right
        anchors.leftMargin: size * 0.02

        anchors.verticalCenter: pole.verticalCenter
        anchors.verticalCenterOffset: -size * 0.12

        // simple white highlight stripe
        Rectangle {
            width: parent.width * 0.08
            height: parent.height * 0.7
            radius: width / 2
            color: "white"
            opacity: 0.75
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.12
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    // ================= Base =================
    Rectangle {
        width: size * 0.36
        height: size * 0.12
        radius: height / 3
        color: "#616161"
        anchors.horizontalCenter: pole.horizontalCenter
        anchors.bottom: parent.bottom
    }

    Rectangle {
        width: size * 0.48
        height: size * 0.14
        radius: height / 3
        color: "#424242"
        anchors.horizontalCenter: pole.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -height * 0.45
    }
}
