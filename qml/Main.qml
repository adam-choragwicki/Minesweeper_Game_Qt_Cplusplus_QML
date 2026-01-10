import QtQuick

Window {
    id: mainWindow
    width: 800
    height: 800
    minimumWidth: 800
    minimumHeight: 800
    visible: true

    Component.onCompleted: {
        if (Controller.startInFullScreenEnabled) {
            console.log("Starting in fullscreen")
            mainWindow.showFullScreen()
        } else {
            console.log("Starting in windowed mode")
            mainWindow.showNormal()
        }
    }

    UiScaler {
        id: uiScaler
        target: gameArea   // this ensures UI scales with a visible gameplay area
    }

    /* Maintain the aspect ratio with black bars */
    Rectangle {
        id: letterboxContainer
        anchors.fill: parent
        color: "black"

        // This Item keeps the correct scaling inside any window shape
        Item {
            id: gameViewport
            anchors.centerIn: parent

            readonly property real targetAspect: 1
            property real currentAspect: letterboxContainer.width / letterboxContainer.height

            // Maintain the aspect ratio and center it
            width: currentAspect > targetAspect ? letterboxContainer.height * targetAspect : letterboxContainer.width
            height: currentAspect > targetAspect ? letterboxContainer.height : letterboxContainer.width / targetAspect

            GameArea {
                id: gameArea
                anchors.fill: parent
            }
        }
    }

    function onChangeGameParameters() {
        gameDimensionsDialog.open()
        Controller.onChangeGameParametersClicked()
    }

    // Overlays
    EndGameOverlay {
        visible: false
        objectName: "endGameOverlay"
        anchors.fill: parent
        onPlayAgainClicked: Controller.onPlayAgainClicked()

        onChangeGameParametersClicked: {
            onChangeGameParameters()
        }

        onQuitClicked: Controller.onQuitClicked()
    }

    EscapeMenuOverlay {
        visible: false
        objectName: "escapeMenuOverlay"
        anchors.fill: parent

        onResumeClicked: Controller.onResumeClicked()
        onRestartClicked: Controller.onRestartClicked()

        onChangeGameParametersClicked: {
            onChangeGameParameters()
        }

        onQuitClicked: Controller.onQuitClicked()
    }

    GameDimensionsDialog {
        id: gameDimensionsDialog
        anchors.centerIn: parent
    }
}
