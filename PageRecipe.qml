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
                    onClicked:  {
                        addDialog.create()
                    }
                    RestDialog {
                        id: addDialog
                        onFinished: {
                            mashModel.append(mashTable.currentRow, name, temp, time)
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
                    onClicked: mashModel.remove(mashTable.currentRow)
                }
                Button {
                    id: edit
                    Text {
                        anchors.centerIn: parent
                        text: "Edit"
                    }
                    Layout.maximumWidth: addText.width + 15
                    onClicked:  {
                        setDialog.edit(mashModel.get(mashTable.currentRow))
                    }
                    RestDialog {
                        id: setDialog
                        onFinished: {
                            mashModel.set(mashTable.currentRow, name, temp, time)
                        }
                    }
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
    Rest {
        id: crap
        name: "fuck"
        temp: 180
        time: 60
    }
}
