QT       += core gui network printsupport websockets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++
LIBS += -L/usr/local/lib64 -lcrypto  -lssl

SOURCES += \
    httpclient.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    tdclient.cpp \
    tdwebsocketclient.cpp

HEADERS += \
    httpclient.h \
    mainwindow.h \
    qcustomplot.h \
    tdclient.h \
    tdwebsocketclient.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
