TEMPLATE = app

QT = core gui widgets

SOURCES = main.cpp mainwidget.cpp
HEADERS = mainwidget.h
FORMS   = mainwidget.ui

INCLUDEPATH += ../../src
LIBS += -L$$OUT_PWD/../../src
CONFIG(debug, debug|release): LIBS += -lmopiqyd
CONFIG(release, debug|release): LIBS += -lmopiqy
