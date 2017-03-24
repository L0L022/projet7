import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import me 1.0


Item {
    id: moidialog
    readonly property string title: "Édition des stats"
    property var item_role
    property var properties_role
    property var additions_role

    ColumnLayout {
        anchors.fill: parent

        ListView {
            clip: true
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: additions_role
            delegate: RowLayout {
                width: parent.width
                Label {
                    text: properties_role.name
                    Layout.fillWidth: true
                }

                Button {
                    text: "Éditer"
                    onClicked: stack.push("qrc:///EditProperty.qml", {"item_role": item_role, "properties_role": properties_role, "additions_role": additions_role})
                }

                Button {
                    text: "Supprimer"
                    onClicked: additions_role.removeOne(id_role)
                }
            }
        }

        RowLayout {

            TextField {
                id: textFieldNom
                Layout.fillWidth: true
                placeholderText: "Nom de la statistique"
            }

            Button {
                text: "Ajouter"
                onClicked: {
                    if(textFieldNom.text !== "") {
                        var addition = additions_role.append()
                        addition.setProperty("name", textFieldNom.text)
                    }
                }
            }
        }
    }
}
