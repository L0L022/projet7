import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import me 1.0

Dialog {
    title: "edit property : " + id_role
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    width: 400
    height: 400

    ColumnLayout {
        anchors.fill: parent
    ListView {
        Layout.fillHeight: true
        Layout.fillWidth: true
        model: Object.keys(properties_role)
        delegate: RowLayout {
            Label {
                text: modelData
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
                text: "reset"
                onClicked: superhelp.reset()
            }

            Button {
                text: "remove"
                onClicked: item_role.removeProperty(modelData)
            }
        }
    }
    RowLayout {
        TextField {
            id: new_key_field
            placeholderText: "new key name"
        }
        Button {
            text: "add key"
            onClicked: item_role.setProperty(new_key_field.text, "")
        }
    }
}
}
