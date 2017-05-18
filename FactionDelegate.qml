import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import Projet7 1.0

Flickable {
    id: item
    contentHeight: layout.implicitHeight

    ColumnLayout {
        id: layout
        width: item.width

        Label {
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: Projet7.factions[modelIndex].name
        }

        Label {
            Layout.fillWidth: true
            text: Projet7.factions[modelIndex].description
            wrapMode: Text.Wrap
        }

        Label {
            Layout.fillWidth: true
            text: qsTr("CP: ") + Projet7.factions[modelIndex].cp
            wrapMode: Text.Wrap
        }
        
        Button {
            Layout.fillWidth: true
            visible: app.currentGame.type === Game.ClientGame
            text: qsTr("Choose this one")
            onClicked: stack.push("qrc:///CharactersView.qml", {"faction": modelIndex})
        }
    }
}
