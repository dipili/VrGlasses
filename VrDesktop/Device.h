#pragma once

#include <QObject>
#include <QHostAddress>

class Device
{
public:
    void initalize(const QByteArray& json);

    inline bool operator==(Device other) const
    {
        return model == other.getModel() && id == other.getId() && port == other.getPort();
    }

    inline bool operator!=(Device other) const
    {
        return !operator==(other);
    }

    QString getModel() const;
    void setModel(const QString& value);

    QString getId() const;
    void setId(const QString& value);

    int getPort() const;
    void setPort(int value);

    QHostAddress getHost() const;
    void setHost(const QHostAddress& value);

private:
    QString model;
    QString id;
    QHostAddress host;
    int port;
};

Q_DECLARE_METATYPE(Device)
