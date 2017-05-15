import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.impl 2.1
import QtQuick.Templates 2.1 as T

T.ItemDelegate {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             Math.max(contentItem.implicitHeight,
                                      indicator ? indicator.implicitHeight : 0) + topPadding + bottomPadding)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    padding: 12
    spacing: 12

    contentItem: Text {
        leftPadding: control.mirrored ? (control.indicator ? control.indicator.width : 0) + control.spacing : 0
        rightPadding: !control.mirrored ? (control.indicator ? control.indicator.width : 0) + control.spacing : 0

        text: control.text
        //font: control.font
        elide: Text.ElideRight
        visible: control.text
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter

        color: "white"
        font.family: smallFont.name
        FontLoader {
            id: smallFont
            source: "Xolonium.ttf"
        }
    }

    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 40
        //visible: control.down || control.highlighted || control.visualFocus
        color: control.visualFocus
            ? (control.pressed ? Default.focusPressedColor : Default.delegateFocusColor)
            : (control.down ? Default.delegatePressedColor : Default.delegateColor)
        radius: 10

        Image {
            anchors.fill: parent
            source: control.visualFocus ? control.down ? "fondR.jpeg" : "fondBC.jpeg" : "fondB.jpeg"
            fillMode: Image.Tile
        }
    }
}
