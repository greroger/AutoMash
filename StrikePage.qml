import QtQuick 2.7
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1
import automash 1.0

Item {
    GridLayout {
        id: grid
        anchors.fill: parent
        columns: 3
        rows: 2
        anchors.margins: 10

        ColumnLayout {
            Layout.alignment: Qt.AlignTop
            Label {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                text: qsTr("Recirc HLT")
                font.pixelSize: 19
                font.bold: true
            }
            RowLayout {
                Text {
                    text: qsTr("Fill HLT to:")
                }
                Text {
                    text: grainBill.totalWater
                }
            }
            TextArea {
                readOnly: true
                wrapMode: TextEdit.WordWrap
                text: qsTr("Connect HLT valve to HLT pump inlet. "
                           + "Connect HLT pump outlet to recirc."
                           + "Light burner then start recirc.")
                Layout.fillWidth: true
            }
            RowLayout {
                Label {
                    id: targetLabel
                    anchors.left: parent
                    text: qsTr("Target (˚F):")
                }
                Text {
                    anchors.left: targetLabel
                    anchors.right: parent
                    text: mashSchedule.doughIn
                    color: "pink"
                }
            }
        }
        ColumnLayout {
            Layout.alignment: Qt.AlignTop
            Label {
                text: qsTr("Fill Deadspace")
                font.pointSize: 20
                font.bold: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }
            RowLayout {
                Text {
                    text: qsTr("Fill HLT to ")
                }
                Text {
                    text: grainBill.totalWater
                }
            }
            TextArea {
                readOnly: true
                wrapMode: TextEdit.WordWrap
                text: qsTr("Connect HLT valve to HLT pump inlet. "
                           + "Connect HLT pump outlet to recirc."
                           + "Light burner then start recirc."
                           + "Keep Burner lit until ")
                Layout.fillWidth: true
            }
        }
        ColumnLayout {
            Layout.alignment: Qt.AlignTop
            Label {
                text: qsTr("Dough In")
                font.pointSize: 20
                font.bold: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }
            RowLayout {
                Text {
                    text: qsTr("Fill HLT to ")
                }
                Text {
                    text: grainBill.totalWater
                }
            }
            TextArea {
                readOnly: true
                wrapMode: TextEdit.WordWrap
                text: qsTr("Connect HLT valve to HLT pump inlet. "
                           + "Connect HLT pump outlet to recirc."
                           + "Light burner then start recirc."
                           + "Keep Burner lit until ")
                Layout.fillWidth: true
            }
        }
        PumpPanel {
            pump: hltPump
            Layout.row: 2
            Layout.column: 0
            Layout.alignment: Qt.AlignLeft
        }

        Button {
            text: qsTr("Quit")
            onClicked: {
                Qt.quit()
            }
        }

        PumpPanel {
            pump: mashPump
            Layout.row: 2
            Layout.column: 2
            Layout.alignment: Qt.AlignRight
            Layout.rightMargin: 10
        }
    }
}
