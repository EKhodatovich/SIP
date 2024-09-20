#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "opencv2/core/mat.hpp"
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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

private:
    int currBright_;
    Ui::MainWindow *ui;
    cv::Mat* image_;
    cv::Mat* gray_;
    cv::Mat* currImage_;

};
#endif // MAINWINDOW_H
