
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("Flight Delay Finder");
    w.setFixedSize(830, 740);
    w.show();
    return a.exec();
}
