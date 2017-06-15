QT += core gui
QT += widgets
QT += xml

QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

TARGET = NoteIt
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    notemanager.cpp \
    relationmanager.cpp \
    relation.cpp \
    addcouplediag.cpp \
    treeform.cpp \
    relationwindow.cpp \
    loadsavemanager.cpp

DISTFILES +=

HEADERS += \
    mainwindow.h \
    note.h \
    article.h \
    task.h \
    notemanager.h \
    resource.h \
    relationmanager.h \
    relation.h \
    enums.h \
    addcouplediag.h \
    treeform.h \
    relationwindow.h \
    loadsavemanager.h

FORMS += \
    mainwindow.ui \
    addcouplediag.ui \
    treeform.ui \
    relationwindow.ui

RESOURCES += \
    resource.qrc
