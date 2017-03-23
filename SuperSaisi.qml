import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import me 1.0

Rectangle {
    id: rectangle
    width: 275
    height: 53
    Layout.fillWidth: true

    property string key: ""
    property string key_name: ""
    //property QtObject name: value

    onKeyChanged: update()

    function update() {
        if (superText.text === superText.right_value || superText.txt === "")
            superText.text = properties_role[key]
        superText.right_value = properties_role[key]
    }

    Connections {
        target: item_role
        onPropertyChanged: {
            if(key === rectangle.key)
                update()
        }
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 6

        Label {
            text: qsTr(key_name+" :")
        }

        TextField {
            id: superText
            onAccepted: item_role.setProperty(key, text)
            Layout.fillWidth: true
            selectByMouse: true
            color: text === right_value ? "green" : "orange"

            property string right_value: ""
        }

        Button {
            text: "Réinitialisation"
            onClicked: superText.text = properties_role[key]
        }
    }
}
