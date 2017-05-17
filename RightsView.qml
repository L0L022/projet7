import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import Projet7 1.0

Flickable {
    id: item
    readonly property string title: qsTr("Rights")
    property var propertyRole
    contentHeight: column.implicitHeight

    ColumnLayout {
        id: column
        width: item.width

        Label {
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("Associated player")
        }

        ComboBox {
            id: clientsCombo
            Layout.fillWidth: true
            model: app.currentGame.clients()
            textRole: "nameRole"
            onActivated: app.currentGame.clients().setId(index, propertyRole.id)
            visible: app.currentGame.type === Game.ServerGame

            Connections {
                target: app.currentGame.clients()
                onDataChanged: clientsCombo.currentIndex = app.currentGame.clients().idToIndex(propertyRole.id)
            }
        }

        ListModel {
            id: players
            Component.onCompleted: update()

            function update() {
                clear()
                for (var i = 0; i < app.currentGame.players().rowCount(); ++i)
                    append(app.currentGame.players().at(i).properties)
            }
        }

        Connections {
            target: app.currentGame.players()
            onRowsInserted: players.update()
            onRowsRemoved: players.update()
            onModelReset: players.update()
            onDataChanged: players.update()
        }

        Label {
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("Read rights")
        }

        RowLayout {
            Layout.fillWidth: true

            ComboBox {
                Layout.fillWidth: true
                id: readPlayerId
                model: players
                textRole: "name"
                onCountChanged: currentIndex = 0
            }

            Button {
                text: qsTr("Add")
                onClicked: propertyRole.addReadRight(players.get(readPlayerId.currentIndex)["id"])
                visible: app.currentGame.type === Game.ServerGame
            }
        }

        Repeater {
            Layout.fillWidth: true
            model: Object.keys(propertyRole.readRights)
            delegate: RowLayout {
                width: parent.width

                Label {
                    Layout.fillWidth: true
                    text: app.currentGame.players().get(propertyRole.readRights[modelData]).properties["name"]
                }

                Button {
                    text: qsTr("Remove")
                    onClicked: propertyRole.removeReadRight(index)
                    visible: app.currentGame.type === Game.ServerGame
                }
            }
        }

        Label {
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("Write rights")
        }

        RowLayout {
            Layout.fillWidth: true

            ComboBox {
                Layout.fillWidth: true
                id: writePlayerId
                model: players
                textRole: "name"
                onCountChanged: currentIndex = 0
            }

            Button {
                text: qsTr("Add")
                onClicked: propertyRole.addWriteRight(players.get(writePlayerId.currentIndex)["id"])
                visible: app.currentGame.type === Game.ServerGame
            }
        }

        Repeater {
            Layout.fillWidth: true
            model: Object.keys(propertyRole.writeRights)
            delegate: RowLayout {
                width: parent.width

                Label {
                    Layout.fillWidth: true
                    text: app.currentGame.players().get(propertyRole.writeRights[modelData]).properties["name"]
                }

                Button {
                    text: qsTr("Remove")
                    onClicked: propertyRole.removeWriteRight(index)
                    visible: app.currentGame.type === Game.ServerGame
                }
            }
        }
    }
}
