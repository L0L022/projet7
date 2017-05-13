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
            text: "Joueur associé"
        }

        ComboBox {
            id: clientsCombo
            Layout.fillWidth: true
            model: app.currentGame.clients()
            textRole: "nameRole"
            onActivated: app.currentGame.clients().setId(index, propertyRole.id)

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
            text: "Droits de lecture"
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
                text: "Ajouter"
                onClicked: propertyRole.addReadRight(players.get(readPlayerId.currentIndex)["id"])
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
                    text: "Supprimer"
                    onClicked: propertyRole.removeReadRight(index)
                }
            }
        }

        Label {
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
            text: "Droits d'écriture"
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
                text: "Ajouter"
                onClicked: propertyRole.addWriteRight(players.get(writePlayerId.currentIndex)["id"])
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
                    text: "Supprimer"
                    onClicked: propertyRole.removeWriteRight(index)
                }
            }
        }
    }
}
