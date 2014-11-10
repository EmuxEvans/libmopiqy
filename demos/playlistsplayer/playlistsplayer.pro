TEMPLATE = app

QT = core gui widgets
macx: QT += websockets

CONFIG += c++11

SOURCES = main.cpp mainwidget.cpp
HEADERS = mainwidget.h
FORMS   = mainwidget.ui

INCLUDEPATH += ../../src

win32 {
    CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../src/debug -lmopiqyd
    CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../src/release -lmopiqy
}
unix {
    LIBS += -L$$OUT_PWD/../../src
    CONFIG(debug, debug|release): LIBS += -lmopiqyd
    CONFIG(release, debug|release): LIBS += -lmopiqy
}
