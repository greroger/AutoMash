import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 1024
    height: 600
    title: qsTr("The AutoMash")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        RecipePage {
        }

        StrikePage {
        }

        Page {
            Label {
                text: qsTr("Mash")
                anchors.centerIn: parent
            }
        }

        SpargePage {
        }

        Page {
            Label {
                text: qsTr("Boil")
                anchors.centerIn: parent
            }
        }

        Page {
            Label {
                text: qsTr("Chill")
                anchors.centerIn: parent
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Recipe")
        }
        TabButton {
            text: qsTr("Strike")
        }
        TabButton {
            text: qsTr("Mash")
        }
        TabButton {
            text: qsTr("Sparge")
        }
        TabButton {
            text: qsTr("Boil")
        }
        TabButton {
            text: qsTr("Chill")
        }
    }
}
