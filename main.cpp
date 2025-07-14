#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include "controllers/ReservationModel.h"
#include "controllers/GuestModel.h"
#include "controllers/RoomModel.h"
#include "controllers/CheckInOutModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ReservationModel reservationModel;
    GuestModel guestModel;
    RoomModel roomModel;
    CheckInOutModel checkInOutModel;

    reservationModel.fetchReservations();
    guestModel.fetchGuests();
    roomModel.fetchRooms();
    checkInOutModel.fetchCheckInOuts();

    QObject::connect(&checkInOutModel, &CheckInOutModel::refreshReservationsRequested,
                     &reservationModel, &ReservationModel::fetchReservations);

    QObject::connect(&checkInOutModel, &CheckInOutModel::refreshGuestsRequested,
                     &guestModel, &GuestModel::fetchGuests);

    QObject::connect(&checkInOutModel, &CheckInOutModel::refreshRoomsRequested,
                     &roomModel, &RoomModel::fetchRooms);

    // Add timer for auto-refresh of reservations
    auto timer = new QTimer(&app);
    timer->setInterval(5000);
    QObject::connect(timer, &QTimer::timeout, [&]() {
        reservationModel.fetchReservations();
    });
    timer->start();

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("reservationModel", &reservationModel);
    engine.rootContext()->setContextProperty("guestModel", &guestModel);
    engine.rootContext()->setContextProperty("roomModel", &roomModel);
    engine.rootContext()->setContextProperty("checkInOutModel", &checkInOutModel);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() {
            QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection
        );

    engine.loadFromModule("HotelManagementSystem", "Main");

    return app.exec();
}
