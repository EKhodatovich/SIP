#include "mainwindow.h"
#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    // catch (std::invalid_argument) {
    //     return 1;
    // }
    return a.exec();
}
