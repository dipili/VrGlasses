QT       += core gui widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include (ext_logsystem/LogSystem.pri)

TARGET = MagServer
TEMPLATE = app


SOURCES += \
    main.cpp \
    ScreenStreamer.cpp \
    MainWindow.cpp \
    DeviceConnectionListener.cpp \
    Device.cpp \
    DeviceListModel.cpp \
    Core.cpp \
    DeviceTableModel.cpp

HEADERS  += \
    MainWindow.h \
    ScreenStreamer.h \
    DeviceConnectionListener.h \
    Device.h \
    DeviceListModel.h \
    Core.h \
    DeviceTableModel.h

FORMS    += \
    MainWindow.ui

LIBS     += \
    -lvlc \
    -Ld:/dev/libs/vlc-3.0.0/sdk/lib \
    -Ld:/dev/libs/vlc-3.0.0 \


INCLUDEPATH += \
    d:/dev/libs/vlc-3.0.0/sdk/include
