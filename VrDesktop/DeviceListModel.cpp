#include "DeviceListModel.h"

#include <QModelIndex>

DeviceListModel::DeviceListModel(QObject* parent) : QAbstractListModel(parent)
{
}

int DeviceListModel::rowCount(const QModelIndex&) const
{
    return _deviceList.size();
}

QVariant DeviceListModel::data(const QModelIndex& index, int) const
{
    return QVariant::fromValue(_deviceList.at(index.row()));
}

void DeviceListModel::signalDataChanged(int row)
{
    QModelIndex index = createIndex(row, 0);
    emit QAbstractItemModel::dataChanged(index, index);
}

void DeviceListModel::addData(const Device& device)
{
    int index = _deviceList.size();
    beginInsertRows(QModelIndex(), index, index);
    _deviceList.append(device);
    endInsertRows();
}

void DeviceListModel::onPendingData(Device device)
{
    qDebug() << "pendingData";
    bool found = false;
    for (int i = 0; i < _deviceList.size(); ++i)
    {
        if (_deviceList.at(i).getId() == device.getId())
        {
            found = true;
            if (device != _deviceList.at(i))
            {
                _deviceList.removeAt(i);
                _deviceList.insert(i, device);
                signalDataChanged(i);
                return;
            }
        }
    }

    if (!found)
        addData(device);
}
