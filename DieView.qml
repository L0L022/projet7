import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import Projet7 1.0

Item {
    readonly property string title: "Lancé de dé"

    ColumnLayout {
        anchors.fill: parent

        Label {
            Layout.fillWidth: true
            Layout.fillHeight: true
            id: number
            text: "0"
            font.pointSize: 400
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.weight: Font.Black
            fontSizeMode: Text.Fit
        }

        Timer {
            id: timer
            interval: 5000
            onTriggered: number.text = "0"
        }

        RowLayout {
            Layout.fillWidth: true

            Label {
                Layout.fillWidth: true
                text: "Nombre de face"
            }

            SpinBox {
                id: face
                value: 6
                editable: true
            }
        }

        Button {
            Layout.fillWidth: true
            text: "Lancer le dé !"
            onClicked: {
                number.text = Projet7.die(face.value)
                timer.start()
            }
        }
    }
}
