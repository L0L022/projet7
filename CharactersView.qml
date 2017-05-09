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
            descriptionRole: "Des sans âmes."
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
            nameRole: "Killian"
            factionRole: "0"
            imageRole: "http://img.over-blog-kiwi.com/1/23/41/63/20151206/ob_1b2311_actu-anime.jpg"
            descriptionRole: "Aime marine. Beurk."
        }

        ListElement {
            nameRole: "L'autre Loic"
            factionRole: "1"
            imageRole: "http://3.bp.blogspot.com/_f7BjNAnSRfo/TFldiUauV5I/AAAAAAAAADY/0q4B-B1aD3A/s1600/blender1.jpg"
            descriptionRole: "L'artiste ultime !"
        }

        ListElement {
            nameRole: "Hugo"
            factionRole: "1"
            imageRole: "http://www.fotofever.com/artist/image/large/3273/galerie-des-soupirs___olivier-dani___sans-titre-1___ame-de-fer___2014.jpg"
            descriptionRole: "MMI sans âme."
        }

        ListElement {
            nameRole: "Laurent"
            factionRole: "1"
            imageRole: "http://www.alextools.be/wp-content/associal.jpg"
            descriptionRole: "Le mec associal qui préfère regarder des animés que faire le diapo. Ce petit con."
        }

        ListElement {
            nameRole: "Martin"
            factionRole: "2"
            imageRole: "http://www.heurtevent.net/wp-content/uploads/2014/07/url.jpg"
            descriptionRole: "Il fait des sites web en html5/css3."
        }
    }

    Component {
        id: swipeview

        Item {
            id: swipeitem
            property string title
            property alias model: repeater.model
            property Component delegate
            property alias currentIndex: swipe.currentIndex

            SwipeView {
                id: swipe
                anchors.fill: parent
                clip: true

                Repeater {
                    id: repeater
                    model: characters
                    delegate: Loader {
                        id: loader
                        property int modelIndex: index
                        active: SwipeView.isCurrentItem || SwipeView.isNextItem || SwipeView.isPreviousItem
                        sourceComponent: swipeitem.delegate
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

    Component {
        id: characterDelegate

        CharacterDelegate {
            character: characters.get(modelIndex)
            faction: factions.get(getFactionIndex(character.factionRole))
        }
    }

    Component {
        id: factionDelegate

        FactionDelegate {
            faction: factions.get(modelIndex)
        }
    }

    ListView {
        anchors.fill: parent
        model: characters
        section.property: "factionRole"
        section.delegate: ItemDelegate {
            width: parent.width
            font.bold: true
            font.italic: true
            Component.onCompleted: text = factions.get(section).nameRole
            onClicked: stack.push(swipeview, {"title": qsTr("Factions"), "model": factions, "delegate": factionDelegate, "currentIndex": section})
        }

        delegate: ItemDelegate {
            width: parent.width
            text: nameRole
            onClicked: stack.push(swipeview, {"title": qsTr("Characters"), "model": characters, "delegate": characterDelegate, "currentIndex": index})
        }
    }
}
