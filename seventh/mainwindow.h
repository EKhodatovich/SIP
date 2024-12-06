#pragma once
#include "imageshaper.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(std::string imageName, QWidget *parent = nullptr);
    ~MainWindow();

    void DrawImage();
private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_3_currentIndexChanged(int index);

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;

    imageShaper* shp;

    double thresh1_ = 100;
    double thresh2_ = 200;
    int apertureSize_ = 3;
    bool L2Gradient_ = false;
    int mode_ = cv::RETR_EXTERNAL;
    int method_ = cv::CHAIN_APPROX_SIMPLE;
};
