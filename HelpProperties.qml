import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import me 1.0

Item {
    id: item

    property string propertyKey: ""
    property string propertyValue: ""
    property string inputValue: ""

    onPropertyKeyChanged: update()

    function update() {
        if (inputValue === propertyValue)
            inputValue = properties_role[propertyKey]
        propertyValue = properties_role[propertyKey]
    }

    function set() {
        item_role.setProperty(propertyKey, inputValue)
    }

    function reset() {
        inputValue = propertyValue
    }

    Connections {
        target: item_role
        onPropertyChanged: {
            if(key === propertyKey)
                update()
        }
    }
}
