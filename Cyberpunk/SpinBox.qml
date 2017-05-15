import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.impl 2.1
import QtQuick.Templates 2.1 as T

T.SpinBox {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + 2 * padding +
                            (up.indicator ? up.indicator.implicitWidth : 0) +
                            (down.indicator ? down.indicator.implicitWidth : 0))
    implicitHeight: Math.max(contentItem.implicitHeight + topPadding + bottomPadding,
                             background ? background.implicitHeight : 0,
                             up.indicator ? up.indicator.implicitHeight : 0,
                             down.indicator ? down.indicator.implicitHeight : 0)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    padding: 6
    leftPadding: padding + (control.mirrored ? (up.indicator ? up.indicator.width : 0) : (down.indicator ? down.indicator.width : 0))
    rightPadding: padding + (control.mirrored ? (down.indicator ? down.indicator.width : 0) : (up.indicator ? up.indicator.width : 0))

    validator: IntValidator {
        locale: control.locale.name
        bottom: Math.min(control.from, control.to)
        top: Math.max(control.from, control.to)
    }

    contentItem: TextInput {
        z: 2
        text: control.textFromValue(control.value, control.locale)
        opacity: control.enabled ? 1 : 0.3

        //font: control.font
        selectionColor: Default.focusColor
        selectedTextColor: Default.textLightColor
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter

        readOnly: !control.editable
        validator: control.validator
        inputMethodHints: Qt.ImhFormattedNumbersOnly

        color: "white"
        font.family: smallFont.name
        FontLoader {
            id: smallFont
            source: "Xolonium.ttf"
        }
    }

    up.indicator: Item {
        x: control.mirrored ? 0 : parent.width - width
        height: parent.height
        implicitWidth: 40
        implicitHeight: 40
    }

    down.indicator: Item {
        x: control.mirrored ? parent.width - width : 0
        height: parent.height
        implicitWidth: 40
        implicitHeight: 40
    }

    background: Item {
        implicitWidth: 140

        Image {
            anchors.fill: parent
            anchors.margins: 4
            source: "fondB.jpeg"
            fillMode: Image.Tile
        }

        Image {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.margins: 5
            width: 30
            visible: down.pressed
            source: "fondR.jpeg"
            fillMode: Image.Tile
        }

        Image {
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: 5
            width: 30
            visible: up.pressed
            source: "fondR.jpeg"
            fillMode: Image.Tile
        }

        BorderImage {
            anchors.fill: parent
            source: "spinbox.png"
            border.left: 53; border.top: 0
            border.right: 53; border.bottom: 0
            horizontalTileMode: BorderImage.Repeat
        }
    }
}
