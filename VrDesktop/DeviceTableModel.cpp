#include "DeviceTableModel.h"

#define COLUMN_COUNT 4

#define NAME_COLUMN 0
#define MODEL_COLUMN 1
#define PORT_COLUMN 2
#define HOST_COLUMN 3

DeviceTableModel::DeviceTableModel(QObject* parent) : QAbstractTableModel(parent), _listModel(NULL)
{
}

void DeviceTableModel::setListModel(DeviceListModel* deviceListModel)
{
    _listModel = deviceListModel;
    connect(_listModel, SIGNAL(dataChanged(QModelIndex, QModelIndex, QVector<int>)),
            SLOT(onListModelChanged(QModelIndex, QModelIndex, QVector<int>)));

    connect(_listModel, SIGNAL(rowsInserted(QModelIndex, int, int)),
            SLOT(onListModelRowInserted(QModelIndex, int, int)));
}

int DeviceTableModel::rowCount(const QModelIndex& parent) const
{
    return _listModel->rowCount(parent);
}

int DeviceTableModel::columnCount(const QModelIndex&) const
{
    return COLUMN_COUNT;
}

QVariant DeviceTableModel::data(const QModelIndex& index, int role) const
{
    if (role != Qt::DisplayRole)
           return QVariant();

    Device device = qvariant_cast<Device>(_listModel->data(index, role));

    switch (index.column())
    {
    case NAME_COLUMN:
        return device.getId();
    case MODEL_COLUMN:
        return device.getModel();
    case PORT_COLUMN:
        return QString::number(device.getPort());
    case HOST_COLUMN:
        return device.getHost().toString();
    default:
        return QVariant();
    }
}

void DeviceTableModel::onListModelChanged(QModelIndex from, QModelIndex to, QVector<int>)
{
    qDebug() << "penis";
    emit dataChanged(from, to);
}

void DeviceTableModel::onListModelRowInserted(QModelIndex index, int from, int to)
{
    beginInsertRows(index, from, to);
    endInsertRows();
}
