/****************************************************************************
** Meta object code from reading C++ file 'showimage.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../EBTS/showimage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'showimage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ShowImage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      25,   10,   10,   10, 0x05,
      39,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      57,   10,   10,   10, 0x0a,
      76,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ShowImage[] = {
    "ShowImage\0\0get2end(bool)\0get2beg(bool)\0"
    "turn2default(int)\0init_path(QString)\0"
    "arise_scale(int)\0"
};

void ShowImage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ShowImage *_t = static_cast<ShowImage *>(_o);
        switch (_id) {
        case 0: _t->get2end((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->get2beg((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->turn2default((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->init_path((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->arise_scale((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ShowImage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ShowImage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ShowImage,
      qt_meta_data_ShowImage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ShowImage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ShowImage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ShowImage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ShowImage))
        return static_cast<void*>(const_cast< ShowImage*>(this));
    return QWidget::qt_metacast(_clname);
}

int ShowImage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ShowImage::get2end(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ShowImage::get2beg(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ShowImage::turn2default(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
