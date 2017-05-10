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

        Button {
            Layout.fillWidth: true
            text: "Ouvrir la liste des joueurs"
            onClicked: stack.push("qrc:///PlayersView.qml")
        }

        Button {
            Layout.fillWidth: true
            text: "Lancer un dé"
            onClicked: stack.push("qrc:///DieView.qml")
        }

        Button {
            Layout.fillWidth: true
            text: "Terminer la partie"
            onClicked: app.closeCurrentGame()
        }
    }
}
