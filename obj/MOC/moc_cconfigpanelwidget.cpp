/****************************************************************************
** Meta object code from reading C++ file 'cconfigpanelwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.15)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../MapDisplay/cconfigpanelwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cconfigpanelwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.15. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CConfigPanelWidget_t {
    QByteArrayData data[24];
    char stringdata0[330];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CConfigPanelWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CConfigPanelWidget_t qt_meta_stringdata_CConfigPanelWidget = {
    {
QT_MOC_LITERAL(0, 0, 18), // "CConfigPanelWidget"
QT_MOC_LITERAL(1, 19, 16), // "mapHomeRequested"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 17), // "openMapsRequested"
QT_MOC_LITERAL(4, 55, 14), // "flushRequested"
QT_MOC_LITERAL(5, 70, 13), // "exitRequested"
QT_MOC_LITERAL(6, 84, 16), // "zoomLevelChanged"
QT_MOC_LITERAL(7, 101, 4), // "zoom"
QT_MOC_LITERAL(8, 106, 14), // "opacityChanged"
QT_MOC_LITERAL(9, 121, 7), // "opacity"
QT_MOC_LITERAL(10, 129, 16), // "trackSizeChanged"
QT_MOC_LITERAL(11, 146, 4), // "size"
QT_MOC_LITERAL(12, 151, 18), // "trackFilterChanged"
QT_MOC_LITERAL(13, 170, 10), // "showFriend"
QT_MOC_LITERAL(14, 181, 11), // "showHostile"
QT_MOC_LITERAL(15, 193, 11), // "showUnknown"
QT_MOC_LITERAL(16, 205, 21), // "animationSpeedChanged"
QT_MOC_LITERAL(17, 227, 5), // "speed"
QT_MOC_LITERAL(18, 233, 21), // "gridVisibilityChanged"
QT_MOC_LITERAL(19, 255, 7), // "visible"
QT_MOC_LITERAL(20, 263, 24), // "compassVisibilityChanged"
QT_MOC_LITERAL(21, 288, 15), // "chartsRequested"
QT_MOC_LITERAL(22, 304, 19), // "historyLimitChanged"
QT_MOC_LITERAL(23, 324, 5) // "limit"

    },
    "CConfigPanelWidget\0mapHomeRequested\0"
    "\0openMapsRequested\0flushRequested\0"
    "exitRequested\0zoomLevelChanged\0zoom\0"
    "opacityChanged\0opacity\0trackSizeChanged\0"
    "size\0trackFilterChanged\0showFriend\0"
    "showHostile\0showUnknown\0animationSpeedChanged\0"
    "speed\0gridVisibilityChanged\0visible\0"
    "compassVisibilityChanged\0chartsRequested\0"
    "historyLimitChanged\0limit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CConfigPanelWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    0,   80,    2, 0x06 /* Public */,
       4,    0,   81,    2, 0x06 /* Public */,
       5,    0,   82,    2, 0x06 /* Public */,
       6,    1,   83,    2, 0x06 /* Public */,
       8,    1,   86,    2, 0x06 /* Public */,
      10,    1,   89,    2, 0x06 /* Public */,
      12,    3,   92,    2, 0x06 /* Public */,
      16,    1,   99,    2, 0x06 /* Public */,
      18,    1,  102,    2, 0x06 /* Public */,
      20,    1,  105,    2, 0x06 /* Public */,
      21,    0,  108,    2, 0x06 /* Public */,
      22,    1,  109,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,   13,   14,   15,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   23,

       0        // eod
};

void CConfigPanelWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CConfigPanelWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->mapHomeRequested(); break;
        case 1: _t->openMapsRequested(); break;
        case 2: _t->flushRequested(); break;
        case 3: _t->exitRequested(); break;
        case 4: _t->zoomLevelChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->opacityChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->trackSizeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->trackFilterChanged((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 8: _t->animationSpeedChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->gridVisibilityChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->compassVisibilityChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->chartsRequested(); break;
        case 12: _t->historyLimitChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CConfigPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CConfigPanelWidget::mapHomeRequested)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CConfigPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CConfigPanelWidget::openMapsRequested)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CConfigPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CConfigPanelWidget::flushRequested)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CConfigPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CConfigPanelWidget::exitRequested)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CConfigPanelWidget::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CConfigPanelWidget::zoomLevelChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (CConfigPanelWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CConfigPanelWidget::opacityChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (CConfigPanelWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CConfigPanelWidget::trackSizeChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (CConfigPanelWidget::*)(bool , bool , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CConfigPanelWidget::trackFilterChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (CConfigPanelWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CConfigPanelWidget::animationSpeedChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (CConfigPanelWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CConfigPanelWidget::gridVisibilityChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (CConfigPanelWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CConfigPanelWidget::compassVisibilityChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (CConfigPanelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CConfigPanelWidget::chartsRequested)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (CConfigPanelWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CConfigPanelWidget::historyLimitChanged)) {
                *result = 12;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CConfigPanelWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QDockWidget::staticMetaObject>(),
    qt_meta_stringdata_CConfigPanelWidget.data,
    qt_meta_data_CConfigPanelWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CConfigPanelWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CConfigPanelWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CConfigPanelWidget.stringdata0))
        return static_cast<void*>(this);
    return QDockWidget::qt_metacast(_clname);
}

int CConfigPanelWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void CConfigPanelWidget::mapHomeRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CConfigPanelWidget::openMapsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CConfigPanelWidget::flushRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void CConfigPanelWidget::exitRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void CConfigPanelWidget::zoomLevelChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CConfigPanelWidget::opacityChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void CConfigPanelWidget::trackSizeChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void CConfigPanelWidget::trackFilterChanged(bool _t1, bool _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void CConfigPanelWidget::animationSpeedChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void CConfigPanelWidget::gridVisibilityChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void CConfigPanelWidget::compassVisibilityChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void CConfigPanelWidget::chartsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void CConfigPanelWidget::historyLimitChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
