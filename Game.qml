import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import me 1.0

Item {
    id: item
    readonly property string title: app.currentGame.name

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
            onClosed: app.closeGame()

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
            text: app.currentGame.name
            onAccepted: app.currentGame.name = text
        }

        Label {
            text: "Ip address : " + app.currentGame.ipAddress + ":" + app.currentGame.port
        }

        TextField {
            placeholderText: "envoi un truc sur le réseau"
            onAccepted: app.say_something(text)
        }

        Button {
            text: "Open players"
            onClicked: stack.push("qrc:///Players.qml")
        }

        Button {
            text: "Termine la partie"
            onClicked: app.closeGame()
        }
    }
}
