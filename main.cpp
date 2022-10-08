#include "mainwindow.h"
#include "logHandler.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(Utility::logMessageHandler);
    MainWindow w;
    w.show();
    return a.exec();
}
