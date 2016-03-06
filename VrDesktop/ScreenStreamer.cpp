#include "ScreenStreamer.h"

//#include "LogSystem.h"

#define LOG_ERROR(str) qDebug() << str;
#define LOG_INFO(str) qDebug() << str;

namespace vrserver
{
ScreenStreamer::ScreenStreamer(QObject *parent) : QObject(parent),
                                                  _mediaName("rtsp://:8554/test")
{
    _isInitialized = false;
}

bool ScreenStreamer::startStreaming(QString mrl)
{
    LOG_INFO(tr("Starting the steram..."));
    if (!_isInitialized)
    {
        if (!initialize())
            return false;
    }

    int res = libvlc_vlm_add_broadcast(_vlcInstance,
                                       _mediaName.toLatin1().data(),
                                       mrl.toLatin1().data(),
                                       _options.toLatin1().data(),
                                       0, NULL, 1, 0);

    if (res == -1)
    {
        LOG_ERROR(trUtf8("Error with starting the stream. %1").arg(QString::number(res)));
        return false;
    }

    libvlc_vlm_play_media(_vlcInstance, _mediaName.toLatin1());

    LOG_INFO(trUtf8("Stream was successfully started."));
    return true;
}

bool ScreenStreamer::initialize()
{
    LOG_INFO(tr("Vlc initialization..."));
    _vlcInstance = libvlc_new(0, NULL);

    if (!_vlcInstance)
    {
        LOG_ERROR(tr("Initialization error. Failed creating vlc instance."));
        return false;
    }

    _isInitialized = true;
    return true;
}

bool ScreenStreamer::isInitialized() const
{
    return _isInitialized;
}

QString ScreenStreamer::mediaName() const
{
    return _mediaName;
}

void ScreenStreamer::setMediaName(const QString &mediaName)
{
    _mediaName = mediaName;
}

QString ScreenStreamer::options() const
{
    return _options;
}

void ScreenStreamer::setOptions(const QString &options)
{
    _options = options;
}
}
