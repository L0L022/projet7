import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

import me 1.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")    

    StackLayout {
        id: view
        anchors.bottom: rowLayout.top
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        currentIndex: bar.currentIndex

        Repeater {
            model: players
            delegate: NewPlayerView {
                height: view.height
                width: view.width
            }
        }
    }

    RowLayout {
        id: rowLayout
        anchors.leftMargin: 6
        anchors.bottomMargin: 6
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 6

        TabBar {
            id: bar
            Layout.fillWidth: true

            Repeater {
                model: players
                delegate: TabButton {
                    text: properties_role.name
                }
            }
        }

        Button {
            id: button
            text: qsTr("Add player")
            onClicked: players.addPlayer()
        }

        Button {
            id: button1
            text: qsTr("Remove player")
            onClicked: players.removePlayerIndex(view.currentIndex)
        }
    }
}
