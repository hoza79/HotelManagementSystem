import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    anchors.fill: parent
    color: "transparent"

    property bool busy: false

    Rectangle {
        id: reservationRect
        width: parent.width * 0.35
        height: parent.height * 0.6
        anchors.centerIn: parent
        color: "#bfbfbf"
        radius: 10
        border.color: "#B8860B"
        border.width: 1

        Text {
            id: reservationText
            text: "New Reservation"
            color: "#B8860B"
            font.pixelSize: 40
            anchors {
                top: parent.top
                topMargin: 20
                horizontalCenter: parent.horizontalCenter
            }
        }

        Column {
            anchors {
                top: reservationText.bottom
                topMargin: 20
                horizontalCenter: parent.horizontalCenter
            }
            spacing: 15

            Column {
                spacing: 5
                width: reservationRect.width * 0.8

                Text { text: "Guest Name"; color: "black"; font.pixelSize: 23 }

                TextField {
                    id: guestNameField
                    placeholderText: "Enter Guest Full Name"
                    color: "black"
                    font.pixelSize: 26
                    width: parent.width
                    height: 35
                    background: Rectangle {
                        color: "#e0e0e0"
                        radius: 8
                        border.color: "#B8860B"
                        border.width: 1
                    }
                }
            }

            Column {
                spacing: 5
                width: reservationRect.width * 0.8

                Text { text: "Phone Number"; color: "black"; font.pixelSize: 23 }

                TextField {
                    id: guestPhoneField
                    placeholderText: "Enter Guest Phone Number (optional)"
                    color: "black"
                    font.pixelSize: 26
                    width: parent.width
                    height: 35
                    background: Rectangle {
                        color: "#e0e0e0"
                        radius: 8
                        border.color: "#B8860B"
                        border.width: 1
                    }
                }
            }

            Column {
                spacing: 5
                width: reservationRect.width * 0.8

                Text { text: "Room Type"; color: "black"; font.pixelSize: 26 }

                ComboBox {
                    id: roomTypeCombo
                    width: parent.width
                    height: 35
                    model: ["Single", "Double", "Suite"]
                    contentItem: Text {
                        text: parent.displayText
                        color: "black"
                        font.pixelSize: 20
                    }
                    background: Rectangle {
                        color: "#e0e0e0"
                        radius: 8
                        border.color: "#B8860B"
                        border.width: 1
                    }
                }
            }

            Column {
                spacing: 5
                width: reservationRect.width * 0.8

                Text { text: "Check In"; color: "black"; font.pixelSize: 26 }

                TextField {
                    id: checkInField
                    placeholderText: "yyyy-MM-dd"
                    text: Qt.formatDate(new Date(), "yyyy-MM-dd")
                    color: "black"
                    width: parent.width
                    height: 35
                    background: Rectangle {
                        color: "#e0e0e0"
                        radius: 8
                        border.color: "#B8860B"
                        border.width: 1
                    }
                }
            }

            Column {
                spacing: 5
                width: reservationRect.width * 0.8

                Text { text: "Check Out"; color: "black"; font.pixelSize: 26 }

                TextField {
                    id: checkOutField
                    placeholderText: "yyyy-MM-dd"
                    text: Qt.formatDate(new Date(), "yyyy-MM-dd")
                    color: "black"
                    width: parent.width
                    height: 35
                    background: Rectangle {
                        color: "#e0e0e0"
                        radius: 8
                        border.color: "#B8860B"
                        border.width: 1
                    }
                }
            }

            Button {
                text: busy ? "Saving..." : "Save Reservation"
                width: reservationRect.width * 0.5
                height: 45
                enabled: !busy
                anchors.horizontalCenter: parent.horizontalCenter
                background: Rectangle {
                    color: "#A77937"
                    radius: 10
                    border.color: "white"
                    border.width: 1
                }
                onClicked: {
                    busy = true
                    reservationModel.addReservation(
                        guestNameField.text,
                        guestPhoneField.text,
                        checkInField.text + ":00",
                        checkOutField.text + ":00",
                        roomTypeCombo.currentText,
                        "Pending"
                    )
                }
            }
        }
    }

    Connections {
        target: reservationModel
        onReservationSaved: {
            busy = false
            pageLoader.source = "../reservationScreen/ReservationScreen.qml"
        }
    }
}
