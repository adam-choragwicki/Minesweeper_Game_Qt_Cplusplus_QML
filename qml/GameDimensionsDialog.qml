// GameDimensionsDialog.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    id: dialog
    modal: true
    width: 400
    height: 250
    title: ""

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 20

        // ===== Title === ==
        Label {
            text: "Game parameters"
            font.pixelSize: 22
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }

        // ===== Form =====
        GridLayout {
            columns: 2
            rowSpacing: 12
            columnSpacing: 16
            Layout.fillWidth: true

            Label {
                text: "Rows:"
                font.bold: true
            }
            ComboBox {
                id: rowsCount
                model: GameConfig.rowsCountOptions
                Layout.fillWidth: true
            }

            Label {
                text: "Columns:"
                font.bold: true
            }
            ComboBox {
                id: columnsCount
                model: GameConfig.columnsCountOptions
                Layout.fillWidth: true
            }

            Label {
                text: "Mine percentage:"
                font.bold: true
            }
            ComboBox {
                id: minePercentage
                model: GameConfig.minePercentageOptions
                Layout.fillWidth: true
            }
        }

        Item {
            Layout.fillHeight: true
        } // spacer

        // ===== Buttons =====
        RowLayout {
            Layout.fillWidth: true
            spacing: 16
            Layout.alignment: Qt.AlignHCenter

            Button {
                text: "Cancel"
                Layout.preferredWidth: 120
                onClicked: dialog.close()
            }

            Button {
                text: "OK"
                Layout.preferredWidth: 120
                onClicked: {
                    Controller.resizeGame(
                        parseInt(rowsCount.currentText),
                        parseInt(columnsCount.currentText),
                        parseInt(minePercentage.currentText)
                    )
                    dialog.close()
                }
            }
        }
    }
}
