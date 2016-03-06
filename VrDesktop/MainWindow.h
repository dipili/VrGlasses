#pragma once

#include "ui_MainWindow.h"
#include "DeviceListModel.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setDeviceListModel(DeviceListModel* listModel);

signals:
    void start(QString mrl);
    void stop();

private slots:
    void on_startButton_clicked();
    void on_mrlBrowseButton_clicked();
    void on_stopButton_clicked();

private:
    DeviceListModel* _deviceListModel;
};

