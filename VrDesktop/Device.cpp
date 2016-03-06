#include "Device.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

#define KEY_MODEL "model"
#define KEY_ID "id"
#define KEY_PORT "port"

void Device::initalize(const QByteArray& json)
{
    QJsonObject object = QJsonDocument::fromJson(json).object();
    model = object.take(KEY_MODEL).toString();
    id = object.take(KEY_ID).toString();
    port = object.take(KEY_PORT).toInt();
}

QString Device::getModel() const
{
    return model;
}

void Device::setModel(const QString& value)
{
    model = value;
}

QString Device::getId() const
{
    return id;
}

void Device::setId(const QString& value)
{
    id = value;
}

int Device::getPort() const
{
    return port;
}

void Device::setPort(int value)
{
    port = value;
}

QHostAddress Device::getHost() const
{
    return host;
}

void Device::setHost(const QHostAddress& value)
{
    host = value;
}
