import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import Projet7 1.0

Item {
    width: textField.implicitWidth
    height: textField.implicitHeight

    property string key: ""
    onKeyChanged: textField.update()

    property bool showResetButton: true
    property alias placeholderText: textField.placeholderText
    property alias inTextField: textField.activeFocus

    Connections {
        target: propertyRole
        onPropertiesChanged: textField.update()
    }

    RowLayout {
        anchors.fill: parent

        TextField {
            id: textField

            property string lastPropertyValue: ""

            Layout.fillWidth: true
            onAccepted: propertyRole.setProperty(key, text)
            selectByMouse: true
            color: text === lastPropertyValue ? "#08FF00" : "#FFE100"

            function update() {
                if (textField.lastPropertyValue !== propertiesRole[key]) {
                    if (textField.text === textField.lastPropertyValue || textField.txt === "")
                        textField.text = propertiesRole[key]
                    textField.lastPropertyValue = propertiesRole[key]
                }
            }
        }

        Button {
            text: "↶"
            font.pointSize: 50
            implicitWidth: height
            implicitHeight: textField.height
            flat: true
            onClicked: textField.text = propertiesRole[key]
            visible: showResetButton && textField.text !== textField.lastPropertyValue
        }
    }
}
