import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import automash 1.0

ColumnLayout {
    Layout.fillWidth: true
    Layout.fillHeight: true
    Text {
        text: qsTr("Mash Schedule:")
        Layout.columnSpan: 2
    }
    TableView {
        id: mashTable
        Layout.columnSpan: 2
        Layout.fillWidth: true
        model: mashSchedule
        TableViewColumn {
            id: rest
            role: "name"
            title: qsTr("Rest")
            width: mashTable.width - restTemp.width - restTime.width - 2
            resizable: true
        }
        TableViewColumn {
            id: restTemp
            role: "temp"
            title: qsTr("Temp")
            resizable: false
            horizontalAlignment: Text.AlignRight
            width: 50
        }
        TableViewColumn {
            id: restTime
            role: "time"
            title: qsTr("Time")
            resizable: false
            horizontalAlignment: Text.AlignRight
            width: 75
        }
    }
    RowLayout {
        Layout.columnSpan: 2
        Layout.fillWidth: true
        Button {
            id: add
            Text {
                id: addText
                anchors.centerIn: parent
                text: "+"
            }
            Layout.maximumWidth: addText.width + 15
            onClicked:  {
                addRestDialog.create()
            }
            RestDialog {
                id: addRestDialog
                onFinished: {
                    mashSchedule.append(mashTable.currentRow, name, temp, time)
                }
            }
        }
        Button {
            id: remove
            Text {
                id: removeText
                anchors.centerIn: parent
                text: "-"
            }
            Layout.maximumWidth: removeText.width + 15
            onClicked: mashSchedule.remove(mashTable.currentRow)
        }
        Button {
            id: edit
            Text {
                id: editText
                anchors.centerIn: parent
                text: "Edit"
            }
            Layout.maximumWidth: editText.width + 15
            onClicked:  {
                setRestDialog.edit(mashSchedule.get(mashTable.currentRow))
            }
            RestDialog {
                id: setRestDialog
                onFinished: {
                    mashSchedule.set(mashTable.currentRow, name, temp, time)
                }
            }
        }
        Label {
            Layout.fillWidth: true
        }
        Label {
            text: qsTr("Mash Time:")
        }
        Text {
            text: String(mashSchedule.totalTime)
            Layout.minimumWidth: 50
            horizontalAlignment: Text.AlignRight
        }
    }
}
