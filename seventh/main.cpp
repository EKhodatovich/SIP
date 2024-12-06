#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    std::string filename = argc >= 2 ? argv[1] : "cards.jpg";

    QApplication app(argc, argv);
    MainWindow window{"cards.jpg"};
    window.show();
    return app.exec();
}
