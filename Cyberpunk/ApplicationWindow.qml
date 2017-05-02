import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.impl 2.1
import QtQuick.Window 2.2
import QtQuick.Templates 2.1 as T
import QtGraphicalEffects 1.0

T.ApplicationWindow {
    id: window

    color: Default.backgroundColor

    overlay.modal: Rectangle {
        color: Default.overlayModalColor
    }

    overlay.modeless: Rectangle {
        color: Default.overlayDimColor
    }

    BorderImage {
        anchors.fill: parent
        source: "cadre.png"
        horizontalTileMode: BorderImage.Repeat
        verticalTileMode: BorderImage.Repeat
        border.left: 67
        border.top: 36
        border.right: 68
        border.bottom: 36
    }

    BorderImage {
        id: fond
        anchors.fill: parent
        source: "cadremask.png"
        horizontalTileMode: BorderImage.Repeat
        verticalTileMode: BorderImage.Repeat
        border.left: 67
        border.top: 36
        border.right: 68
        border.bottom: 36
    }

    Glow {
        anchors.fill: fond
        source: fond
        color: "#0ACAE7"
        samples: 30

        SequentialAnimation on spread {
                loops: Animation.Infinite
                PropertyAnimation { to: 0.3; duration: 1000 }
                PropertyAnimation { to: 0.6; duration: 1000 }
        }
    }
}
