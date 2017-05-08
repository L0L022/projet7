import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import Projet7 1.0

Item {
    id: item
    readonly property string title: qsTr("Choose a character")

    ListModel {
        id: factions

        ListElement {
            idRole: "0"
            nameRole: "Linux"
            descriptionRole: "La plus puissante des factions !"
        }

        ListElement {
            idRole: "1"
            nameRole: "Windows"
            descriptionRole: "Des sans ames."
        }

        ListElement {
            idRole: "2"
            nameRole: "Macaca"
            descriptionRole: "No comment."
        }
    }

    function getFactionIndex(id) {
        for (var i = 0; i < factions.count; ++i)
            if (factions.get(i).idRole === id)
                return i
        return -1
    }

    ListModel {
        id: characters

        ListElement {
            nameRole: "Loïc"
            factionRole: "0"
            imageRole: "http://images6.fanpop.com/image/photos/35600000/Light-Yagami-death-note-35690679-800-600.jpg"
            descriptionRole: "Le maitre de l'univers."
        }

        ListElement {
            nameRole: "Alexandre Dejeeaguèrre"
            factionRole: "0"
            imageRole: "https://www.metaliercoatings.com/wp-content/uploads/2014/11/Aluminium-Liquid-Metal-540x272.jpg"
            descriptionRole: "Utilisateur linux qui est trop métal ! Et gros branleur à temps plein."
        }

        ListElement {
            nameRole: "L'autre Loic"
            factionRole: "1"
            imageRole: "http://3.bp.blogspot.com/_f7BjNAnSRfo/TFldiUauV5I/AAAAAAAAADY/0q4B-B1aD3A/s1600/blender1.jpg"
            descriptionRole: "L'artiste ultime !"
        }

        ListElement {
            nameRole: "Martin"
            factionRole: "2"
            imageRole: "http://www.heurtevent.net/wp-content/uploads/2014/07/url.jpg"
            descriptionRole: "Il fait des sites web en html5/css3."
        }
    }

    Component {
        id: charactersSwipe

        Item {
            readonly property string title: qsTr("Characters")
            property alias currentIndex: swipe.currentIndex

            SwipeView {
                id: swipe
                anchors.fill: parent
                clip: true

                Repeater {
                    model: characters
                    delegate: Loader {
                        active: SwipeView.isCurrentItem || SwipeView.isNextItem || SwipeView.isPreviousItem
                        sourceComponent: CharacterDelegate {
                            faction: factions.get(getFactionIndex(factionRole))
                        }
                    }
                }
            }

            PageIndicator {
                 count: swipe.count
                 currentIndex: swipe.currentIndex

                 anchors.bottom: swipe.bottom
                 anchors.horizontalCenter: parent.horizontalCenter
             }
        }
    }

    ListView {
        anchors.fill: parent
        model: characters
        section.property: "factionRole"
        section.delegate: ItemDelegate {
            text: factions.get(section).nameRole
            font.bold: true
            font.italic: true
        }

        delegate: ItemDelegate {
            text: nameRole
            onClicked: stack.push(charactersSwipe, {"currentIndex": index})
        }
    }
}
