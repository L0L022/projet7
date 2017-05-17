import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.impl 2.1
import QtQuick.Templates 2.1 as T

T.TabButton {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             contentItem.implicitHeight + topPadding + bottomPadding)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    padding: 6

    contentItem: Text {
        text: control.text
//        font: control.font
        elide: Text.ElideRight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        color: "white"
        font.family: smallFont.name
        FontLoader {
            id: smallFont
            source: "Xolonium.ttf"
        }
    }

    background: Rectangle {
        implicitHeight: 45
        color: "transparent"

        Image {
            anchors.fill: parent
            anchors.bottomMargin: 4
            opacity: control.checked ? 1 : 0.78
            source: control.checked ? "fondBC.jpeg" : "fondB.jpeg"
            fillMode: Image.Tile
        }

        Image {
            anchors.fill: parent
            anchors.bottomMargin: 4
            visible: control.checked
            opacity: 0.90
            source: "fondR.jpeg"
            fillMode: Image.Tile
        }

        BorderImage {
            anchors.fill: parent
            source: "TabButton.png"
            border.left: 9; border.top: 0
            border.right: 9; border.bottom: 6
            horizontalTileMode: BorderImage.Repeat
            verticalTileMode: BorderImage.Repeat
        }
    }
}
