import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.impl 2.1
import QtQuick.Templates 2.1 as T

T.ToolButton {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0,
                            contentItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0,
                             contentItem.implicitHeight + topPadding + bottomPadding)
    baselineOffset: contentItem.y + contentItem.baselineOffset

    padding: 6

    contentItem: Text {
        text: control.text
        font: control.font
        color: control.enabled ? (control.visualFocus ? Default.focusColor : Default.textDarkColor) : Default.textDisabledLightColor
        elide: Text.ElideRight
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        implicitWidth: 40
        implicitHeight: 40

        color: Qt.darker(Default.toolButtonColor, control.enabled && (control.checked || control.highlighted) ? 1.5 : 1.0)
        opacity: control.down ? 1.0 : control.enabled && (control.checked || control.highlighted) ? 0.5 : 0
        visible: control.down || (control.enabled && (control.checked || control.highlighted))
    }
}
