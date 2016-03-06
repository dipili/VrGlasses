#pragma once

#include <QObject>
#include <QUdpSocket>

#include "Device.h"

class DeviceConnectionListener : public QObject
{
    Q_OBJECT

  public:
    explicit DeviceConnectionListener(QObject* parent = 0);

public slots:
    void start();
    void stop();

  signals:
    void deviceReceived(Device device);

  private slots:
    void readSocketData();

  private:
    QUdpSocket* udpSocket;
};
