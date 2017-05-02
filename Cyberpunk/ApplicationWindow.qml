import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.impl 2.1
import QtQuick.Window 2.2
import QtQuick.Templates 2.1 as T
import QtGraphicalEffects 1.0

T.ApplicationWindow {
    id: window

    background: Image {
        anchors.fill: parent
        source: "fond.jpg"
        fillMode: Image.Tile
    }
}
