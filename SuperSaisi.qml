import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import Projet7 1.0

Item {
    id: rectangle
    width: 275
    height: 53
    Layout.fillWidth: true

    property string key: ""
    property string key_name: ""

    onKeyChanged: update()

    function update() {
        if (superText.right_value !== PropertiesRole[key]) {
            if (superText.text === superText.right_value || superText.txt === "")
                superText.text = PropertiesRole[key]
            superText.right_value = PropertiesRole[key]
        }
    }

    Connections {
        target: ItemRole
        onPropertiesChanged: update()
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 6

        Label {
            text: qsTr(key_name+" :")
        }

        TextField {
            id: superText
            onAccepted: ItemRole.setProperty(key, text)
            Layout.fillWidth: true
            selectByMouse: true
            color: text === right_value ? "green" : "orange"

            property string right_value: ""
        }

        Button {
            text: "Réinitialisation"
            onClicked: superText.text = PropertiesRole[key]
        }
    }
}
