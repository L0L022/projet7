import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.impl 2.1
import QtQuick.Window 2.2
import QtQuick.Templates 2.1 as T
import QtGraphicalEffects 1.0

T.ApplicationWindow {
    id: window

    background: Item {
        Image {
            anchors.fill: parent
            source: "fond.jpeg"
            fillMode: Image.Tile
            sourceSize: Qt.size(500, 500)
        }

        RadialGradient {
            anchors.fill: parent
            gradient: Gradient {
                GradientStop {
                    position: 0.4
                    color: "#00000000"
                  }
                  GradientStop {
                    position: 1.0
                    color: "#FF000000"
                  }
            }
        }

        Image {
            id: mask
            anchors.fill: parent
            source: "fondmask.png"
            fillMode: Image.Tile
            sourceSize: Qt.size(500, 500)
        }

        Glow {
            anchors.fill: mask
            visible: Qt.platform.os !== "android"
            source: mask
            color: "#21FFFF"
            samples: 30

            SequentialAnimation on spread {
                    loops: Animation.Infinite
                    PropertyAnimation { to: 0.3; duration: 1000 }
                    PropertyAnimation { to: 0.6; duration: 1000 }
            }
        }
    }
}
