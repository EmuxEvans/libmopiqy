INCLUDEPATH += ../../ ../

#
# Platform dependant config
#
unix {
    LIBS += -L../../mopiqy_core -lmopiqy_core
    DESTDIR = ../tst_bin
}

win32 {
    LIBS += -L../../bin
    DESTDIR = ../../bin

    CONFIG(debug, debug|release): LIBS += -lmopiqy_cored
    CONFIG(release, debug|release): LIBS += -lmopiqy_core
}
