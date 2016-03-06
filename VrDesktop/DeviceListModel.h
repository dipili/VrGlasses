#pragma once

#include <QAbstractListModel>

#include "Device.h"
#include "DeviceConnectionListener.h"

class DeviceListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    DeviceListModel(QObject* parent = NULL);
    int rowCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

public slots:
    void onPendingData(Device device);

private:
    void signalDataChanged(int row);
    void addData(const Device& device);

private:
    QList<Device> _deviceList;
};
