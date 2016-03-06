#pragma once

#include <QAbstractTableModel>

#include "DeviceListModel.h"

class DeviceTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    DeviceTableModel(QObject* parent = NULL);

    void setListModel(DeviceListModel* deviceListModel);

    // Overrided methods
    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;

private slots:
    void onListModelChanged(QModelIndex from, QModelIndex to, QVector<int>);
    void onListModelRowInserted(QModelIndex, int row, int);

private:
    DeviceListModel* _listModel;
};
