import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0

Item {
    id: item1
    height: 200
    width: 400

    Column {
        TextField {
            id: name
            text: properties["name"]
        }
        TextField {
            id: calling
            text: properties["calling"]
        }
        SpinBox {
            id: age
            value: properties["age"]
        }
        SpinBox {
            id: height_
            value: properties["height"]
        }
    }

    Button {
        id: button
        text: qsTr("Appliquer")
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        onClicked: {
            var _name = name.text, _calling = calling.text, _age = age.value, _height = height_.value;
            playerModel.addProperty(properties["id"], "name", _name);
            playerModel.addProperty(properties["id"], "age", _age);
            playerModel.addProperty(properties["id"], "calling", _calling);
            playerModel.addProperty(properties["id"], "height", _height);
        }
    }

    GridView {
        x: 206
        y: 0
        width: 194
        height: 160
        cellWidth: 90; cellHeight: 90
        model: playerModel.getAdditions(properties["id"])
        delegate: Text {
            text: properties_a["name"]
        }
    }
}
