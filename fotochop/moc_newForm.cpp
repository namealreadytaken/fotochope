/****************************************************************************
** Meta object code from reading C++ file 'newForm.h'
**
** Created: Tue 15. Jan 18:26:36 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "newForm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'newForm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_newForm[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      33,    8,    8,    8, 0x0a,
      57,    8,    8,    8, 0x0a,
      81,    8,    8,    8, 0x0a,
     107,    8,    8,    8, 0x0a,
     134,    8,    8,    8, 0x0a,
     158,    8,    8,    8, 0x0a,
     182,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_newForm[] = {
    "newForm\0\0on_loadButton_clicked()\0"
    "on_cropButton_clicked()\0on_saveButton_clicked()\0"
    "on_resizeButton_clicked()\0"
    "on_pipetteButton_clicked()\0"
    "on_greyButton_clicked()\0on_blurButton_clicked()\0"
    "on_histoButton_clicked()\0"
};

void newForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        newForm *_t = static_cast<newForm *>(_o);
        switch (_id) {
        case 0: _t->on_loadButton_clicked(); break;
        case 1: _t->on_cropButton_clicked(); break;
        case 2: _t->on_saveButton_clicked(); break;
        case 3: _t->on_resizeButton_clicked(); break;
        case 4: _t->on_pipetteButton_clicked(); break;
        case 5: _t->on_greyButton_clicked(); break;
        case 6: _t->on_blurButton_clicked(); break;
        case 7: _t->on_histoButton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData newForm::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject newForm::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_newForm,
      qt_meta_data_newForm, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &newForm::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *newForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *newForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_newForm))
        return static_cast<void*>(const_cast< newForm*>(this));
    return QDialog::qt_metacast(_clname);
}

int newForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
