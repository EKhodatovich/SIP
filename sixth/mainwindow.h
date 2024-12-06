#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "grayimageshaper.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const std::string &imageName, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;

    grayImageShaper* shp_;
    int ksize_ = 1;
    double scale_ = 1, delta_ = 0;
};

#endif // MAINWINDOW_H
