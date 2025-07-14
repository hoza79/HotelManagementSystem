import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../commonComponents"

Rectangle {
    anchors.fill: parent
    color: "transparent"

    Component.onCompleted: {
        roomModel.fetchRooms()
    }

    Rectangle {
        width: parent.width * 0.8
        height: parent.height * 0.8
        anchors.centerIn: parent
        color: "#153B56"
        opacity: 0.9
        radius: 10

        Text {
            id: roomStatusText
            text: "Room Status"
            color: "white"
            anchors {
                top: parent.top
                topMargin: 15
                horizontalCenter: parent.horizontalCenter
            }
            font.pixelSize: 50
            font.bold: true
        }

        RowLayout {
            id: inputRow
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: roomStatusText.bottom
            anchors.topMargin: 20
            spacing: 40

            ComboBox {
                Layout.preferredWidth: 150
                Layout.preferredHeight: 40
                model: ["All Floors", "First", "Second", "Third"]
                currentIndex: 0
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

            ComboBox {
                Layout.preferredWidth: 150
                Layout.preferredHeight: 40
                model: ["All Types", "Single", "Double", "Suite"]
                currentIndex: 0
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

        Rectangle {
            id: roomsData
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

            Flickable {
                anchors.fill: parent
                contentWidth: grid.width
                contentHeight: grid.height
                clip: true

                GridLayout {
                    id: grid
                    columns: 10
                    anchors {
                        left: parent.left
                        right: parent.right
                        top: parent.top
                        leftMargin: 60
                        topMargin: 20
                    }
                    rowSpacing: 6
                    columnSpacing: 4

                    Repeater {
                        model: roomModel

                        delegate: RoomLayout {
                            roomNumber: model.roomNumber
                            status: model.status

                            onClicked: {
                                var newStatus = (status === "Vacant") ? "Occupied" : "Vacant"
                                console.log("Clicked room:", roomNumber, "new status:", newStatus, "id:", model.id)
                                roomModel.updateRoomStatus(model.id, newStatus)
                            }
                        }
                    }


                }
            }
        }
    }
}
