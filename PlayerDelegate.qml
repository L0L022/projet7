import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import Projet7 1.0

Flickable {
    id: item
    contentHeight: columnLayout.implicitHeight
    clip: true

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        Button {
            Layout.fillWidth: true
            text: app.currentGame.type === Game.ServerGame ? qsTr("Edit rights") : qsTr("View rights")
            onClicked: stack.push("qrc:///RightsView.qml", {"propertyRole": propertyRole})
        }

        ColumnLayout {
            Layout.fillWidth: true

            Repeater {
                model: ["intelligence", "instinct", "combativeness", "relational", "cohesion", "treasury", "population"]
                delegate: ColumnLayout {
                    Label {
                        Layout.fillWidth: true
                        text: modelData
                        font.capitalization: Font.Capitalize
                        horizontalAlignment: Text.AlignHCenter
                    }

                    PropertyField {
                        Layout.fillWidth: true
                        key: modelData
                        placeholderText: modelData
                    }
                }
            }
        }
    }
}
