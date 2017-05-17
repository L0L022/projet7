import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import Projet7 1.0

Item {
    id: item
    property var character: Projet7.makeCharacteristics(faction)

    ColumnLayout {
        anchors.fill: parent

        Repeater {
            model: ["intelligence", "instinct", "combativeness", "relational", "cohesion", "treasury", "population"]
            delegate: Label {
                Layout.fillWidth: true
                Layout.leftMargin: 10
                text: modelData + ": " + character[modelData]
                font.capitalization: Font.Capitalize
            }
        }

        Button {
            Layout.fillWidth: true
            //visible: app.currentGame.type === Game.ClientGame
            text: qsTr("Choose this one")
            onClicked: {
                 var player = app.currentGame.players().append();
                 player.properties = character;
                 player.setProperty("name", Projet7.userName);
                 stack.replace(stack.find(function(item, index) {
                     return item.objectName === "FactionsView";
                 }), Qt.resolvedUrl("qrc:///PlayersView.qml"), {}, StackView.Transition);
            }
         }
    }
}
