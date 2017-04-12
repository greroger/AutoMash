import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import automash 1.0

Dialog {
    id: dialog

    signal finished(string name, double amount, string time)

    function create() {
        name.text = ""
        amount.text = ""
        time.text = ""
        dialog.title = qsTr("Add Hop")
        dialog.open()
        name.focus = true
    }

    function edit(hop) {
        name.text = hop.name
        amount.text = hop.amount
        time.text = hop.time
        dialog.title = qsTr("Edit Hop")
        dialog.open()
        name.focus = true
    }

    modality: Qt.WindowModal
    standardButtons: StandardButton.Ok | StandardButton.Cancel | StandardButton.Apply
    ColumnLayout {
        //columns: 2
        anchors.fill: parent
        RowLayout {
            Layout.fillWidth: true
            Label {
                text: "Hop:"
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
                text: "Amount(oz):"
            }
            TextField {
                id: amount
                placeholderText: "10"
                horizontalAlignment: TextInput.AlignRight
                Layout.fillWidth: true
                inputMethodHints: Qt.ImhDigitsOnly
            }
        }
        RowLayout {
            Layout.fillWidth: true
            Label {
                text: "Time(minutes):"
            }
            TextField {
                id: time
                placeholderText: "10"
                horizontalAlignment: TextInput.AlignRight
                Layout.fillWidth: true
                inputMethodHints: Qt.ImhDigitsOnly
            }
        }
    }
    onAccepted: finished(name.text, amount.text, time.text)
}
