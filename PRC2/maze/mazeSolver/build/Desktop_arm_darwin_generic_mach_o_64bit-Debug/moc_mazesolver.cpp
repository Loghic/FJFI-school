/****************************************************************************
** Meta object code from reading C++ file 'mazesolver.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mazesolver.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mazesolver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMazeSolverENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMazeSolverENDCLASS = QtMocHelpers::stringData(
    "MazeSolver",
    "onLoadFileClicked",
    "",
    "onCellSizeChanged",
    "onMazeLoaded",
    "onSolveClicked",
    "onCoordsChanged",
    "onSbSpeedChange",
    "onTimeout",
    "onResetClicked",
    "onAlgorthimsChanged"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMazeSolverENDCLASS_t {
    uint offsetsAndSizes[22];
    char stringdata0[11];
    char stringdata1[18];
    char stringdata2[1];
    char stringdata3[18];
    char stringdata4[13];
    char stringdata5[15];
    char stringdata6[16];
    char stringdata7[16];
    char stringdata8[10];
    char stringdata9[15];
    char stringdata10[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMazeSolverENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMazeSolverENDCLASS_t qt_meta_stringdata_CLASSMazeSolverENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MazeSolver"
        QT_MOC_LITERAL(11, 17),  // "onLoadFileClicked"
        QT_MOC_LITERAL(29, 0),  // ""
        QT_MOC_LITERAL(30, 17),  // "onCellSizeChanged"
        QT_MOC_LITERAL(48, 12),  // "onMazeLoaded"
        QT_MOC_LITERAL(61, 14),  // "onSolveClicked"
        QT_MOC_LITERAL(76, 15),  // "onCoordsChanged"
        QT_MOC_LITERAL(92, 15),  // "onSbSpeedChange"
        QT_MOC_LITERAL(108, 9),  // "onTimeout"
        QT_MOC_LITERAL(118, 14),  // "onResetClicked"
        QT_MOC_LITERAL(133, 19)   // "onAlgorthimsChanged"
    },
    "MazeSolver",
    "onLoadFileClicked",
    "",
    "onCellSizeChanged",
    "onMazeLoaded",
    "onSolveClicked",
    "onCoordsChanged",
    "onSbSpeedChange",
    "onTimeout",
    "onResetClicked",
    "onAlgorthimsChanged"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMazeSolverENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x08,    1 /* Private */,
       3,    0,   69,    2, 0x08,    2 /* Private */,
       4,    0,   70,    2, 0x08,    3 /* Private */,
       5,    0,   71,    2, 0x08,    4 /* Private */,
       6,    0,   72,    2, 0x08,    5 /* Private */,
       7,    0,   73,    2, 0x08,    6 /* Private */,
       8,    0,   74,    2, 0x08,    7 /* Private */,
       9,    0,   75,    2, 0x08,    8 /* Private */,
      10,    0,   76,    2, 0x08,    9 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MazeSolver::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMazeSolverENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMazeSolverENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMazeSolverENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MazeSolver, std::true_type>,
        // method 'onLoadFileClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCellSizeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMazeLoaded'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSolveClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCoordsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSbSpeedChange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onTimeout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onResetClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onAlgorthimsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MazeSolver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MazeSolver *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onLoadFileClicked(); break;
        case 1: _t->onCellSizeChanged(); break;
        case 2: _t->onMazeLoaded(); break;
        case 3: _t->onSolveClicked(); break;
        case 4: _t->onCoordsChanged(); break;
        case 5: _t->onSbSpeedChange(); break;
        case 6: _t->onTimeout(); break;
        case 7: _t->onResetClicked(); break;
        case 8: _t->onAlgorthimsChanged(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *MazeSolver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MazeSolver::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMazeSolverENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MazeSolver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
