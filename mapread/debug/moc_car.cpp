/****************************************************************************
** Meta object code from reading C++ file 'car.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../car.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'car.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_car_t {
    QByteArrayData data[32];
    char stringdata0[318];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_car_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_car_t qt_meta_stringdata_car = {
    {
QT_MOC_LITERAL(0, 0, 3), // "car"
QT_MOC_LITERAL(1, 4, 11), // "ConnectSend"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 2), // "ip"
QT_MOC_LITERAL(4, 20, 14), // "DisconnectSend"
QT_MOC_LITERAL(5, 35, 3), // "num"
QT_MOC_LITERAL(6, 39, 18), // "send_task_list_sig"
QT_MOC_LITERAL(7, 58, 4), // "list"
QT_MOC_LITERAL(8, 63, 16), // "send_ctrl_motion"
QT_MOC_LITERAL(9, 80, 2), // "vx"
QT_MOC_LITERAL(10, 83, 1), // "w"
QT_MOC_LITERAL(11, 85, 4), // "time"
QT_MOC_LITERAL(12, 90, 15), // "send_config_par"
QT_MOC_LITERAL(13, 106, 5), // "speed"
QT_MOC_LITERAL(14, 112, 6), // "wspeed"
QT_MOC_LITERAL(15, 119, 3), // "acc"
QT_MOC_LITERAL(16, 123, 4), // "wacc"
QT_MOC_LITERAL(17, 128, 14), // "send_ctrl_stop"
QT_MOC_LITERAL(18, 143, 13), // "car_pausedown"
QT_MOC_LITERAL(19, 157, 10), // "car_resume"
QT_MOC_LITERAL(20, 168, 10), // "car_cancel"
QT_MOC_LITERAL(21, 179, 13), // "send_car_task"
QT_MOC_LITERAL(22, 193, 3), // "pot"
QT_MOC_LITERAL(23, 197, 4), // "mode"
QT_MOC_LITERAL(24, 202, 11), // "frame_floor"
QT_MOC_LITERAL(25, 214, 9), // "car_floor"
QT_MOC_LITERAL(26, 224, 12), // "send_car_pot"
QT_MOC_LITERAL(27, 237, 5), // "point"
QT_MOC_LITERAL(28, 243, 13), // "send_car_roll"
QT_MOC_LITERAL(29, 257, 14), // "send_car_reset"
QT_MOC_LITERAL(30, 272, 20), // "send_car_control_get"
QT_MOC_LITERAL(31, 293, 24) // "send_car_control_release"

    },
    "car\0ConnectSend\0\0ip\0DisconnectSend\0"
    "num\0send_task_list_sig\0list\0"
    "send_ctrl_motion\0vx\0w\0time\0send_config_par\0"
    "speed\0wspeed\0acc\0wacc\0send_ctrl_stop\0"
    "car_pausedown\0car_resume\0car_cancel\0"
    "send_car_task\0pot\0mode\0frame_floor\0"
    "car_floor\0send_car_pot\0point\0send_car_roll\0"
    "send_car_reset\0send_car_control_get\0"
    "send_car_control_release"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_car[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      19,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  109,    2, 0x06 /* Public */,
       4,    1,  112,    2, 0x06 /* Public */,
       6,    1,  115,    2, 0x06 /* Public */,
       8,    3,  118,    2, 0x06 /* Public */,
       8,    2,  125,    2, 0x26 /* Public | MethodCloned */,
       8,    1,  130,    2, 0x26 /* Public | MethodCloned */,
      12,    4,  133,    2, 0x06 /* Public */,
      17,    0,  142,    2, 0x06 /* Public */,
      18,    0,  143,    2, 0x06 /* Public */,
      19,    0,  144,    2, 0x06 /* Public */,
      20,    0,  145,    2, 0x06 /* Public */,
      21,    4,  146,    2, 0x06 /* Public */,
      21,    3,  155,    2, 0x26 /* Public | MethodCloned */,
      21,    2,  162,    2, 0x26 /* Public | MethodCloned */,
      26,    1,  167,    2, 0x06 /* Public */,
      28,    2,  170,    2, 0x06 /* Public */,
      29,    0,  175,    2, 0x06 /* Public */,
      30,    0,  176,    2, 0x06 /* Public */,
      31,    0,  177,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::QStringList,    7,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    9,   10,   11,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,    9,   10,
    QMetaType::Void, QMetaType::Double,    9,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,   13,   14,   15,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   24,   25,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   24,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   22,   23,
    QMetaType::Void, QMetaType::QString,   27,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   22,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void car::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        car *_t = static_cast<car *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ConnectSend((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->DisconnectSend((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->send_task_list_sig((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 3: _t->send_ctrl_motion((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 4: _t->send_ctrl_motion((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 5: _t->send_ctrl_motion((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->send_config_par((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 7: _t->send_ctrl_stop(); break;
        case 8: _t->car_pausedown(); break;
        case 9: _t->car_resume(); break;
        case 10: _t->car_cancel(); break;
        case 11: _t->send_car_task((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 12: _t->send_car_task((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 13: _t->send_car_task((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: _t->send_car_pot((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: _t->send_car_roll((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 16: _t->send_car_reset(); break;
        case 17: _t->send_car_control_get(); break;
        case 18: _t->send_car_control_release(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (car::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&car::ConnectSend)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (car::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&car::DisconnectSend)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (car::*_t)(QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&car::send_task_list_sig)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (car::*_t)(double , double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&car::send_ctrl_motion)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (car::*_t)(double , double , double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&car::send_config_par)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (car::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&car::send_ctrl_stop)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (car::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&car::car_pausedown)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (car::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&car::car_resume)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (car::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&car::car_cancel)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (car::*_t)(int , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&car::send_car_task)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (car::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&car::send_car_pot)) {
                *result = 14;
                return;
            }
        }
        {
            typedef void (car::*_t)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&car::send_car_roll)) {
                *result = 15;
                return;
            }
        }
        {
            typedef void (car::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&car::send_car_reset)) {
                *result = 16;
                return;
            }
        }
        {
            typedef void (car::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&car::send_car_control_get)) {
                *result = 17;
                return;
            }
        }
        {
            typedef void (car::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&car::send_car_control_release)) {
                *result = 18;
                return;
            }
        }
    }
}

const QMetaObject car::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_car.data,
      qt_meta_data_car,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *car::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *car::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_car.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int car::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void car::ConnectSend(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void car::DisconnectSend(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void car::send_task_list_sig(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void car::send_ctrl_motion(double _t1, double _t2, double _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 6
void car::send_config_par(double _t1, double _t2, double _t3, double _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void car::send_ctrl_stop()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void car::car_pausedown()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void car::car_resume()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void car::car_cancel()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void car::send_car_task(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 14
void car::send_car_pot(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void car::send_car_roll(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void car::send_car_reset()
{
    QMetaObject::activate(this, &staticMetaObject, 16, nullptr);
}

// SIGNAL 17
void car::send_car_control_get()
{
    QMetaObject::activate(this, &staticMetaObject, 17, nullptr);
}

// SIGNAL 18
void car::send_car_control_release()
{
    QMetaObject::activate(this, &staticMetaObject, 18, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
