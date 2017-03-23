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
    }

    Component {
        id: mainView

        Item {
            readonly property string title: "Projet7"
            StackLayout {
                id: view
                anchors.bottom: rowLayout.top
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.top: parent.top
                currentIndex: bar.currentIndex

                Repeater {
                    model: players
                    delegate: NewPlayerView {
                        height: view.height
                        width: view.width
                    }
                }
            }

            RowLayout {
                id: rowLayout
                anchors.leftMargin: 6
                anchors.bottomMargin: 6
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 6

                TabBar {
                    id: bar
                    Layout.fillWidth: true

                    Repeater {
                        model: players
                        delegate: TabButton {
                            width: 100
                            text: properties_role.name
                        }
                    }
                }

                Button {
                    text: qsTr("Ajouter un joueur")
                    onClicked: players.addPlayer()
                }

                Button {
                    text: qsTr("Supprimer un joueur")
                    onClicked: players.removePlayerIndex(view.currentIndex)
                }
            }
        }
    }
}
