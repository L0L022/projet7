import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import Projet7 1.0


Item {
    id: moidialog
    readonly property string title: "Édition des stats"
    property var item_role
    property var additions_role

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 6

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
                    onClicked: stack.push("qrc:///EditProperty.qml", {"item_role": item_role, "additions_role": additions_role})
                }

                Button {
                    text: "Supprimer"
                    onClicked: additions_role.removeOne(id_role)
                }
            }
        }

        RowLayout {

            function addProperty() {
                if(textFieldNom.text !== "") {
                    var addition = additions_role.append()
                    addition.setProperty("name", textFieldNom.text)
                    textFieldNom.text = ""
                }
            }

            TextField {
                id: textFieldNom
                Layout.fillWidth: true
                placeholderText: "Nom de la nouvelle statistique"
                onAccepted: parent.addProperty()
            }

            Button {
                id: superButon
                text: "Ajouter"
                onClicked: parent.addProperty()
            }
        }
    }
}
