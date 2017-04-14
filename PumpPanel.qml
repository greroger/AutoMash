import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4
import automash 1.0

ColumnLayout {
    property var pump
    id: pumpCtrl
    Layout.maximumWidth: 150

    ToggleButton {
        id: tb
        Layout.preferredWidth: 75
        Layout.preferredHeight: Layout.preferredWidth
        checked: pump.running
        text: pump.name
        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        onClicked: {
            tb.checked ? pump.start() : pump.stop()
        }
        Connections {
            target: pump
            onRunningChanged: {
                tb.checked = running
            }
        }
    }

    RowLayout {
        Label {
            text: qsTr("Actual Flow:")
        }
        Text {
            id: actual
            text: pump.actualFlow
            Layout.fillWidth: true
            horizontalAlignment: TextInput.AlignRight
        }
    }
    RowLayout {
        Layout.fillWidth: true
        Label {
            id: pumpedLabel
            text: qsTr("Pumped:")
        }
        Text {
            id: pumped
            text: pump.pumped
            Layout.preferredWidth: pumpCtrl.width - pumpedLabel.width - reset.width
            horizontalAlignment: TextInput.AlignRight
        }
        RoundButton {
            id: reset
            text: "\u21a9"
            flat: true
            onClicked: pump.resetPumped()
        }
    }

    Slider {
        id: slider
        Layout.fillWidth: true
        anchors.horizontalCenter: parent.horizontalCenter
        stepSize: 5.0
        from: 5.0
        to: 100.0
        value: pump.desiredFlow
        onValueChanged: pump.desiredFlow = value
    }
}
