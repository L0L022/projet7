import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import me 1.0

Item {
    id: item
    property var item_role
    property var additions_role
    readonly property string title: "Édition de : " + item_role.properties.name

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 6

        ListView {
            clip: true
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: Object.keys(item_role.properties)
            delegate: GridLayout {
                width: parent.width
                columns: item.width > item.height ? 4 : 2

                Label {
                    text: modelData
                    Layout.fillWidth: true
                }

                HelpProperties {
                    id: superhelp
                    propertyKey: modelData
                }

                TextField {
                    text: superhelp.inputValue
                    onTextChanged: superhelp.inputValue = text
                    color: text === superhelp.propertyValue ? "green" : "orange"
                    onAccepted: superhelp.set()
                }

                Button {
                    text: "Réinitialisation"
                    onClicked: superhelp.reset()
                }

                Button {
                    text: "Supprimer"
                    onClicked: item_role.removeProperty(modelData)
                }
            }
        }

        RowLayout {

            function addKey() {
                if(new_key_field.text !== "") {
                    item_role.setProperty(new_key_field.text, "")
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
