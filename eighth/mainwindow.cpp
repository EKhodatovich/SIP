#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "opencv2/highgui.hpp"

using namespace cv;

MainWindow::MainWindow(std::string imageName, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    shp(new imageShaper(imageName))
{
    ui->setupUi(this);

    thresh1_ = ui->spinBox->value();
    thresh2_ = ui->spinBox_2->value();
    apertureSize_ = ui->comboBox->currentText().toInt();
    L2Gradient_ = ui->checkBox->isChecked();

    rho_ = ui->doubleSpinBox->value();
    theta_ = ui->doubleSpinBox_2->value();
    threshold_ = ui->spinBox_3->value();

    namedWindow("Images", cv::WINDOW_NORMAL);
    DrawImage();
}

void MainWindow::DrawImage()
{
    Mat primal = shp->getImage();
    Mat canny = shp->cannyImage(thresh1_,
                                thresh2_,
                                apertureSize_,
                                L2Gradient_);

    auto shaped = shp->shapedImage(thresh1_,
                                  thresh2_,
                                  apertureSize_,
                                  L2Gradient_,
                                  rho_,
                                  theta_,
                                  threshold_);
    Mat result1, result2, result;

    vconcat(std::vector<Mat>{primal, canny}, result1);
    vconcat(shaped, result2);
    hconcat(std::vector<Mat>{result1, result2}, result);

    imshow("Images", result);
}

MainWindow::~MainWindow()
{
    delete shp;
    delete ui;
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    thresh1_ = arg1;
    DrawImage();
}


void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    thresh2_ = arg1;
    DrawImage();
}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    apertureSize_ = arg1.toInt();
    DrawImage();
}




void MainWindow::on_checkBox_stateChanged(int arg1)
{
    L2Gradient_ = arg1;
    DrawImage();
}


void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    rho_ = arg1;
    DrawImage();
}


void MainWindow::on_doubleSpinBox_2_valueChanged(double arg1)
{
    theta_ = arg1;
    DrawImage();
}


void MainWindow::on_spinBox_3_valueChanged(int arg1)
{
    threshold_ = arg1;
    DrawImage();
}

