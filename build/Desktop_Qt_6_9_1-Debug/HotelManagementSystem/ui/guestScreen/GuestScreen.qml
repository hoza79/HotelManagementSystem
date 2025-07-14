import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Rectangle {
    anchors.fill: parent
    color: "transparent"

    signal newGuestRequested()

    Component.onCompleted: {
        guestModel.fetchGuests()
        guestModel.setSearchText("")
        textInput.text = ""

        console.log("GuestScreen loaded, model rowCount:", guestModel.rowCount())
    }

    Connections {
        target: guestModel
        function onModelReset() {
            flick.contentY = 0;
        }
    }

    Rectangle {
        width: parent.width * 0.8
        height: parent.height * 0.8
        anchors.centerIn: parent
        color: "#153B56"
        opacity: 0.9
        radius: 10

        Text {
            id: guestText
            text: "Guests"
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
                top: guestText.bottom
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
                    id: textInput
                    anchors.fill: parent
                    color: "white"
                    font.pixelSize: 23
                    topPadding: 18
                    bottomPadding: 18
                    leftPadding: 60
                    font.bold: true
                    font.weight: Font.Black

                    onTextChanged: {
                        guestModel.setSearchText(text)
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
                            guestModel.setSearchText(textInput.text)
                        }
                        hoverEnabled: true
                    }
                }

                Text {
                    id: placeHolder
                    text: "Search Guests..."
                    color: "white"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: searchIcon.right
                    anchors.leftMargin: 7
                    font.pixelSize: 17
                    font.bold: true
                    font.weight: Font.Black
                    visible: textInput.text.length === 0 && !textInput.focus
                }
            }

            Rectangle {
                id: newGuestButton
                height: 60
                width: 227
                color: "#A77937"
                radius: 10
                border.color: "white"
                border.width: 1

                Text {
                    color: "white"
                    font.pixelSize: 23
                    text: "+ New Guest"
                    font.bold: true
                    font.weight: Font.Black
                    anchors.centerIn: parent
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        newGuestRequested()
                    }
                    hoverEnabled: true
                    onEntered: newGuestButton.color = Qt.darker("#A77937", 1.2)
                    onExited: newGuestButton.color = "#A77937"
                }
            }
        }

        Rectangle {
            id: guestData
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
                        text: "Phone Number"
                        color: "white"
                        font.pixelSize: 22
                        font.bold: true
                        Layout.preferredWidth: 180
                        horizontalAlignment: Text.AlignLeft
                        padding: 20
                    }
                    Text {
                        text: "Room Number"
                        color: "white"
                        font.pixelSize: 22
                        font.bold: true
                        Layout.preferredWidth: 150
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
                contentWidth: guestData.width

                Column {
                    width: parent.width
                    spacing: 1

                    Repeater {
                        model: guestModel

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
                                    text: phoneNumber
                                    color: highlight ? "#FFA500" : "white"
                                    font.pixelSize: 20
                                    Layout.preferredWidth: 180
                                    padding: 20
                                }
                                Text {
                                    text: roomNumber === "" ? "(No Room Assigned)" : roomNumber
                                    color: highlight ? "#FFA500" : "white"
                                    font.pixelSize: 20
                                    Layout.preferredWidth: 150
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
