import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

Dialog {
    id: dialog

    signal finished(string name, double amount)

    function create() {
        name.text = ""
        amount.text = ""
        dialog.title = qsTr("Add Grain")
        dialog.open()
        name.focus = true
    }

    function edit(grain) {
        name.text = grain.name
        amount.text = grain.amount
        dialog.title = qsTr("Edit Grain")
        dialog.open()
        name.focus = true
    }

    modality: Qt.WindowModal
    standardButtons: StandardButton.Ok | StandardButton.Cancel | StandardButton.Apply
    ColumnLayout {
        anchors.fill: parent
        RowLayout {
            Layout.fillWidth: true
            Label {
                text: "Grain:"
            }
            TextField {
                id: name
                placeholderText: "Name"
                horizontalAlignment: TextInput.AlignRight
                Layout.fillWidth: true
            }
        }
        RowLayout {
            Layout.fillWidth: true
            Label {
                text: "Amount(lbs):"
            }
            TextField {
                id: amount
                placeholderText: "10.0"
                horizontalAlignment: TextInput.AlignRight
                Layout.fillWidth: true
                inputMethodHints: Qt.ImhDigitsOnly
            }
        }
    }
    onAccepted: finished(name.text, amount.text)
}

