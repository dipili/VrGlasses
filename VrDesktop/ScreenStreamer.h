#pragma once

#include <QObject>
#include <QDebug>
#include <vlc/vlc.h>

namespace vrserver
{
// Класс предоставляет возможность передачи по RTP протоколу изображения экрана компьютера
class ScreenStreamer : public QObject
{
    Q_OBJECT

  public:
    explicit ScreenStreamer(QObject *parent = 0);

    QString options() const;
    void setOptions(const QString &options);

    QString mediaName() const;
    void setMediaName(const QString &mediaName);

    bool isInitialized() const;

  public slots:
    bool startStreaming(QString mrl);

  private:
    bool initialize();

  private:
    bool _isInitialized;

    libvlc_instance_t *_vlcInstance;
    QString _options;
    QString _mediaName;
};
}
