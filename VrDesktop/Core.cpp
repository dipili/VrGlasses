#include "Core.h"

#include <QDebug>
#include <vlc/vlc.h>

#include "ScreenStreamer.h"
#include "MainWindow.h"
#include "DeviceConnectionListener.h"
#include "DeviceListModel.h"

Core::Core(QObject* parent) : QObject(parent)
{
}

Core::~Core()
{
    delete _mainWindow;
}

void Core::start()
{
    _mainWindow = new MainWindow();
    _mainWindow->show();
    vrserver::ScreenStreamer screenStreamer;
    screenStreamer.setOptions(
        "#transcode{vcodec=h264,vb=2000,venc=x264{profile=baseline},width=1280,height=720,acodec=none,ab=192,"
        "channels=2,samplerate=44100}:rtp{sdp=rtsp://:8554/test}");

    connect(_mainWindow, SIGNAL(start(QString)), &screenStreamer, SLOT(startStreaming(QString)));

    DeviceConnectionListener* connectionListener = new DeviceConnectionListener(this);

    DeviceListModel* deviceModel = new DeviceListModel(this);
    connect(connectionListener, SIGNAL(deviceReceived(Device)), deviceModel, SLOT(onPendingData(Device)));

    _mainWindow->setDeviceListModel(deviceModel);

    connectionListener->start();
}
