INCLUDEPATH += $${PWD}/src

win32 {
    CONFIG(debug, debug|release): LIBS += -lmopiqyd0
    CONFIG(release, debug|release): LIBS += -lmopiqy0
}
unix {
    CONFIG(debug, debug|release): LIBS += -lmopiqyd
    CONFIG(release, debug|release): LIBS += -lmopiqy
}
