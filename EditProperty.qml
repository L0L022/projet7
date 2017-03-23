import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import me 1.0

Item {
    readonly property string title: "Édition de : " + properties_role.name
    property var item_role
    property var properties_role
    property var additions_role

    ColumnLayout {
        anchors.fill: parent

        ListView {
            clip: true
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: Object.keys(properties_role)
            delegate: RowLayout {
                width: parent.width

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
            TextField {
                id: new_key_field
                placeholderText: "Nom de la proriété"
                Layout.fillWidth: true
            }

            Button {
                text: "Ajouter une propriété"
                onClicked: item_role.setProperty(new_key_field.text, "")
            }
        }
    }
}
