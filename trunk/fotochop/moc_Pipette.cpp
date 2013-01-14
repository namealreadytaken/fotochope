/****************************************************************************
** Meta object code from reading C++ file 'Pipette.h'
**
** Created: Mon 14. Jan 16:32:11 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Pipette.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Pipette.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Pipette[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Pipette[] = {
    "Pipette\0\0on_YUV_toggled()\0"
};

void Pipette::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Pipette *_t = static_cast<Pipette *>(_o);
        switch (_id) {
        case 0: _t->on_YUV_toggled(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Pipette::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Pipette::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Pipette,
      qt_meta_data_Pipette, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Pipette::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Pipette::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Pipette::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Pipette))
        return static_cast<void*>(const_cast< Pipette*>(this));
    return QDialog::qt_metacast(_clname);
}

int Pipette::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
