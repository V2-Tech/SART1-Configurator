#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowState(Qt::WindowMaximized);
    w.setWindowTitle("OMD SART1 Configurator");
    w.show();

    return a.exec();
}
