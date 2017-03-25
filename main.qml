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
        initialItem: "qrc:///Players.qml"
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

            ColumnLayout {
                anchors.fill: parent

                Button {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter
                    text: "Commencer une nouvelle partie"
                }

                Button {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter
                    text: "Charger une partie sauvegardée"
                    onClicked: app.refreshSavedGame()
                }

                Button {
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter
                    text: "Se connecter à une partie"
                }
            }
        }
    }
}
