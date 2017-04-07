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
                id: openRecipe
                text: qsTr("Open")
                onClicked: {
                    fileDialogRecipe.title = "Open Recipe File"
                    fileDialogRecipe.selectExisting = true
                    fileDialogRecipe.open()
                }
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
                    resizable: true
                }
                TableViewColumn {
                    id: grainAmount
                    role: "amount"
                    title: qsTr("Pounds")
                    resizable: false
                    width: 70
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
                    width: hops.width - hopType.width - hopAmount.width - hopTime.width - 2
                    resizable: true
                }
                TableViewColumn {
                    id: hopType
                    role: "type"
                    title: qsTr("Type")
                    resizable: false
                    width: 50
                    delegate: Item {
                        ComboBox {
                            anchors.verticalCenter: parent.verticalCenter
                            model: ListModel {
                                ListElement { text: qsTr("Whole") }
                                ListElement { text: qsTr("Plug") }
                                ListElement { text: qsTr("Pellet") }
                                ListElement { text: qsTr("Shot") }
                            }
                        }
                    }
                }

                TableViewColumn {
                    id: hopAmount
                    role: "amount"
                    title: qsTr("Ounces")
                    resizable: false
                    width: 60
                }
                TableViewColumn {
                    id: hopTime
                    role: "time"
                    title: qsTr("Minutes")
                    resizable: false
                    width: 70
                }
            }
            RowLayout {
                id: grainControls
                Layout.alignment: Qt.AlignHLeft | Qt.AlignVCenter
                Layout.fillWidth: true
                Layout.fillHeight: true
                layoutDirection: Qt.LeftToRight
                AddRemove {
                }
                Text {
                    text: qsTr("Total:")
                    Layout.alignment: Qt.AlignRight
                }
                Text {
                    id: grainTotal
                    Layout.alignment: Qt.AlignRight
                    Layout.maximumWidth:70
                    Layout.minimumWidth:70
                }
            }
            RowLayout {
                id: hopControls
                Layout.fillWidth: true
                AddRemove {
                }
            }
            Text {
                text: qsTr("Mash Schedule:")
                Layout.columnSpan: 2
            }
            TableView {
                id: mashTable
                Layout.columnSpan: 2
                Layout.fillWidth: true
                model: mashModel
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
                    width: 50
                    /*
                    delegate: Item {
                        SpinBox {
                            id: tempDel
                            anchors.fill: parent
                            decimals: 0
                            maximumValue: 212
                            minimumValue: 80
                            value: styleData.value
                            onValueChanged: {
                                mashModel.setData(mashModel.index(styleData.row, 0), value, mashModel.temp)
                            }
                        }
                    }
                    */
                }
                TableViewColumn {
                    id: restTime
                    role: "time"
                    title: qsTr("Time")
                    resizable: false
                    width: 50
                }
            }
            RowLayout {
                Button {
                    id: add
                    Text {
                        id: addText
                        anchors.centerIn: parent
                        text: "+"
                    }
                    Layout.maximumWidth: addText.width + 15
                    //onClicked: mashModel.addRow(mashModel.index(mashTable.currentRow, 0))
                    onClicked:  {
                        restDialog.open()
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
                    onClicked: mashModel.removeRow(mashModel.index(mashTable.currentRow, 0))
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
    Dialog {
        id: restDialog
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
                    placeholderText: "150"
                    horizontalAlignment: TextInput.AlignRight
                    Layout.fillWidth: true
                }
            }
            RowLayout {
                Layout.fillWidth: true
                Label {
                    text: "Time(minutes):"
                }
                TextField {
                    placeholderText: "60"
                    horizontalAlignment: TextInput.AlignRight
                    Layout.fillWidth: true
                }
            }
        }
    }
}
