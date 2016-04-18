TARGET = TestGstreamer
CONFIG += console
CONFIG -= app_bundle

#CONFIG += link_pkgconfig
#PKGCONFIG += QtGStreamer-1.0

TEMPLATE = app

SOURCES += main.cpp

unix {
    GSTREAMER_INCLUDE_PATH=/opt/gstreamer-sdk
    GSTREAMER_LIB_PATH=/opt/gstreamer-sdk
}
win32 {
    GSTREAMER_INCLUDE_PATH=D:/gstreamer/1.0/x86
    GSTREAMER_LIB_PATH=D:/gstreamer/1.0/x86
}
mac {
    GSTREAMER_INCLUDE_PATH=/opt/local/include/gstreamer-1.0
    GSTREAMER_LIB_PATH=/opt/local/lib/gstreamer-1.0
}

INCLUDEPATH += \
    $${GSTREAMER_INCLUDE_PATH} \
    $${GSTREAMER_INCLUDE_PATH}/include \
    $${GSTREAMER_INCLUDE_PATH}/include/gstreamer-1.0 \
    $${GSTREAMER_INCLUDE_PATH}/lib/glib-2.0/include \
    $${GSTREAMER_INCLUDE_PATH}/include/glib-2.0 \
    $${GSTREAMER_INCLUDE_PATH}/include/libxml2 \
    $${GSTREAMER_INCLUDE_PATH}/lib/gstreamer-1.0/include

mac {
INCLUDEPATH += \
    /opt/local/include/glib-2.0 \
    /opt/local/lib/glib-2.0/include \
    /opt/local/lib/gstreamer-1.0/include

LIBS += \
    -L/opt/local/lib
    -L/opt/local/lib/gstreamer-1.0
}

LIBS += \
    -L$${GSTREAMER_LIB_PATH}/lib \
    -L$${GSTREAMER_LIB_PATH}/gst/rtsp-server

LIBS += \
    -lglib-2.0 \
    -lgstreamer-1.0 \
    -lgobject-2.0 \
#    -lgtk-x11-2.0 \
#    -lgstrtsp-1.0 \
#    -lgstapp-1.0 \
    -lstdc++
#    -lgstrtspserver-1.0

QT += core
QT -= gui
