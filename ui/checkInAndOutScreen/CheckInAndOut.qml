import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Rectangle {
    anchors.fill: parent
    color: "transparent"

    signal newCheckInOutRequested()

    Component.onCompleted: {
        checkInOutModel.fetchCheckInOuts()
    }

    Rectangle {
        width: parent.width * 0.8
        height: parent.height * 0.8
        anchors.centerIn: parent
        color: "#153B56"
        opacity: 0.9
        radius: 10

        Text {
            id: checkInOutText
            text: "Check-In / Check-Out"
            color: "white"
            anchors {
                top: parent.top
                topMargin: 15
                horizontalCenter: parent.horizontalCenter
            }
            font.pixelSize: 60
            font.bold: true
        }

        Row {
            id: inputRow
            spacing: 10
            anchors {
                top: checkInOutText.bottom
                left: parent.left
                right: parent.right
                leftMargin: 30
                rightMargin: 30
            }

            Rectangle {
                id: textInputBackground
                color: "#A77937"
                radius: 10
                height: 60
                width: parent.width * 0.84
                border.color: "white"
                border.width: 1

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: textInputBackground.color = Qt.darker("#A77937", 1.2)
                    onExited: textInputBackground.color = "#A77937"
                }

                TextInput {
                    id: searchField
                    anchors.fill: parent
                    color: "white"
                    font.pixelSize: 23
                    topPadding: 18
                    bottomPadding: 18
                    leftPadding: 60
                    font.bold: true
                    font.weight: Font.Black

                    onTextChanged: {
                        checkInOutModel.setSearchText(text)
                    }
                }

                Image {
                    id: searchIcon
                    source: "qrc:/ui/assets/searchIcon.png"
                    anchors {
                        left: parent.left
                        verticalCenter: parent.verticalCenter
                        leftMargin: 10
                    }
                    height: 45
                    width: 45
                    fillMode: Image.PreserveAspectFit

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            checkInOutModel.setSearchText(searchField.text)
                        }
                        hoverEnabled: true
                    }
                }

                Text {
                    id: placeHolder
                    text: "Search Check-Ins/Outs..."
                    color: "white"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: searchIcon.right
                    anchors.leftMargin: 7
                    font.pixelSize: 17
                    font.bold: true
                    font.weight: Font.Black
                    visible: searchField.text.length === 0 && !searchField.focus
                }
            }

            Rectangle {
                id: newCheckInOutButton
                height: 60
                width: 227
                color: "#A77937"
                radius: 10
                border.color: "white"
                border.width: 1

                Text {
                    color: "white"
                    font.pixelSize: 23
                    text: "+ New Check-In/Out"
                    font.bold: true
                    font.weight: Font.Black
                    anchors.centerIn: parent
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        newCheckInOutRequested()
                    }
                    hoverEnabled: true
                    onEntered: newCheckInOutButton.color = Qt.darker("#A77937", 1.2)
                    onExited: newCheckInOutButton.color = "#A77937"
                }
            }
        }

        Rectangle {
            id: checkInOutData
            radius: 10
            border.color: "white"
            border.width: 1
            color: "#153B564D"

            anchors {
                top: inputRow.bottom
                left: parent.left
                right: parent.right
                bottom: parent.bottom
                leftMargin: 30
                rightMargin: 30
                topMargin: 14
                bottomMargin: 20
            }

            Rectangle {
                id: headerRow
                height: 50
                width: parent.width
                color: "#0E2A3C"
                radius: 5

                RowLayout {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 20

                    Text {
                        text: "Guest Name"
                        color: "white"
                        font.pixelSize: 22
                        font.bold: true
                        Layout.preferredWidth: 200
                        horizontalAlignment: Text.AlignLeft
                        padding: 20
                    }
                    Text {
                        text: "Room"
                        color: "white"
                        font.pixelSize: 22
                        font.bold: true
                        Layout.preferredWidth: 150
                        horizontalAlignment: Text.AlignLeft
                        padding: 20
                    }
                    Text {
                        text: "Action"
                        color: "white"
                        font.pixelSize: 22
                        font.bold: true
                        Layout.preferredWidth: 100
                        horizontalAlignment: Text.AlignLeft
                        padding: 20
                    }
                    Text {
                        text: "Timestamp"
                        color: "white"
                        font.pixelSize: 22
                        font.bold: true
                        Layout.preferredWidth: 300
                        horizontalAlignment: Text.AlignLeft
                        padding: 20
                    }
                }
            }

            Flickable {
                id: flick
                anchors {
                    top: headerRow.bottom
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
                clip: true
                contentWidth: checkInOutData.width

                Column {
                    width: parent.width
                    spacing: 1

                    Repeater {
                        model: checkInOutModel

                        Rectangle {
                            width: parent.width
                            height: 50
                            color: index % 2 === 0 ? "#153B5655" : "transparent"

                            RowLayout {
                                anchors.fill: parent
                                spacing: 20

                                Text {
                                    text: guestName
                                    color: highlight ? "#FFA500" : "white"
                                    font.pixelSize: 20
                                    Layout.preferredWidth: 200
                                    padding: 20
                                }
                                Text {
                                    text: room
                                    color: highlight ? "#FFA500" : "white"
                                    font.pixelSize: 20
                                    Layout.preferredWidth: 150
                                    padding: 20
                                }
                                Text {
                                    text: action
                                    color: highlight ? "#FFA500" : "white"
                                    font.pixelSize: 20
                                    Layout.preferredWidth: 100
                                    padding: 20
                                }
                                Text {
                                    text: timestamp.substring(0,10)
                                    color: highlight ? "#FFA500" : "white"
                                    font.pixelSize: 20
                                    Layout.preferredWidth: 300
                                    padding: 20
                                }

                            }
                        }
                    }
                }
            }
        }
    }
}
