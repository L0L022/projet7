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

    Connections {
        target: app
        onCurrentGameChanged: {
            if(app.currentGame !== null)
                stack.push("qrc:///Game.qml")
        }
    }

    Component {
        id: mainView
        Item {
            readonly property string title: "Projet7"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 6

                ListView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: app.availableGames()
                    Component.onCompleted: app.refreshAvailableGames()
                    delegate: ItemDelegate {
                        width: parent.width
                        text: NameRole + " at " + LocationRole
                        onClicked: app.startGame(index)
                    }
                }

                TextField {
                    id: nameField
                    placeholderText: "fichier ou ip"
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter
                }

                TextField {
                    id: portFiel
                    placeholderText: "port"
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter
                }

                Button {
                    text: "Ouvre la partie en cour"
                    visible: app.currentGame !== null
                    onClicked: stack.push("qrc:///Game.qml")
                }

                Button {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter
                    text: "Commencer une nouvelle partie ou charger une partie existante"
                    onClicked: app.startNewGame(nameField.text)
                }

                Button {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter
                    text: "Se connecter à une partie"
                    onClicked: app.loadExistGame(nameField.text, portFiel.text)
                }
            }
        }
    }
}
