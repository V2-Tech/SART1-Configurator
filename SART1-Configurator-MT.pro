QT       += core gui serialport printsupport concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

VERSION = 1.0.0.0 # major.minor.patch.build

INCLUDEPATH += "c:\fftw-3.3.5"

LIBS += "c:\fftw-3.3.5\libfftw3-3.dll"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cobstrancoder.cpp \
    connectiondialog.cpp \
    fft.cpp \
    imu.cpp \
    qcustomplot.cpp \
    main.cpp \
    mainwindow.cpp \
    serial.cpp \
    usbcommprotocol.cpp

HEADERS += \
    IIM42652.h \
    cobstrancoder.h \
    connectiondialog.h \
    fft.h \
    qcustomplot.h \
    imu.h \
    mainwindow.h \
    serial.h \
    usbcommprotocol.h \
    version.h

FORMS += \
    connectiondialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

RC_ICONS = favicon.ico
