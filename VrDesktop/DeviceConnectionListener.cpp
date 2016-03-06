#include "DeviceConnectionListener.h"

#include <QDebug>

#define WAITER_PORT 12345

DeviceConnectionListener::DeviceConnectionListener(QObject* parent) : QObject(parent)
{
}

void DeviceConnectionListener::start()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(WAITER_PORT, QUdpSocket::ShareAddress);
    connect(udpSocket, SIGNAL(readyRead()), SLOT(readSocketData()));
}

void DeviceConnectionListener::stop()
{
    delete udpSocket;
}

void DeviceConnectionListener::readSocketData()
{
    while (udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());

        QHostAddress host;
        udpSocket->readDatagram(datagram.data(), datagram.size(), &host);

        Device device;
        device.initalize(datagram);
        device.setHost(host);

        emit deviceReceived(device);
    }
}
