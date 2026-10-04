/****************************************************************************
** Meta object code from reading C++ file 'udpreceiver.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../udpreceiver.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'udpreceiver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.12.0. It"
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
struct qt_meta_tag_ZN11UdpReceiverE_t {};
} // unnamed namespace

template <> constexpr inline auto UdpReceiver::qt_create_metaobjectdata<qt_meta_tag_ZN11UdpReceiverE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "UdpReceiver",
        "errorOccurred",
        "",
        "message",
        "addResponseReceived",
        "respID",
        "ack",
        "uniqueID",
        "lat",
        "longitude",
        "comment",
        "deleteResponseReceived",
        "start",
        "readPendingDatagrams"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'errorOccurred'
        QtMocHelpers::SignalData<void(const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'addResponseReceived'
        QtMocHelpers::SignalData<void(quint8, quint8, quint32, float, float, const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UChar, 5 }, { QMetaType::UChar, 6 }, { QMetaType::UInt, 7 }, { QMetaType::Float, 8 },
            { QMetaType::Float, 9 }, { QMetaType::QString, 10 },
        }}),
        // Signal 'deleteResponseReceived'
        QtMocHelpers::SignalData<void(quint8, quint8, quint32)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UChar, 5 }, { QMetaType::UChar, 6 }, { QMetaType::UInt, 7 },
        }}),
        // Slot 'start'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'readPendingDatagrams'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<UdpReceiver, qt_meta_tag_ZN11UdpReceiverE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject UdpReceiver::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11UdpReceiverE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11UdpReceiverE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11UdpReceiverE_t>.metaTypes,
    nullptr
} };

void UdpReceiver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<UdpReceiver *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->errorOccurred((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->addResponseReceived((*reinterpret_cast<std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<quint8>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<quint32>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<float>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<float>>(_a[5])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[6]))); break;
        case 2: _t->deleteResponseReceived((*reinterpret_cast<std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<quint8>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<quint32>>(_a[3]))); break;
        case 3: _t->start(); break;
        case 4: _t->readPendingDatagrams(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (UdpReceiver::*)(const QString & )>(_a, &UdpReceiver::errorOccurred, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (UdpReceiver::*)(quint8 , quint8 , quint32 , float , float , const QString & )>(_a, &UdpReceiver::addResponseReceived, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (UdpReceiver::*)(quint8 , quint8 , quint32 )>(_a, &UdpReceiver::deleteResponseReceived, 2))
            return;
    }
}

const QMetaObject *UdpReceiver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UdpReceiver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11UdpReceiverE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int UdpReceiver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void UdpReceiver::errorOccurred(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void UdpReceiver::addResponseReceived(quint8 _t1, quint8 _t2, quint32 _t3, float _t4, float _t5, const QString & _t6)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2, _t3, _t4, _t5, _t6);
}

// SIGNAL 2
void UdpReceiver::deleteResponseReceived(quint8 _t1, quint8 _t2, quint32 _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2, _t3);
}
QT_WARNING_POP
