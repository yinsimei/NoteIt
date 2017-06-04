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
    relationtree.cpp \
    relationnode.cpp \
    relation.cpp

DISTFILES +=

HEADERS += \
    mainwindow.h \
    note.h \
    article.h \
    task.h \
    notemanager.h \
    resource.h \
    relationmanager.h \
    relationtree.h \
    relationnode.h \
    relation.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resource.qrc
