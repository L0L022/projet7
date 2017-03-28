import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import Projet7 1.0

Item {
    id: item

    property string propertyKey: ""
    property string propertyValue: ""
    property string inputValue: ""

    onPropertyKeyChanged: update()

    function update() {
        if(propertyValue !== ItemRole.properties[propertyKey]) {
            if (inputValue === propertyValue)
                inputValue = ItemRole.properties[propertyKey]
            propertyValue = ItemRole.properties[propertyKey]
        }
    }

    function set() {
        ItemRole.setProperty(propertyKey, inputValue);
    }

    function reset() {
        inputValue = propertyValue
    }

    Connections {
        target: ItemRole
        onPropertiesChanged: update()
    }
}
