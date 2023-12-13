QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

DESTDIR = $$PWD/bin

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += ./headfile
               $$PWD/libmodbus

SOURCES += sourcefile/main.cpp \
    sourcefile/cJSON.c \
    sourcefile/car.cpp \
    sourcefile/communicate_test.cpp \
    sourcefile/mainwindow.cpp \
    sourcefile/map_read.cpp \
    sourcefile/qcustomplot.cpp \
    sourcefile/car_tcp.cpp

HEADERS +=  headfile/mainwindow.h \
    headfile/cJSON.h \
    headfile/car_test.h \
    headfile/communicate_test.h \
    headfile/map_read.h \
    headfile/qcustomplot.h \
    headfile/car_tcp.h

FORMS += \
    mainwindow.ui

LIBS += -lws2_32\
        -luser32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    nav.png


