/****************************************************************************
** Meta object code from reading C++ file 'myreceivedata.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../vcu_full_function_detection_v2.2/myAnalysis/myreceivedata.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myreceivedata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_myreceivedata_t {
    QByteArrayData data[10];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myreceivedata_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myreceivedata_t qt_meta_stringdata_myreceivedata = {
    {
QT_MOC_LITERAL(0, 0, 13), // "myreceivedata"
QT_MOC_LITERAL(1, 14, 12), // "ResultSignal"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 15), // "DetectionResult"
QT_MOC_LITERAL(4, 44, 10), // "ResultData"
QT_MOC_LITERAL(5, 55, 10), // "resultFlag"
QT_MOC_LITERAL(6, 66, 9), // "stateData"
QT_MOC_LITERAL(7, 76, 14), // "ReceiveCanData"
QT_MOC_LITERAL(8, 91, 11), // "VCI_CAN_OBJ"
QT_MOC_LITERAL(9, 103, 5) // "frame"

    },
    "myreceivedata\0ResultSignal\0\0DetectionResult\0"
    "ResultData\0resultFlag\0stateData\0"
    "ReceiveCanData\0VCI_CAN_OBJ\0frame"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myreceivedata[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::QString,    4,    5,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void myreceivedata::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<myreceivedata *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ResultSignal((*reinterpret_cast< const DetectionResult(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->ReceiveCanData((*reinterpret_cast< const VCI_CAN_OBJ(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (myreceivedata::*)(const DetectionResult & , int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myreceivedata::ResultSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject myreceivedata::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_myreceivedata.data,
    qt_meta_data_myreceivedata,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *myreceivedata::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myreceivedata::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myreceivedata.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int myreceivedata::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void myreceivedata::ResultSignal(const DetectionResult & _t1, int _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
