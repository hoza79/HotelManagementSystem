import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    anchors.fill: parent
    color: "transparent"

    signal guestSaved()

    property bool busy: false

    Component.onCompleted: {
        roomModel.fetchRooms()
    }

    Rectangle {
        id: guestRect
        width: parent.width * 0.5
        height: parent.height * 0.7
        anchors.centerIn: parent
        color: "#bfbfbf"
        radius: 10
        border.color: "#B8860B"
        border.width: 1

        Text {
            id: guestText
            text: "New Guest"
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
                top: guestText.bottom
                topMargin: 30
                horizontalCenter: parent.horizontalCenter
            }
            spacing: 20

            Column {
                spacing: 5
                width: guestRect.width * 0.8
                Text { text: "Guest Name"; color: "black"; font.pixelSize: 23 }
                TextField {
                    id: guestNameField
                    width: parent.width
                    height: 40
                    color: "black"
                    font.pixelSize: 23
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
                width: guestRect.width * 0.8
                Text { text: "Phone Number"; color: "black"; font.pixelSize: 23 }
                TextField {
                    id: phoneNumberField
                    width: parent.width
                    height: 40
                    color: "black"
                    font.pixelSize: 23
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
                width: guestRect.width * 0.8
                Text { text: "Assign Room"; color: "black"; font.pixelSize: 23 }
                ComboBox {
                    id: roomCombo
                    width: parent.width
                    height: 40
                    model: roomModel.vacantRoomNumbers
                    background: Rectangle {
                        color: "#e0e0e0"
                        radius: 8
                        border.color: "#B8860B"
                        border.width: 1
                    }
                    contentItem: Text {
                        text: parent.displayText
                        color: "black"
                        font.pixelSize: 20
                    }
                }
            }

            Button {
                text: busy ? "Saving..." : "Save Guest"
                width: guestRect.width * 0.5
                height: 50
                enabled: !busy
                anchors.horizontalCenter: parent.horizontalCenter
                background: Rectangle {
                    color: "#A77937"
                    radius: 10
                    border.color: "white"
                    border.width: 1
                }

                onClicked: {
                    busy = true;

                    var selectedRoom = roomCombo.currentText;
                    var roomId = -1;
                    if (selectedRoom && selectedRoom.length > 0) {
                        roomId = roomModel.roomIdForNumber(selectedRoom);
                    }

                    guestModel.addGuest(
                        guestNameField.text,
                        phoneNumberField.text,
                        roomId
                    );

                    reservationModel.addReservation(
                        guestNameField.text,
                        phoneNumberField.text,
                        Qt.formatDateTime(new Date(), "yyyy-MM-ddTHH:mm") + ":00",
                        Qt.formatDateTime(new Date(), "yyyy-MM-ddTHH:mm") + ":00",
                        "Single",
                        "Pending"
                    );
                }
            }
        }
    }

    Connections {
        target: reservationModel
        onReservationSaved: {
            var resIdx = reservationModel.fullNames.indexOf(guestNameField.text);
            var reservationId = reservationModel.reservationIdAt(resIdx);
            var roomId = roomModel.roomIdForNumber(roomCombo.currentText);

            if (reservationId !== -1 && roomId !== -1) {
                checkInOutModel.addCheckInOut(
                    reservationId,
                    "IN",
                    roomId
                );

                reservationModel.updateReservationStatus(reservationId, "Checked-in");
                roomModel.updateRoomStatus(roomId, "Occupied");
            }

            guestModel.setSearchText("")
            guestModel.fetchGuests()
            guestSaved()

            roomModel.fetchRooms()
            checkInOutModel.fetchCheckInOuts()

            busy = false;
            pageLoader.source = "../guestScreen/GuestScreen.qml";
        }
    }
}
