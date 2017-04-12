import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import automash 1.0

ColumnLayout {
    Layout.fillWidth: true
    Layout.fillHeight: true
    Text {
        text: qsTr("Grain Bill:")
    }
    TableView {
        id: grainTable
        Layout.fillWidth: true
        Layout.fillHeight: true
        model: grainBill
        TableViewColumn {
            id: name
            role: "name"
            title: qsTr("Grain")
            width: grainTable.width - amount.width - 2
            resizable: true
        }
        TableViewColumn {
            id: amount
            role: "amount"
            title: qsTr("Pounds")
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
            GrainDialog {
                id: addDialog
                onFinished: {
                    grainBill.append(grainTable.currentRow, name, amount)
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
            onClicked: grainBill.remove(grainTable.currentRow)
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
                setDialog.edit(grainBill.get(grainTable.currentRow))
            }
            GrainDialog {
                id: setDialog
                onFinished: {
                    grainBill.set(grainTable.currentRow, name, amount)
                }
            }
        }
        Label {
            Layout.fillWidth: true
        }
        Label {
            text: qsTr("Total Grain:")
        }
        Text {
            text: String(grainBill.totalAmount)
            Layout.minimumWidth: 50
            horizontalAlignment: Text.AlignRight
        }
    }
}
