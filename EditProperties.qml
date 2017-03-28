import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import Projet7 1.0


Item {
    id: moidialog
    readonly property string title: "Édition des stats"
    property var itemRole
    property var additionsRole

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 6

        ListView {
            clip: true
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: additionsRole
            delegate: RowLayout {
                width: parent.width
                Label {
                    text: PropertiesRole.name
                    Layout.fillWidth: true
                }

                Button {
                    text: "Éditer"
                    onClicked: stack.push("qrc:///EditProperty.qml", {"itemRole": itemRole, "additionsRole": additionsRole})
                }

                Button {
                    text: "Supprimer"
                    onClicked: additionsRole.removeOne(id_role)
                }
            }
        }

        RowLayout {

            function addProperty() {
                if(textFieldNom.text !== "") {
                    var addition = additionsRole.append()
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
