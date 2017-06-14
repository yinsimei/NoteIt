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
    note.cpp \
    article.cpp \
    task.cpp \
    notemanager.cpp \
    relationmanager.cpp \
    relation.cpp \
    resource.cpp \
    addcouplediag.cpp

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
    addcouplediag.h

FORMS += \
    mainwindow.ui \
    addcouplediag.ui

RESOURCES += \
    resource.qrc
