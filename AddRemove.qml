import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

RowLayout {
    Button {
        id: add
        Text {
            id: addText
            anchors.centerIn: parent
            text: "+"
        }
        Layout.maximumWidth: addText.width + 15
    }
    Button {
        id: remove
        Text {
            id: removeText
            anchors.centerIn: parent
            text: "-"
        }
        Layout.maximumWidth: removeText.width + 15
    }
}
