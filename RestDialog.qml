import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

Dialog {
    id: dialog

    signal finished(string name, int temp, int time)

    function create() {
        dialog.title = qsTr("Add Rest");
        dialog.open();
    }

    function edit(rest) {
    }

    modality: Qt.WindowModal
    standardButtons: StandardButton.Ok | StandardButton.Cancel | StandardButton.Apply
    ColumnLayout {
        //columns: 2
        anchors.fill: parent
        RowLayout {
            Layout.fillWidth: true
            Label {
                text: "Rest:"
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
                text: "Temp(˚F):"
            }
            TextField {
                id: temp
                placeholderText: "150"
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
                placeholderText: "60"
                horizontalAlignment: TextInput.AlignRight
                Layout.fillWidth: true
            }
        }
    }
    onAccepted: finished(name.text, temp.text, time.text)
}

