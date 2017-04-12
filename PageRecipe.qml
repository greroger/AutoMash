import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import automash 1.0

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
                id: openRecipe
                text: qsTr("Open")
                onClicked: {
                    fileDialogRecipe.title = "Open Recipe File"
                    fileDialogRecipe.selectExisting = true
                    fileDialogRecipe.open()
                }
            }
            Button {
                Rest {
                    id: newOne
                }

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
            GrainBill {
                Layout.columnSpan: 1
            }
            Hops {
                Layout.columnSpan: 1
            }
            MashSchedule {
                Layout.columnSpan: 2
            }

        }
        RowLayout {
            Layout.fillWidth: true;
            Label {
                text: qsTr("Mash Thickness (qts./lb):")
            }
            TextField {
                Layout.minimumWidth: 50
            }
            Label {
                text: qsTr("Dead Space (gal):")
            }
            TextField {
                Layout.minimumWidth: 50
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
