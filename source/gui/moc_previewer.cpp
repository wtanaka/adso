/****************************************************************************
** Meta object code from reading C++ file 'previewer.h'
**
** Created: Thu Nov 20 07:16:50 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "previewer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'previewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Previewer[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      21,   11,   10,   10, 0x0a,
      42,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Previewer[] = {
    "Previewer\0\0firstName\0processAdso(QString)\0"
    "populateJavaScriptWindowObject()\0"
};

const QMetaObject Previewer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Previewer,
      qt_meta_data_Previewer, 0 }
};

const QMetaObject *Previewer::metaObject() const
{
    return &staticMetaObject;
}

void *Previewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Previewer))
        return static_cast<void*>(const_cast< Previewer*>(this));
    if (!strcmp(_clname, "Ui::Form"))
        return static_cast< Ui::Form*>(const_cast< Previewer*>(this));
    return QWidget::qt_metacast(_clname);
}

int Previewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: processAdso((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: populateJavaScriptWindowObject(); break;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
