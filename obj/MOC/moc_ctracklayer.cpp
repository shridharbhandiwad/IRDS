/****************************************************************************
** Meta object code from reading C++ file 'ctracklayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.15)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../MapDisplay/ctracklayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ctracklayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.15. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CTrackLayer_t {
    QByteArrayData data[11];
    char stringdata0[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CTrackLayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CTrackLayer_t qt_meta_stringdata_CTrackLayer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "CTrackLayer"
QT_MOC_LITERAL(1, 12, 17), // "trackRightClicked"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 7), // "trackId"
QT_MOC_LITERAL(4, 39, 9), // "globalPos"
QT_MOC_LITERAL(5, 49, 16), // "_UpdateAnimation"
QT_MOC_LITERAL(6, 66, 12), // "onFocusTrack"
QT_MOC_LITERAL(7, 79, 13), // "onDeleteTrack"
QT_MOC_LITERAL(8, 93, 16), // "onLoadTrackImage"
QT_MOC_LITERAL(9, 110, 20), // "onToggleTrackHistory"
QT_MOC_LITERAL(10, 131, 16) // "onHighlightTrack"

    },
    "CTrackLayer\0trackRightClicked\0\0trackId\0"
    "globalPos\0_UpdateAnimation\0onFocusTrack\0"
    "onDeleteTrack\0onLoadTrackImage\0"
    "onToggleTrackHistory\0onHighlightTrack"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CTrackLayer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   54,    2, 0x08 /* Private */,
       6,    0,   55,    2, 0x08 /* Private */,
       7,    0,   56,    2, 0x08 /* Private */,
       8,    0,   57,    2, 0x08 /* Private */,
       9,    0,   58,    2, 0x08 /* Private */,
      10,    0,   59,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QPoint,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CTrackLayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CTrackLayer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->trackRightClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QPoint(*)>(_a[2]))); break;
        case 1: _t->_UpdateAnimation(); break;
        case 2: _t->onFocusTrack(); break;
        case 3: _t->onDeleteTrack(); break;
        case 4: _t->onLoadTrackImage(); break;
        case 5: _t->onToggleTrackHistory(); break;
        case 6: _t->onHighlightTrack(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CTrackLayer::*)(int , const QPoint & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CTrackLayer::trackRightClicked)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CTrackLayer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CTrackLayer.data,
    qt_meta_data_CTrackLayer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CTrackLayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CTrackLayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CTrackLayer.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QgsMapCanvasItem"))
        return static_cast< QgsMapCanvasItem*>(this);
    return QObject::qt_metacast(_clname);
}

int CTrackLayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void CTrackLayer::trackRightClicked(int _t1, const QPoint & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
