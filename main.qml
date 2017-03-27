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
    title: qsTr("Projet7")

    header: ToolBar {
        RowLayout {
          anchors.fill: parent
          ToolButton {
              text: qsTr("‹")
              onClicked: stack.pop()
              visible: stack.depth > 1

          }
          Label {
              text: stack.currentItem.title
              elide: Label.ElideRight
              horizontalAlignment: Qt.AlignHCenter
              verticalAlignment: Qt.AlignVCenter
              Layout.fillWidth: true
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

    StackView {
        id: stack
        initialItem: mainView
        anchors.fill: parent
        Keys.onBackPressed: {
            if(depth > 1)
                pop()
            else
                applicationWindow.close()
        }
    }

    Component {
        id: mainView
        Item {
            readonly property string title: "Projet7"

            Component {
                id: fileGame

                ColumnLayout {
                    readonly property string title: "Nouvelle partie"

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
                                stack.replace("qrc:///Game.qml")
                            }
                        }
                    }
                }
            }

            Component {
                id: networkGame

                ColumnLayout {
                    readonly property string title: "Se connecter"

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
                            to: 9999
                        }
                    }

                    Button {
                        Layout.fillWidth: true
                        text: "Connection"
                        onClicked: {
                            if(ipField.text !== "" && portSpin.value !== 0) {
                                app.loadNetworkGame(ipField.text, portSpin.value)
                                stack.replace("qrc:///Game.qml")
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


                    delegate: ItemDelegate {
                        width: parent.width
                        text: NameRole + " at " + LocationRole
                        onClicked: {
                            app.loadAvailableGame(index)
                            stack.push("qrc:///Game.qml")
                        }
                    }
                }

                Button {
                    text: "Ouvrir la partie en cours"
                    visible: app.currentGame !== null
                    onClicked: stack.push("qrc:///Game.qml")
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
