/****************************************************************************
** Meta object code from reading C++ file 'Histogramme.h'
**
** Created: Tue 15. Jan 18:26:34 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Histogramme.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Histogramme.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Histogramme[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      38,   12,   12,   12, 0x0a,
      63,   12,   12,   12, 0x0a,
      88,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Histogramme[] = {
    "Histogramme\0\0on_checkR_stateChanged()\0"
    "on_checkG_stateChanged()\0"
    "on_checkB_stateChanged()\0on_YUVradio_toggled()\0"
};

void Histogramme::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Histogramme *_t = static_cast<Histogramme *>(_o);
        switch (_id) {
        case 0: _t->on_checkR_stateChanged(); break;
        case 1: _t->on_checkG_stateChanged(); break;
        case 2: _t->on_checkB_stateChanged(); break;
        case 3: _t->on_YUVradio_toggled(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Histogramme::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Histogramme::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Histogramme,
      qt_meta_data_Histogramme, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Histogramme::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Histogramme::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Histogramme::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Histogramme))
        return static_cast<void*>(const_cast< Histogramme*>(this));
    return QDialog::qt_metacast(_clname);
}

int Histogramme::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
