import QtQuick 2.15
import "../commonComponents"
import "../sideBar"
import "../reservationScreen"
import "../guestScreen"
import "../checkInAndOutScreen"
import "../roomStatus"
import "../welcomeScreen"

Rectangle {
    id: sharedScreen
    anchors.fill: parent

    Image {
        id: bg
        source: "qrc:/ui/assets/backgroundImage.png"
        fillMode: Image.Stretch
        anchors.fill: parent
    }

    Loader {
        id: pageLoader
        anchors.fill: parent
        source: "../welcomeScreen/WelcomeScreen.qml"

        onLoaded: {
            if (item && item.newReservationRequested) {
                item.newReservationRequested.connect(function() {
                    pageLoader.source = "../reservationScreen/NewReservation.qml"
                })
            }

            if (item && item.newGuestRequested) {
                item.newGuestRequested.connect(function() {
                    pageLoader.source = "../guestScreen/NewGuest.qml"
                })
            }

            if (item && item.newCheckInOutRequested) {
                item.newCheckInOutRequested.connect(function() {
                    pageLoader.source = "../checkInAndOutScreen/NewCheckInOut.qml"
                })
            }

            if (item && item.guestSaved) {
                item.guestSaved.connect(function() {
                    pageLoader.source = "../guestScreen/GuestScreen.qml"
                })
            }

        }
    }

    SideBar {
        id: sideBar

        onHomeClicked: {
            pageLoader.source = "../welcomeScreen/WelcomeScreen.qml"
        }

        onReservationsClicked: {
            pageLoader.source = "../reservationScreen/ReservationScreen.qml"
        }

        onGuestsClicked: {
            pageLoader.source = "../guestScreen/GuestScreen.qml"
        }

        onCheckInAndOutClicked: {
            pageLoader.source = "../checkInAndOutScreen/CheckInAndOut.qml"
        }

        onRoomStatusClicked: {
            pageLoader.source = "../roomStatus/RoomStatus.qml"
        }
    }
}
