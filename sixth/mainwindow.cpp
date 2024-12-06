#include "mainwindow.h"
#include "opencv2/highgui.hpp"
#include "ui_mainwindow.h"

using namespace cv;

MainWindow::MainWindow(const std::string& imageName , QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    shp_(new grayImageShaper(imageName))
{
    ui->setupUi(this);
    namedWindow("Different shapes", cv::WINDOW_NORMAL);
    imshow("Different shapes", shp_->shapedImages(ksize_, scale_, delta_));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete shp_;
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    ksize_ = arg1.toInt();
    imshow("Different shapes", shp_->shapedImages(ksize_, scale_, delta_));
}

void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    scale_ = arg1;
    imshow("Different shapes", shp_->shapedImages(ksize_, scale_, delta_));
}

void MainWindow::on_doubleSpinBox_2_valueChanged(double arg1)
{
    delta_ = arg1;
    imshow("Different shapes", shp_->shapedImages(ksize_, scale_, delta_));
}

