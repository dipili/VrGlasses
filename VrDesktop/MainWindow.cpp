#include "MainWindow.h"

#include <QFileDialog>

#include "DeviceTableModel.h"

#define FILE_PREFIX "file:///"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setupUi(this);
    tableView->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::setDeviceListModel(DeviceListModel* listModel)
{
    _deviceListModel = listModel;
    DeviceTableModel* tableModel = new DeviceTableModel(this);
    tableModel->setListModel(listModel);
    tableView->setModel(tableModel);
}

void MainWindow::on_startButton_clicked()
{
    QModelIndex index = tableView->selectionModel()->selectedRows().at(0);
    Device selectedDevice = qvariant_cast<Device>(_deviceListModel->data(index));
    qDebug() << selectedDevice.getId();
//    emit start(mrlLineEdit->text(), selectedDevice.getHost());

    QUdpSocket* outSocket = new QUdpSocket();
    outSocket->connectToHost(selectedDevice.getHost(), selectedDevice.getPort());
    outSocket->waitForConnected();
    qDebug() << outSocket->write("1233");
    qDebug() << outSocket->flush();
}

void MainWindow::on_mrlBrowseButton_clicked()
{
    mrlLineEdit->setText(QString("%1%2").arg(FILE_PREFIX, QFileDialog::getOpenFileName()));
}

void MainWindow::on_stopButton_clicked()
{
    emit stop();
}
