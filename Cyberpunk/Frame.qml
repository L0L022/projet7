import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.impl 2.1
import QtQuick.Templates 2.1 as T
import QtGraphicalEffects 1.0

T.Frame {
    id: control

    implicitWidth: Math.max(background ? background.implicitWidth : 0, contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0, contentHeight + topPadding + bottomPadding)

    contentWidth: contentItem.implicitWidth || (contentChildren.length === 1 ? contentChildren[0].implicitWidth : 0)
    contentHeight: contentItem.implicitHeight || (contentChildren.length === 1 ? contentChildren[0].implicitHeight : 0)

    padding: 30

    background: Item {
        BorderImage {
            anchors.fill: parent
            anchors.margins: -23
            source: "cadre.png"
            horizontalTileMode: BorderImage.Repeat
            verticalTileMode: BorderImage.Repeat
            border.left: 102
            border.top: 103
            border.right: 102
            border.bottom: 103
        }

        BorderImage {
            id: fond
            anchors.fill: parent
            anchors.margins: -23
            source: "cadremask.png"
            horizontalTileMode: BorderImage.Repeat
            verticalTileMode: BorderImage.Repeat
            border.left: 102
            border.top: 103
            border.right: 102
            border.bottom: 103
        }

        Glow {
            anchors.fill: fond
            source: fond
            color: "#0ACAE7"
            visible: Qt.platform.os !== "android"
            samples: 30

            SequentialAnimation on spread {
                    loops: Animation.Infinite
                    PropertyAnimation { to: 0.3; duration: 1000 }
                    PropertyAnimation { to: 0.6; duration: 1000 }
            }
        }
    }
}
