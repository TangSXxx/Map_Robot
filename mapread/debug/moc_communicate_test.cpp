/****************************************************************************
** Meta object code from reading C++ file 'communicate_test.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../communicate_test.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'communicate_test.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MapThread_t {
    QByteArrayData data[10];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MapThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MapThread_t qt_meta_stringdata_MapThread = {
    {
QT_MOC_LITERAL(0, 0, 9), // "MapThread"
QT_MOC_LITERAL(1, 10, 10), // "recv_value"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 1), // "x"
QT_MOC_LITERAL(4, 24, 1), // "y"
QT_MOC_LITERAL(5, 26, 5), // "angle"
QT_MOC_LITERAL(6, 32, 14), // "got_currentmap"
QT_MOC_LITERAL(7, 47, 10), // "connect_OK"
QT_MOC_LITERAL(8, 58, 11), // "Stop_thread"
QT_MOC_LITERAL(9, 70, 3) // "num"

    },
    "MapThread\0recv_value\0\0x\0y\0angle\0"
    "got_currentmap\0connect_OK\0Stop_thread\0"
    "num"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MapThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   34,    2, 0x06 /* Public */,
       6,    0,   41,    2, 0x06 /* Public */,
       7,    0,   42,    2, 0x06 /* Public */,
       8,    1,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    3,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,

       0        // eod
};

void MapThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MapThread *_t = static_cast<MapThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->recv_value((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 1: _t->got_currentmap(); break;
        case 2: _t->connect_OK(); break;
        case 3: _t->Stop_thread((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MapThread::*_t)(double , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MapThread::recv_value)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MapThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MapThread::got_currentmap)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MapThread::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MapThread::connect_OK)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MapThread::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MapThread::Stop_thread)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject MapThread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MapThread.data,
      qt_meta_data_MapThread,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MapThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MapThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MapThread.stringdata0))
        return static_cast<void*>(const_cast< MapThread*>(this));
    return QObject::qt_metacast(_clname);
}

int MapThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MapThread::recv_value(double _t1, double _t2, double _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MapThread::got_currentmap()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MapThread::connect_OK()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MapThread::Stop_thread(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
