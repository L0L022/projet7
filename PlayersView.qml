import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

import Projet7 1.0

Item {
    readonly property string title: "Joueurs"

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
                delegate: PlayerDelegate {
                    height: view.height
                    width: view.width
                }
            }
        }

        GridLayout {
            flow: parent.width > parent.height ? GridLayout.LeftToRight : GridLayout.TopToBottom
            TabBar {
                id: bar
                Layout.fillWidth: true
                clip: true

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
                text: qsTr("Ajouter un joueur")
                onClicked: {
                    app.currentGame.players().append()
                    bar.currentIndex = view.count - 1
                }
            }

            Button {
                Layout.fillWidth: parent.flow === GridLayout.TopToBottom
                text: qsTr("Supprimer un joueur")
                onClicked: app.currentGame.players().removeAt(view.currentIndex)
            }
        }
    }
}
