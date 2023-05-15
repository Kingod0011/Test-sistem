QT       += testlib

QT       -= gui

QT += widgets

TARGET = tst_try2test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_try2test.cpp \
    workwithfile.cpp \
    workwithstats.cpp \
    test.cpp \
    testquestion.cpp \
    workwithhistory.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    workwithfile.h \
    workwithstats.h \
    test.h \
    testquestion.h \
    workwithhistory.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
