import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import Projet7 1.0

Flickable {
    id: item
    readonly property string title: qsTr("Map")
    contentHeight: image.height
    contentWidth: image.width

    Image {
        id: image
        source: "Univers/map.png"
    }
}
