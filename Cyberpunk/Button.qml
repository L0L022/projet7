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
    leftPadding: padding + 2
    rightPadding: padding + 2

    contentItem: Text {
        text: control.text
        opacity: enabled || control.highlighted || control.checked ? 1 : 0.3
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight

        font.family: "Hack"
        font.bold: true
        font.capitalization: Font.AllUppercase
    }

    Glow {
        anchors.fill: contentItem
        source: contentItem
        samples: 30
        color: "#843025"

        SequentialAnimation on spread {
                loops: Animation.Infinite
                PropertyAnimation { to: 0.3; duration: 2000 }
                PropertyAnimation { to: 0.6; duration: 2000 }
        }
    }

    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 50
        visible: !control.flat || control.down || control.checked || control.highlighted
        /*color: control.checked || control.highlighted ?
            (control.visualFocus ? (control.down ? Default.buttonCheckedFocusColor : Default.focusColor) : (control.down ? Default.buttonCheckedPressedColor : Default.textColor)) :
            (control.visualFocus ? (control.down ? Default.focusPressedColor : Default.focusLightColor) : (control.down ? Default.buttonPressedColor : Default.buttonColor))
        border.color: Default.focusColor
        border.width: control.visualFocus ? 2 : 0*/
        color: "transparent"

        BorderImage {
            id: image
            anchors.fill: parent
            source: "Button.png"
            border.left: 37; border.top: 14
            border.right: 33; border.bottom: 9
        }

        Glow {
            anchors.fill: image
            source: image
            color: "green"
            visible: control.visualFocus
            samples: 30

            SequentialAnimation on spread {
                    loops: Animation.Infinite
                    running: control.visualFocus
                    //alwaysRunToEnd: true

                    PropertyAnimation { to: 0.1; duration: 2000 }
                    PropertyAnimation { to: 0.5; duration: 2000 }
            }
        }

        LevelAdjust {
            anchors.fill: image
            source: image
            visible: control.down
            gamma: Qt.vector3d(1.4, 0.7, 1.0)
        }
    }
/*
    BrightnessContrast {
        anchors.fill: parent
        source: parent
        contrast: control.checked || control.visualFocus ? 0.5 : 0
    }*/
}
