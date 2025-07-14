/****************************************************************************
** Meta object code from reading C++ file 'ReservationModel.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../controllers/ReservationModel.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ReservationModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN16ReservationModelE_t {};
} // unnamed namespace

template <> constexpr inline auto ReservationModel::qt_create_metaobjectdata<qt_meta_tag_ZN16ReservationModelE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ReservationModel",
        "fullNamesChanged",
        "",
        "refreshCheckInOutsRequested",
        "reservationSaved",
        "onReplyFinished",
        "QNetworkReply*",
        "reply",
        "fetchReservations",
        "addReservation",
        "guestName",
        "guestPhone",
        "checkIn",
        "checkOut",
        "roomType",
        "status",
        "reservationIdAt",
        "index",
        "updateReservationStatus",
        "reservationId",
        "newStatus",
        "get",
        "QVariantMap",
        "row",
        "fullNames"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'fullNamesChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'refreshCheckInOutsRequested'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'reservationSaved'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onReplyFinished'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(5, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Method 'fetchReservations'
        QtMocHelpers::MethodData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'addReservation'
        QtMocHelpers::MethodData<void(const QString &, const QString &, const QString &, const QString &, const QString &, const QString &)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 10 }, { QMetaType::QString, 11 }, { QMetaType::QString, 12 }, { QMetaType::QString, 13 },
            { QMetaType::QString, 14 }, { QMetaType::QString, 15 },
        }}),
        // Method 'reservationIdAt'
        QtMocHelpers::MethodData<int(int) const>(16, 2, QMC::AccessPublic, QMetaType::Int, {{
            { QMetaType::Int, 17 },
        }}),
        // Method 'updateReservationStatus'
        QtMocHelpers::MethodData<void(int, const QString &)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 19 }, { QMetaType::QString, 20 },
        }}),
        // Method 'get'
        QtMocHelpers::MethodData<QVariantMap(int) const>(21, 2, QMC::AccessPublic, 0x80000000 | 22, {{
            { QMetaType::Int, 23 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'fullNames'
        QtMocHelpers::PropertyData<QStringList>(24, QMetaType::QStringList, QMC::DefaultPropertyFlags, 0),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ReservationModel, qt_meta_tag_ZN16ReservationModelE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ReservationModel::staticMetaObject = { {
    QMetaObject::SuperData::link<FilterableListModel::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16ReservationModelE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16ReservationModelE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN16ReservationModelE_t>.metaTypes,
    nullptr
} };

void ReservationModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ReservationModel *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->fullNamesChanged(); break;
        case 1: _t->refreshCheckInOutsRequested(); break;
        case 2: _t->reservationSaved(); break;
        case 3: _t->onReplyFinished((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 4: _t->fetchReservations(); break;
        case 5: _t->addReservation((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[6]))); break;
        case 6: { int _r = _t->reservationIdAt((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->updateReservationStatus((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 8: { QVariantMap _r = _t->get((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QNetworkReply* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ReservationModel::*)()>(_a, &ReservationModel::fullNamesChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ReservationModel::*)()>(_a, &ReservationModel::refreshCheckInOutsRequested, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ReservationModel::*)()>(_a, &ReservationModel::reservationSaved, 2))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QStringList*>(_v) = _t->fullNames(); break;
        default: break;
        }
    }
}

const QMetaObject *ReservationModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ReservationModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16ReservationModelE_t>.strings))
        return static_cast<void*>(this);
    return FilterableListModel::qt_metacast(_clname);
}

int ReservationModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FilterableListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void ReservationModel::fullNamesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ReservationModel::refreshCheckInOutsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ReservationModel::reservationSaved()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
