import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

import Projet7 1.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Projet7")

    header: ToolBar {
        Label {
            anchors.centerIn: parent
            text: stack.currentItem.title
            elide: Label.ElideRight
        }

        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 5
            ToolButton {
              text: qsTr("‹")
              onClicked: stack.pop()
              visible: stack.depth > 1
            }
        }
    }

    Connections {
        target: app
        onCurrentGameChanged: {
            app.refreshNetworkGames()
            app.refreshFileGames()
        }
    }

    Frame {
        anchors.fill: parent
        contentItem: StackView {
            id: stack
            clip: true
            initialItem: mainView
            Keys.onBackPressed: {
                if(depth > 1)
                    pop()
                else
                    applicationWindow.close()
            }
        }
    }

    Component {
        id: mainView
        Item {
            readonly property string title: "Projet7"

            Component {
                id: fileGame

                Item {
                    readonly property string title: "Nouvelle partie"

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 6

                        TextField {
                            Layout.fillWidth: true
                            id: newGameName
                            placeholderText: "Nom de la nouvelle partie"
                        }

                        Button {
                            Layout.fillWidth: true
                            text: "Créer la partie"
                            onClicked: {
                                if(newGameName.text !== "") {
                                    app.newFileGame(newGameName.text)
                                    stack.replace("qrc:///GameView.qml")
                                }
                            }
                        }
                    }
                }
            }

            Component {
                id: networkGame

                Item {
                    readonly property string title: "Se connecter"

                ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 6

                        TextField {
                            id: ipField
                            placeholderText: "Addresse ip"
                            Layout.fillWidth: true
                        }

                        RowLayout {

                            Label {
                                Layout.fillWidth: true
                                text: "Port"
                            }

                            SpinBox {
                                Layout.fillWidth: true
                                id: portSpin
                                editable: true
                                to: 999999
                                value: Projet7.portGame
                            }
                        }

                        Button {
                            Layout.fillWidth: true
                            text: "Connexion"
                            onClicked: {
                                if(ipField.text !== "" && portSpin.value !== 0) {
                                    app.loadNetworkGame(ipField.text, portSpin.value)
                                    stack.replace("qrc:///GameView.qml")
                                }
                            }
                        }
                    }
                }
            }

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 6

                ListView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: app.availableGames()
                    Component.onCompleted: {
                        app.refreshNetworkGames()
                        app.refreshFileGames()
                    }


                    delegate: RowLayout {
                        width: parent.width

                        ItemDelegate {
                            Layout.fillWidth: true
                            text: nameRole + " at " + locationRole
                            onClicked: {
                                app.loadAvailableGame(index)
                                stack.push("qrc:///GameView.qml")
                            }
                        }

                        Button {
                            visible: typeRole === GameItem.FileGame
                            text: "Supprimer"
                            onClicked: app.removeAvailableGame(index)
                        }
                    }
                }

                Button {
                    text: "Ouvrir la partie en cours"
                    visible: app.currentGame !== null
                    onClicked: stack.push("qrc:///GameView.qml")
                    Layout.fillWidth: true
                }

                Button {
                    Layout.fillWidth: true
                    text: "Commencer une nouvelle partie"
                    onClicked: stack.push(fileGame)

                }

                Button {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter
                    text: "Se connecter à une partie"
                    onClicked: stack.push(networkGame)
                }
            }
        }
    }
}
