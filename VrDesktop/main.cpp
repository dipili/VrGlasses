#include <QApplication>

#include "Core.h"

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);

    Core core;
    core.start();

    return application.exec();
}
