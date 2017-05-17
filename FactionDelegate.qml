import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import Projet7 1.0

Flickable {
    id: item
    contentHeight: layout.implicitHeight

    GridLayout {
        id: layout
        width: item.width

        Image {
            Layout.row: 0
            Layout.column: 0
            Layout.rowSpan: 2
            Layout.fillHeight: true
            source: Projet7.factions[modelIndex].image
            fillMode: Image.PreserveAspectFit
        }

        Label {
            Layout.row: 0
            Layout.column: 1
            Layout.fillWidth: true
            Layout.fillHeight: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: Projet7.factions[modelIndex].name
        }

        Label {
            Layout.row: 2
            Layout.column: 0
            Layout.columnSpan: 2
            Layout.fillWidth: true
            text: Projet7.factions[modelIndex].description
            wrapMode: Text.Wrap
        }
        
        Button {
            Layout.fillWidth: true
            //visible: app.currentGame.type === Game.ClientGame
            text: qsTr("Choose this one")
            onClicked: stack.push("qrc:///CharactersView.qml", {"faction": modelIndex})
        }
    }
}
