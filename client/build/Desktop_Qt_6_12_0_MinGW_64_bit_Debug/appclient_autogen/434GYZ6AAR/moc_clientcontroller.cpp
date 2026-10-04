/****************************************************************************
** Meta object code from reading C++ file 'clientcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../Downloads/Qt_Client_Server_Refined/qt_refined/client/clientcontroller.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientcontroller.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN16ClientControllerE_t {};
} // unnamed namespace

template <> constexpr inline auto ClientController::qt_create_metaobjectdata<qt_meta_tag_ZN16ClientControllerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ClientController",
        "recordsChanged",
        "",
        "statusChanged",
        "sendAddRequest",
        "uniqueID",
        "lat",
        "longitude",
        "comment",
        "sendUpdateRequest",
        "sendDeleteRequest",
        "onAddResponse",
        "respID",
        "ack",
        "onDeleteResponse",
        "setStatus",
        "message",
        "addRecord",
        "updateRecord",
        "deleteRecord",
        "records",
        "QVariantList",
        "status"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'recordsChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'statusChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sendAddRequest'
        QtMocHelpers::SignalData<void(int, double, double, const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 5 }, { QMetaType::Double, 6 }, { QMetaType::Double, 7 }, { QMetaType::QString, 8 },
        }}),
        // Signal 'sendUpdateRequest'
        QtMocHelpers::SignalData<void(int, double, double, const QString &)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 5 }, { QMetaType::Double, 6 }, { QMetaType::Double, 7 }, { QMetaType::QString, 8 },
        }}),
        // Signal 'sendDeleteRequest'
        QtMocHelpers::SignalData<void(int)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 5 },
        }}),
        // Slot 'onAddResponse'
        QtMocHelpers::SlotData<void(quint8, quint8, quint32, float, float, const QString &)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UChar, 12 }, { QMetaType::UChar, 13 }, { QMetaType::UInt, 5 }, { QMetaType::Float, 6 },
            { QMetaType::Float, 7 }, { QMetaType::QString, 8 },
        }}),
        // Slot 'onDeleteResponse'
        QtMocHelpers::SlotData<void(quint8, quint8, quint32)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UChar, 12 }, { QMetaType::UChar, 13 }, { QMetaType::UInt, 5 },
        }}),
        // Slot 'setStatus'
        QtMocHelpers::SlotData<void(const QString &)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 16 },
        }}),
        // Method 'addRecord'
        QtMocHelpers::MethodData<void(int, double, double, const QString &)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 5 }, { QMetaType::Double, 6 }, { QMetaType::Double, 7 }, { QMetaType::QString, 8 },
        }}),
        // Method 'updateRecord'
        QtMocHelpers::MethodData<void(int, double, double, const QString &)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 5 }, { QMetaType::Double, 6 }, { QMetaType::Double, 7 }, { QMetaType::QString, 8 },
        }}),
        // Method 'deleteRecord'
        QtMocHelpers::MethodData<void(int)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 5 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'records'
        QtMocHelpers::PropertyData<QVariantList>(20, 0x80000000 | 21, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 0),
        // property 'status'
        QtMocHelpers::PropertyData<QString>(22, QMetaType::QString, QMC::DefaultPropertyFlags, 1),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ClientController, qt_meta_tag_ZN16ClientControllerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ClientController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16ClientControllerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16ClientControllerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN16ClientControllerE_t>.metaTypes,
    nullptr
} };

void ClientController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ClientController *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->recordsChanged(); break;
        case 1: _t->statusChanged(); break;
        case 2: _t->sendAddRequest((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4]))); break;
        case 3: _t->sendUpdateRequest((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4]))); break;
        case 4: _t->sendDeleteRequest((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->onAddResponse((*reinterpret_cast<std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<quint8>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<quint32>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<float>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<float>>(_a[5])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[6]))); break;
        case 6: _t->onDeleteResponse((*reinterpret_cast<std::add_pointer_t<quint8>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<quint8>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<quint32>>(_a[3]))); break;
        case 7: _t->setStatus((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->addRecord((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4]))); break;
        case 9: _t->updateRecord((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<double>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4]))); break;
        case 10: _t->deleteRecord((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ClientController::*)()>(_a, &ClientController::recordsChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClientController::*)()>(_a, &ClientController::statusChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClientController::*)(int , double , double , const QString & )>(_a, &ClientController::sendAddRequest, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClientController::*)(int , double , double , const QString & )>(_a, &ClientController::sendUpdateRequest, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ClientController::*)(int )>(_a, &ClientController::sendDeleteRequest, 4))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QVariantList*>(_v) = _t->records(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->status(); break;
        default: break;
        }
    }
}

const QMetaObject *ClientController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16ClientControllerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ClientController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ClientController::recordsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ClientController::statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ClientController::sendAddRequest(int _t1, double _t2, double _t3, const QString & _t4)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2, _t3, _t4);
}

// SIGNAL 3
void ClientController::sendUpdateRequest(int _t1, double _t2, double _t3, const QString & _t4)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2, _t3, _t4);
}

// SIGNAL 4
void ClientController::sendDeleteRequest(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}
QT_WARNING_POP
