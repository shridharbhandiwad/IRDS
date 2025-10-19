/****************************************************************************
** Meta object code from reading C++ file 'csimulationwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.15)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../MapDisplay/csimulationwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'csimulationwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.15. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CSimulationWidget_t {
    QByteArrayData data[20];
    char stringdata0[276];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CSimulationWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CSimulationWidget_t qt_meta_stringdata_CSimulationWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "CSimulationWidget"
QT_MOC_LITERAL(1, 18, 18), // "simulatedTrackData"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 15), // "stTrackRecvInfo"
QT_MOC_LITERAL(4, 54, 5), // "track"
QT_MOC_LITERAL(5, 60, 15), // "startSimulation"
QT_MOC_LITERAL(6, 76, 14), // "stopSimulation"
QT_MOC_LITERAL(7, 91, 15), // "pauseSimulation"
QT_MOC_LITERAL(8, 107, 15), // "resetSimulation"
QT_MOC_LITERAL(9, 123, 16), // "updateSimulation"
QT_MOC_LITERAL(10, 140, 19), // "onTrackCountChanged"
QT_MOC_LITERAL(11, 160, 5), // "count"
QT_MOC_LITERAL(12, 166, 17), // "onMaxRangeChanged"
QT_MOC_LITERAL(13, 184, 5), // "range"
QT_MOC_LITERAL(14, 190, 19), // "onUpdateRateChanged"
QT_MOC_LITERAL(15, 210, 4), // "rate"
QT_MOC_LITERAL(16, 215, 22), // "onAzimuthSpreadChanged"
QT_MOC_LITERAL(17, 238, 6), // "spread"
QT_MOC_LITERAL(18, 245, 13), // "sendTrackData"
QT_MOC_LITERAL(19, 259, 16) // "updateTrackTable"

    },
    "CSimulationWidget\0simulatedTrackData\0"
    "\0stTrackRecvInfo\0track\0startSimulation\0"
    "stopSimulation\0pauseSimulation\0"
    "resetSimulation\0updateSimulation\0"
    "onTrackCountChanged\0count\0onMaxRangeChanged\0"
    "range\0onUpdateRateChanged\0rate\0"
    "onAzimuthSpreadChanged\0spread\0"
    "sendTrackData\0updateTrackTable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CSimulationWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   77,    2, 0x0a /* Public */,
       6,    0,   78,    2, 0x0a /* Public */,
       7,    0,   79,    2, 0x0a /* Public */,
       8,    0,   80,    2, 0x0a /* Public */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    1,   82,    2, 0x08 /* Private */,
      12,    1,   85,    2, 0x08 /* Private */,
      14,    1,   88,    2, 0x08 /* Private */,
      16,    1,   91,    2, 0x08 /* Private */,
      18,    1,   94,    2, 0x08 /* Private */,
      19,    0,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Double,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

       0        // eod
};

void CSimulationWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CSimulationWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->simulatedTrackData((*reinterpret_cast< stTrackRecvInfo(*)>(_a[1]))); break;
        case 1: _t->startSimulation(); break;
        case 2: _t->stopSimulation(); break;
        case 3: _t->pauseSimulation(); break;
        case 4: _t->resetSimulation(); break;
        case 5: _t->updateSimulation(); break;
        case 6: _t->onTrackCountChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->onMaxRangeChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->onUpdateRateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->onAzimuthSpreadChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->sendTrackData((*reinterpret_cast< const stTrackRecvInfo(*)>(_a[1]))); break;
        case 11: _t->updateTrackTable(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CSimulationWidget::*)(stTrackRecvInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CSimulationWidget::simulatedTrackData)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CSimulationWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QDockWidget::staticMetaObject>(),
    qt_meta_stringdata_CSimulationWidget.data,
    qt_meta_data_CSimulationWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CSimulationWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CSimulationWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CSimulationWidget.stringdata0))
        return static_cast<void*>(this);
    return QDockWidget::qt_metacast(_clname);
}

int CSimulationWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void CSimulationWidget::simulatedTrackData(stTrackRecvInfo _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
