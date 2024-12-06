#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    std::string filename = argc >= 2 ? argv[1] : "coins.png";
    QApplication app(argc, argv);
    MainWindow window{filename};
    window.show();
    return app.exec();
}
