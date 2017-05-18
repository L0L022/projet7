import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

import Projet7 1.0

Item {
    readonly property string title: qsTr("Players")

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 6

        StackLayout {
            id: view
            currentIndex: bar.currentIndex
            Layout.fillHeight: true
            Layout.fillWidth: true

            Repeater {
                model: app.currentGame.players()
                delegate: Component {
                    Loader {
                        active: bar.currentIndex === index
                        sourceComponent: PlayerDelegate {
                            height: view.height
                            width: view.width
                        }
                    }
                }
            }
        }

        GridLayout {
            flow: parent.width > parent.height ? GridLayout.LeftToRight : GridLayout.TopToBottom
            TabBar {
                id: bar
                Layout.fillWidth: true
                clip: true
                visible: bar.count > 1 || app.currentGame.type === Game.ServerGame

                Repeater {
                    model: app.currentGame.players()
                    delegate: TabButton {
                        width: 100
                        text: propertiesRole.name
                    }
                }
            }

            Button {
                Layout.fillWidth: parent.flow === GridLayout.TopToBottom
                text: qsTr("Add a player")
                visible: app.currentGame.type === Game.ServerGame
                onClicked: {
                    app.currentGame.players().append()
                    bar.currentIndex = view.count - 1
                }
            }

            Button {
                Layout.fillWidth: parent.flow === GridLayout.TopToBottom
                text: qsTr("Remove a player")
                onClicked: {
                    app.currentGame.players().removeAt(view.currentIndex)
                    if (bar.currentIndex === -1)
                        bar.currentIndex = 0
                }
            }
        }
    }
}
