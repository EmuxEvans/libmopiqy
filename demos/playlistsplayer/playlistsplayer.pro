TEMPLATE = app

QT = core gui widgets
macx: QT += websockets

CONFIG += c++11

SOURCES = main.cpp mainwidget.cpp
HEADERS = mainwidget.h
FORMS   = mainwidget.ui

INCLUDEPATH += ../../src
CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../src/debug -lmopiqyd0
CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../src/release -lmopiqy0
