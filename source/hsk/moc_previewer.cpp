/****************************************************************************
** Meta object code from reading C++ file 'previewer.h'
**
** Created: Wed Dec 3 18:47:31 2008
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
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      29,   11,   10,   10, 0x0a,
      59,   10,   10,   10, 0x0a,
      92,   10,   10,   10, 0x0a,
     144,  130,  125,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Previewer[] = {
    "Previewer\0\0userName,userPass\0"
    "registerUser(QString,QString)\0"
    "populateJavaScriptWindowObject()\0"
    "downloadFinished(QNetworkReply*)\0bool\0"
    "filename,data\0saveToDisk(QString,QIODevice*)\0"
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
        case 0: registerUser((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: populateJavaScriptWindowObject(); break;
        case 2: downloadFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 3: { bool _r = saveToDisk((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QIODevice*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
