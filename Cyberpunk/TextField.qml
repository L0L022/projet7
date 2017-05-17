import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.impl 2.1
import QtQuick.Templates 2.1 as T

T.TextField {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            placeholderText ? placeholder.implicitWidth + leftPadding + rightPadding : 0)
                            || contentWidth + leftPadding + rightPadding
    implicitHeight: Math.max(contentHeight + topPadding + bottomPadding,
                             background ? background.implicitHeight : 0,
                             placeholder.implicitHeight + topPadding + bottomPadding)

    padding: 6
    leftPadding: padding + 10

    opacity: enabled ? 1 : 0.2
    verticalAlignment: TextInput.AlignVCenter

    color: "white"
    selectedTextColor: color
    selectionColor: "#4DB5C7"
    font.pointSize: 15
    font.family: smallFont.name
    FontLoader {
        id: smallFont
        source: "Xolonium.ttf"
    }

    Text {
        id: placeholder
        x: control.leftPadding
        y: control.topPadding
        width: control.width - (control.leftPadding + control.rightPadding)
        height: control.height - (control.topPadding + control.bottomPadding)

        text: control.placeholderText
        font: control.font
        color: Default.textDisabledColor
        horizontalAlignment: control.horizontalAlignment
        verticalAlignment: control.verticalAlignment
        visible: !control.length && !control.preeditText && (!control.activeFocus || control.horizontalAlignment !== Qt.AlignHCenter)
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 200
        implicitHeight: 40
        color: "transparent"

        BorderImage {
            anchors.fill: parent
            source: "textline.png"
            border.left: 16; border.top: 0
            border.right: 16; border.bottom: 28
            horizontalTileMode: BorderImage.Repeat
        }
    }
}
