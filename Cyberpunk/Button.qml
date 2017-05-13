import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.impl 2.1
import QtQuick.Templates 2.1 as T
import QtGraphicalEffects 1.0

T.Button {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             contentItem.implicitHeight + topPadding + bottomPadding)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    padding: 6

    contentItem: Text {
        text: control.text
        opacity: enabled || control.highlighted || control.checked ? 1 : 0.3
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight

        color: "white"
        font.bold: true
        font.family: smallFont.name
        FontLoader {
            id: smallFont
            source: "Xolonium.ttf"
        }
    }

    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 50
        visible: !control.flat || control.down || control.checked || control.highlighted
        color: "transparent"

        Image {
            anchors.fill: parent
            anchors.topMargin: 4
            anchors.bottomMargin: 4
            anchors.leftMargin: 8
            anchors.rightMargin: 8
            opacity: control.visualFocus ? 1 : 0.78
            source: control.visualFocus ? "fondBC.jpeg" : "fondB.jpeg"
            fillMode: Image.Tile
        }

        Image {
            anchors.fill: parent
            anchors.topMargin: 4
            anchors.bottomMargin: 4
            anchors.leftMargin: 8
            anchors.rightMargin: 8
            visible: control.down
            opacity: 0.90
            source: "fondR.jpeg"
            fillMode: Image.Tile
        }

        BorderImage {
            anchors.fill: parent
            source: "bouton.png"
            border.left: 16; border.top: 11
            border.right: 16; border.bottom: 11
            horizontalTileMode: BorderImage.Repeat
            verticalTileMode: BorderImage.Repeat
        }
    }
}
