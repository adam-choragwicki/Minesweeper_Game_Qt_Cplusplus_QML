// GameInput.qml
import QtQuick

Item {
    // For keyboard events
    FocusScope {
        focus: true

        Keys.onPressed: (event) => {
            Controller.processKeyPress(event.key)
            event.accepted = true
        }
    }
}
