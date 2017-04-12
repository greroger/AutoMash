import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import automash 1.0

ColumnLayout {
    Layout.fillWidth: true
    Layout.fillHeight: true
    Text {
        text: qsTr("Hop Schedule:")
    }
    TableView {
        id: hopTable
        Layout.fillWidth: true
        Layout.fillHeight: true
        model: hops
        TableViewColumn {
            id: name
            role: "hop"
            title: qsTr("Hop")
            width: hopTable.width - type.width - amount.width - time.width - 2
            resizable: true
        }
        TableViewColumn {
            id: type
            role: "type"
            title: qsTr("Type")
            resizable: false
            width: 50
        }
        TableViewColumn {
            id: amount
            role: "amount"
            title: qsTr("Ounces")
            resizable: false
            width: 60
        }
        TableViewColumn {
            id: time
            role: "time"
            title: qsTr("Minutes")
            resizable: false
            width: 70
        }
    }
    RowLayout {
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
                addDialog.create()
            }
                HopDialog {
                    id: addDialog
                    onFinished: {
                        hops.append(hopTable.currentRow, name, type.currentIndex, amount, time)
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
            onClicked: hops.remove(hopTable.currentRow)
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
                setDialog.edit(hops.get(hopTable.currentRow))
            }
            HopDialog {
                id: setDialog
                onFinished: {
                    hops.set(hopTable.currentRow, name, temp, time)
                }
            }
        }
        Label {
            Layout.fillWidth: true
        }
        Label {
            text: qsTr("Minimum Boil:")
        }
        Text {
            text: hops.minimumBoil
            Layout.minimumWidth: 50
            horizontalAlignment: Text.AlignRight
        }
    }
}
