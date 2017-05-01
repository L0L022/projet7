import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import Projet7 1.0

Item {
    id: item
    readonly property string title: app.currentGame !== null ? app.currentGame.name : ""

    Connections {
        target: app
        onCurrentGameChanged: {
            if(app.currentGame === null)
                stack.pop()
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 6

        Dialog {
            id: dialogError
            x: (item.width - width) / 2
            y: (item.height - height) / 2
            title: "Une erreur est survenue"
            standardButtons: Dialog.Ok
            onClosed: app.closeCurrentGame()

            Label {
                id: labelError
            }
        }

        Connections {
            target: app.currentGame
            onError: {
                labelError.text = errorString
                dialogError.open()
            }
        }

        TextField {
            Layout.fillWidth: true
            text: app.currentGame !== null ? app.currentGame.name : ""
            onAccepted: app.currentGame.name = text
        }

        Label {
            Layout.fillWidth: true
            text: app.currentGame !== null ? "Adresse ip : " + app.currentGame.ipAddress + ":" + app.currentGame.port : ""
        }

        Loader {
            visible: active
            Layout.fillWidth: true
            Layout.fillHeight: true
            sourceComponent: serverComponent
            active: app.currentGame.type === Game.ServerGame
        }

        Component {
            id: serverComponent

            ColumnLayout {

                Label {
                    Layout.fillWidth: true
                    text: "Nom du joueur -> Id Joueur"
                }

                ListView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    clip: true
                    model: app.currentGame.clients()

                    delegate: RowLayout {
                        width: parent.width

                        Label {
                            Layout.fillWidth: true
                            text: nameRole
                        }

                        TextField {
                            text: idRole
                            onAccepted: app.currentGame.clients().setId(index, text)
                        }
                    }
                }
            }
        }

        Button {
            Layout.fillWidth: true
            text: "Ouvrir la liste des joueurs"
            onClicked: stack.push("qrc:///PlayersView.qml")
        }

        Button {
            Layout.fillWidth: true
            text: "Terminer la partie"
            onClicked: app.closeCurrentGame()
        }
    }
}
