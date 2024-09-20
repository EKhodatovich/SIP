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


    cv::Mat image_;
    cv::Mat new_image_;
    int threshold_ = 128;
    int mode_ = 0;
private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    void show_images() const;
};
#endif // MAINWINDOW_H
