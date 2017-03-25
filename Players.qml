import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

import me 1.0

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
                model: players
                delegate: NewPlayerView {
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
                    model: players
                    delegate: TabButton {
                        width: 100
                        text: properties_role.name
                    }
                }
            }

            Button {
                Layout.fillWidth: parent.flow === GridLayout.TopToBottom
                text: qsTr("Ajouter un joueur")
                onClicked: {
                    players.append()
                    bar.currentIndex = view.count - 1
                }
            }

            Button {
                Layout.fillWidth: parent.flow === GridLayout.TopToBottom
                text: qsTr("Supprimer un joueur")
                onClicked: players.removeAt(view.currentIndex)
            }
        }
    }
}
