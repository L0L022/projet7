import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

import Projet7 1.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Project 7")

    header: ToolBar {
        Label {
            anchors.centerIn: parent
            text: stack.currentItem.title
            elide: Label.ElideRight
        }

        RowLayout {
            anchors.fill: parent
            ToolButton {
              text: qsTr("‹")
              onClicked: stack.pop()
              visible: stack.depth > 1
            }
        }
    }

    Frame {
        anchors.fill: parent
        contentItem: StackView {
            id: stack
            clip: true
            initialItem: mainView
            Keys.onBackPressed: {
                if(depth === 1)
                    stack.clear()
                else
                    stack.pop()
            }

            onDepthChanged: {
                if(depth === 0)
                    applicationWindow.close()
            }
        }
    }

    Connections {
        target: app
        onCurrentGameChanged: {
            if (app.currentGame === null)
                stack.pop(null)
        }
    }

    Component {
        id: mainView

        Item {
            readonly property string title: applicationWindow.title

            StackView.onActivated: {
                app.refreshNetworkGames()
                app.refreshFileGames()
            }

            Component {
                id: fileGame

                Item {
                    readonly property string title: qsTr("Begin a new game")

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 6

                        TextField {
                            id: newGameName
                            Layout.fillWidth: true
                            placeholderText: qsTr("The game's name")
                            onAccepted: parent.newgame()
                        }

                        Button {
                            Layout.fillWidth: true
                            text: qsTr("Make the game")
                            onClicked: parent.newgame()
                        }

                        function newgame() {
                            if(newGameName.text !== "") {
                                app.newFileGame(newGameName.text)
                                stack.replace("qrc:///GameView.qml")
                            }
                        }
                    }
                }
            }

            Component {
                id: networkGame

                Item {
                    readonly property string title: qsTr("Connect to a game")

                ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 6

                        RowLayout {
                            Layout.fillWidth: true

                            Label {
                                Layout.fillWidth: true
                                text: qsTr("IP address")
                            }

                            TextField {
                                id: ipField
                                Layout.fillWidth: true
                                onAccepted: portSpin.focus = true
                            }
                        }

                        RowLayout {
                            Layout.fillWidth: true

                            Label {
                                Layout.fillWidth: true
                                text: qsTr("Port")
                            }

                            SpinBox {
                                id: portSpin
                                Layout.fillWidth: true
                                editable: true
                                to: 65535
                                value: Projet7.portGame
                            }
                        }

                        Button {
                            Layout.fillWidth: true
                            text: qsTr("Connection")
                            onClicked: parent.connectgame()
                        }

                        function connectgame() {
                            if(ipField.text !== "" && portSpin.value !== 0) {
                                app.loadNetworkGame(ipField.text, portSpin.value)
                                stack.replace("qrc:///GameView.qml")
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
                            text: typeRole === GameItem.FileGame ? nameRole : nameRole + " at " + locationRole
                            onClicked: {
                                app.loadAvailableGame(index)
                                stack.push("qrc:///GameView.qml")
                            }
                        }

                        Button {
                            visible: typeRole === GameItem.FileGame
                            text: qsTr("Remove")
                            onClicked: app.removeAvailableGame(index)
                        }
                    }
                }

                Button {
                    Layout.fillWidth: true
                    visible: app.currentGame !== null
                    text: qsTr("Open the current game")
                    onClicked: stack.push("qrc:///GameView.qml")
                }

                Button {
                    Layout.fillWidth: true
                    text: qsTr("Begin a new game")
                    onClicked: stack.push(fileGame)
                }

                Button {
                    Layout.fillWidth: true
                    text: qsTr("Connect to a game")
                    onClicked: stack.push(networkGame)
                }
            }
        }
    }
}
