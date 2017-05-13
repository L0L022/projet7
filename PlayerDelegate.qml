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
                model: ["name", "faction", "image", "description"]
                delegate: RowLayout {
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
