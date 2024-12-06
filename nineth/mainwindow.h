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

    void drawImage();

private slots:

    void on_blockSizeBox_currentTextChanged(const QString &arg1);

    void on_KSizeBox_currentTextChanged(const QString &arg1);

    void on_alphaBox_valueChanged(double arg1);

    void on_betaBox_valueChanged(double arg1);

    void on_XBox_valueChanged(int arg1);

    void on_YBox_valueChanged(int arg1);

    void on_maxCornersBox_valueChanged(int arg1);

    void on_angleBox_valueChanged(double arg1);

    void on_scaleBox_valueChanged(double arg1);

    void on_KBox_valueChanged(double arg1);

    void on_qualityBox_valueChanged(double arg1);

    void on_minDistBox_valueChanged(double arg1);

    void on_XPerspBox_valueChanged(double arg1);

    void on_YPerspBox_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;

    imageShaper* shp;
};
