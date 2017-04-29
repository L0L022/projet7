import QtQuick 2.7
//import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import Projet7 1.0

Item {
    id: item
    property var propertyRole
    readonly property string title: "Édition de : " + propertyRole.properties.name

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 6

        ListView {
            clip: true
            Layout.fillHeight: true
            Layout.fillWidth: true
            spacing: 3
            model: Object.keys(propertyRole.properties)
            delegate: GridLayout {
                width: parent.width
                columns: item.width > item.height ? 4 : 2

                Label {
                    text: modelData
                    Layout.fillWidth: true
                }

                PropertyField {
                    key: modelData
                    property var propertiesRole: propertyRole.properties
                }

                Button {
                    text: "Supprimer"
                    onClicked: propertyRole.removeProperty(modelData)
                }
            }
        }

        RowLayout {

            function addKey() {
                if(new_key_field.text !== "") {
                    propertyRole.setProperty(new_key_field.text, "")
                }
            }

            TextField {
                id: new_key_field
                placeholderText: "Nom de la nouvelle proriété"
                Layout.fillWidth: true
                onAccepted: parent.addKey()
            }

            Button {
                text: "Ajouter une propriété"
                onClicked: parent.addKey()
            }
        }
    }
}
