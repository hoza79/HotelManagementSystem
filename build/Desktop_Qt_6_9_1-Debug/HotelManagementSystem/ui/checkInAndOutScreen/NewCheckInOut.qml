import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    anchors.fill: parent
    color: "transparent"

    property bool busy: false

    ListModel {
        id: checkedInModel
    }

    ListModel {
        id: pendingReservationsModel
    }

    Component.onCompleted: {
        reservationModel.fetchReservations()
        roomModel.fetchRooms()
        updatePendingReservations()
    }

    Connections {
        target: checkInOutModel
        function onRefreshReservationsRequested() {
            reservationModel.fetchReservations();
            updatePendingReservations();
            updateCheckedInReservations();
        }
    }

    function updateCheckedInReservations() {
        checkedInModel.clear();

        var rows = reservationModel.rowCount();
        for (var i = 0; i < rows; i++) {
            var res = reservationModel.get(i);
            var name = res.guestName;
            var status = res.reservationStatus;

            console.log("Reservation:", name, "Status:", status);

            if (status === "Checked-in") {
                checkedInModel.append({ name: name });
            }
        }
    }

    function updatePendingReservations() {
        pendingReservationsModel.clear();

        var rows = reservationModel.rowCount();
        for (var i = 0; i < rows; i++) {
            var res = reservationModel.get(i);
            var name = res.guestName;
            var status = res.reservationStatus;

            if (status === "Pending") {
                pendingReservationsModel.append({ name: name });
            }
        }
    }

    Rectangle {
        id: reservationRect
        width: parent.width * 0.35
        height: parent.height * 0.5
        anchors.centerIn: parent
        color: "#bfbfbf"
        radius: 10
        border.color: "#B8860B"
        border.width: 1

        Text {
            id: reservationText
            text: "New Check-In / Out"
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

                Text {
                    text: "Reservation"
                    color: "black"
                    font.pixelSize: 23
                }

                ComboBox {
                    id: reservationCombo
                    width: parent.width
                    height: 35

                    model: actionCombo.currentText === "OUT"
                        ? checkedInModel
                        : pendingReservationsModel

                    textRole: "name"

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

                Text {
                    text: "Action"
                    color: "black"
                    font.pixelSize: 23
                }

                ComboBox {
                    id: actionCombo
                    width: parent.width
                    height: 35
                    model: ["IN", "OUT"]
                    onCurrentTextChanged: {
                        if (actionCombo.currentText === "OUT") {
                            updateCheckedInReservations()
                        } else {
                            updatePendingReservations()
                        }
                    }
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
                id: roomSelectBlock
                visible: actionCombo.currentText === "IN"
                spacing: 5
                width: reservationRect.width * 0.8

                Text {
                    text: "Select Room"
                    color: "black"
                    font.pixelSize: 23
                }

                ComboBox {
                    id: roomCombo
                    width: parent.width
                    height: 35
                    model: roomModel.vacantRoomNumbers
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

            Button {
                text: busy ? "Saving..." : "Save Action"
                width: reservationRect.width * 0.5
                height: 45
                enabled: !busy
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 23
                background: Rectangle {
                    color: "#A77937"
                    radius: 10
                    border.color: "white"
                    border.width: 1
                }

                onClicked: {
                    var resIdx = reservationCombo.currentIndex;
                    if (resIdx === -1) {
                        console.log("Select a reservation first!");
                        return;
                    }

                    busy = true;

                    var reservationId;
                    if (actionCombo.currentText === "OUT") {
                        var name = checkedInModel.get(resIdx).name;
                        reservationId = reservationModel.reservationIdAt(
                            reservationModel.fullNames.indexOf(name)
                        );
                    } else {
                        var name = pendingReservationsModel.get(resIdx).name;
                        reservationId = reservationModel.reservationIdAt(
                            reservationModel.fullNames.indexOf(name)
                        );
                    }

                    var action = actionCombo.currentText;

                    if (action === "IN") {
                        var roomId = roomModel.roomIdForNumber(roomCombo.currentText);
                        console.log("Checking IN reservation:", reservationId, "into room:", roomId);
                        checkInOutModel.addCheckInOut(reservationId, action, roomId);
                    } else {
                        console.log("Checking OUT reservation:", reservationId);
                        checkInOutModel.addCheckInOut(reservationId, action, -1);
                    }
                }
            }
        }
    }

    Connections {
        target: checkInOutModel
        function onCheckInOutSaved() {
            busy = false;
            pageLoader.source = "../checkInAndOutScreen/CheckInAndOut.qml";
        }
    }
}
