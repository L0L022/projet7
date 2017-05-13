import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import Projet7 1.0

Item {
    id: item
    property var character
    property var faction

    GridLayout {
        anchors.fill: parent

        Image {
            Layout.row: 0
            Layout.column: 0
            Layout.rowSpan: 2
            Layout.fillWidth: true
            Layout.fillHeight: true
            source: character.image
            fillMode: Image.PreserveAspectFit
        }

        Label {
            Layout.row: 0
            Layout.column: 1
            text: character.name
        }

        Label {
            Layout.row: 1
            Layout.column: 1
            text: faction.name
        }

        Label {
            Layout.row: 2
            Layout.column: 0
            Layout.columnSpan: 2
            text: character.description
        }

        Button {
             Layout.row: 3
             Layout.column: 0
             Layout.columnSpan: 2
             //visible: app.currentGame.type === Game.ClientGame
             text: qsTr("Choose this one")
             onClicked: {
                 var player = app.currentGame.players().append();
                 player.properties = character;
                 stack.replace(stack.find(function(item, index) {
                     return item.objectName === "UniverseView";
                 }), Qt.resolvedUrl("qrc:///PlayersView.qml"), {}, StackView.Transition);
             }
         }
    }
}
