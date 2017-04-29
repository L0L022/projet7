import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import Projet7 1.0

Item {
    id: item
    readonly property string title: "Édition des sous propriétées"
    property var propertyRole

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 6

        ListView {
            clip: true
            Layout.fillHeight: true
            Layout.fillWidth: true
            spacing: 3
            model: propertyRole.subProperties()
            delegate: RowLayout {
                width: parent.width
                Label {
                    text: propertiesRole.name
                    Layout.fillWidth: true
                }

                Button {
                    text: "Éditer"
                    onClicked: stack.push("qrc:///PropertyDelegate.qml", {"propertyRole": propertyRole})
                }

                Button {
                    text: "Supprimer"
                    onClicked: item.propertyRole.subProperties().removeOne(idRole)
                }
            }
        }

        RowLayout {

            function addProperty() {
                if(textFieldNom.text !== "") {
                    var addition = propertyRole.append()
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
