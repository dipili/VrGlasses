#pragma once

#include <QObject>

class MainWindow;

class Core : public QObject
{
    Q_OBJECT

  public:
    explicit Core(QObject* parent = 0);
    virtual ~Core();

    void start();

  private:
    MainWindow* _mainWindow;
};
