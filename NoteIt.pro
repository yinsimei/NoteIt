QT += core gui
QT += widgets
QT += xml

QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

TARGET = NoteIt
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp

DISTFILES +=

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resource.qrc
