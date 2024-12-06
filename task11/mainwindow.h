#pragma once
#include <QMainWindow>
#include "watershedsegmenter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow final: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(std::string imageName, QWidget *parent = nullptr);
    ~MainWindow() final;

    void drawImage();
private slots:
    void on_shapeBox_currentIndexChanged(int index);

    void on_sizeBox_valueChanged(int arg1);

    void on_iterationsBox_valueChanged(int arg1);

    void on_borderTypeBox_currentIndexChanged(int index);

    void on_distTypeBox_currentIndexChanged(int index);

    void on_borderMaskBox_currentIndexChanged(int index);

    void on_connBox_valueChanged(int arg1);

    void on_FGThreshBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    watershedSegmenter* wts;
};

