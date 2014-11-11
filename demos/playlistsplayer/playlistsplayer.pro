TEMPLATE = app

QT = core gui widgets
macx: QT += websockets

CONFIG += c++11

SOURCES = main.cpp mainwidget.cpp
HEADERS = mainwidget.h
FORMS   = mainwidget.ui

include(../../libmopiqy.pri)
LIBS += -L$$OUT_PWD/../../src
