INCLUDEPATH += $${PWD}/src
CONFIG += c++11

win32 {
    CONFIG(debug, debug|release): LIBS += -lmopiqyd0
    CONFIG(release, debug|release): LIBS += -lmopiqy0
}
unix {
    LIBS += -lmopiqy
}
