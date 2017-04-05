import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

Item {
    ColumnLayout {
        anchors.fill: parent
        RowLayout {
            id: file
            Layout.fillWidth: true
            TextField {
                id: recipeName
                placeholderText: "eat shit and die"
                Layout.fillWidth: true
            }
            Button {
                id: loadRecipe
                text: qsTr("Load")
            }
            Button {
                id: saveRecipe
                text: qsTr("Save")
                onClicked: {
                    fileDialogRecipe.title = "Save Recipe to Disk"
                    fileDialogRecipe.selectExisting = true
                    fileDialogRecipe.open()
                }
            }
            Button {
                id: saveAsRecipe
                text: qsTr("SaveAs")
            }
        }
        GridLayout {
            id: ingrediants
            Layout.fillWidth: true
            Layout.fillHeight: true
            columns: 2
            Text {
                text: qsTr("Grain Bill:")
            }
            Text {
                text: qsTr("Hop Schedule:")
            }

            TableView {
                id: grains
                Layout.fillWidth: true
                Layout.fillHeight: true
                TableViewColumn {
                    id: grainName
                    role: "grain"
                    title: qsTr("Grain")
                    width: grains.width - grainAmount.width - 2
                }
                TableViewColumn {
                    id: grainAmount
                    role: "amount"
                    title: qsTr("Pounds")
                }
            }
            TableView {
                id: hops
                Layout.fillWidth: true
                Layout.fillHeight: true
                TableViewColumn {
                    id: hopname
                    role: "hop"
                    title: qsTr("Hop")
                    width: hops.width - hopAmount.width - hopTime.width - 2
                }
                TableViewColumn {
                    id: hopAmount
                    role: "amount"
                    title: qsTr("Ounces")
                }
                TableViewColumn {
                    id: hopTime
                    role: "time"
                    title: qsTr("Boil Time")
                }
            }
            RowLayout {
                id: grainControls
                Button {
                    id: grainAdd
                    text: "+"
                }
                Button {
                    id: grainRemove
                    text: "-"
                }
                Text {
                    text: qsTr("Total:")
                }
                Text {
                    id: grainTotal
                }
            }
            RowLayout {
                id: hopControls
                Button {
                    id: hopAdd
                    text: "+"
                }
                Button {
                    id: hopRemove
                    text: "-"
                }
            }
        }

    }
    FileDialog {
        id: fileDialogRecipe
        folder: shortcuts.home
        selectMultiple: false
        selectFolder: false
    }
}
