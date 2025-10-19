/****************************************************************************
** Meta object code from reading C++ file 'crecordingwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.15)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../MapDisplay/crecordingwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'crecordingwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.15. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CRecordingWidget_t {
    QByteArrayData data[23];
    char stringdata0[320];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CRecordingWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CRecordingWidget_t qt_meta_stringdata_CRecordingWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CRecordingWidget"
QT_MOC_LITERAL(1, 17, 15), // "replayTrackData"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 15), // "stTrackRecvInfo"
QT_MOC_LITERAL(4, 50, 5), // "track"
QT_MOC_LITERAL(5, 56, 14), // "startRecording"
QT_MOC_LITERAL(6, 71, 13), // "stopRecording"
QT_MOC_LITERAL(7, 85, 14), // "pauseRecording"
QT_MOC_LITERAL(8, 100, 11), // "startReplay"
QT_MOC_LITERAL(9, 112, 10), // "stopReplay"
QT_MOC_LITERAL(10, 123, 11), // "pauseReplay"
QT_MOC_LITERAL(11, 135, 15), // "recordTrackData"
QT_MOC_LITERAL(12, 151, 11), // "replayFrame"
QT_MOC_LITERAL(13, 163, 19), // "onRecordingSelected"
QT_MOC_LITERAL(14, 183, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(15, 200, 4), // "item"
QT_MOC_LITERAL(16, 205, 15), // "deleteRecording"
QT_MOC_LITERAL(17, 221, 15), // "exportRecording"
QT_MOC_LITERAL(18, 237, 17), // "refreshRecordings"
QT_MOC_LITERAL(19, 255, 20), // "onReplaySpeedChanged"
QT_MOC_LITERAL(20, 276, 5), // "index"
QT_MOC_LITERAL(21, 282, 16), // "openReplayWindow"
QT_MOC_LITERAL(22, 299, 20) // "onReplayWindowClosed"

    },
    "CRecordingWidget\0replayTrackData\0\0"
    "stTrackRecvInfo\0track\0startRecording\0"
    "stopRecording\0pauseRecording\0startReplay\0"
    "stopReplay\0pauseReplay\0recordTrackData\0"
    "replayFrame\0onRecordingSelected\0"
    "QListWidgetItem*\0item\0deleteRecording\0"
    "exportRecording\0refreshRecordings\0"
    "onReplaySpeedChanged\0index\0openReplayWindow\0"
    "onReplayWindowClosed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CRecordingWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   97,    2, 0x0a /* Public */,
       6,    0,   98,    2, 0x0a /* Public */,
       7,    0,   99,    2, 0x0a /* Public */,
       8,    0,  100,    2, 0x0a /* Public */,
       9,    0,  101,    2, 0x0a /* Public */,
      10,    0,  102,    2, 0x0a /* Public */,
      11,    0,  103,    2, 0x08 /* Private */,
      12,    0,  104,    2, 0x08 /* Private */,
      13,    1,  105,    2, 0x08 /* Private */,
      16,    0,  108,    2, 0x08 /* Private */,
      17,    0,  109,    2, 0x08 /* Private */,
      18,    0,  110,    2, 0x08 /* Private */,
      19,    1,  111,    2, 0x08 /* Private */,
      21,    0,  114,    2, 0x08 /* Private */,
      22,    0,  115,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CRecordingWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CRecordingWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->replayTrackData((*reinterpret_cast< stTrackRecvInfo(*)>(_a[1]))); break;
        case 1: _t->startRecording(); break;
        case 2: _t->stopRecording(); break;
        case 3: _t->pauseRecording(); break;
        case 4: _t->startReplay(); break;
        case 5: _t->stopReplay(); break;
        case 6: _t->pauseReplay(); break;
        case 7: _t->recordTrackData(); break;
        case 8: _t->replayFrame(); break;
        case 9: _t->onRecordingSelected((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 10: _t->deleteRecording(); break;
        case 11: _t->exportRecording(); break;
        case 12: _t->refreshRecordings(); break;
        case 13: _t->onReplaySpeedChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->openReplayWindow(); break;
        case 15: _t->onReplayWindowClosed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CRecordingWidget::*)(stTrackRecvInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CRecordingWidget::replayTrackData)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CRecordingWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QDockWidget::staticMetaObject>(),
    qt_meta_stringdata_CRecordingWidget.data,
    qt_meta_data_CRecordingWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CRecordingWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CRecordingWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CRecordingWidget.stringdata0))
        return static_cast<void*>(this);
    return QDockWidget::qt_metacast(_clname);
}

int CRecordingWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void CRecordingWidget::replayTrackData(stTrackRecvInfo _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
