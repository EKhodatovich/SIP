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
    mode_ = ui->comboBox_2->currentIndex();
    method_ = ui->comboBox_3->currentIndex()+1;

    namedWindow("Images", cv::WINDOW_NORMAL);
    DrawImage();
}

void MainWindow::DrawImage()
{
    Mat primal = shp->getImage();
    Mat shaped = shp->shapedImage(thresh1_,
                                  thresh2_,
                                  apertureSize_,
                                  L2Gradient_,
                                  mode_,
                                  method_);
    Mat result;

    hconcat(std::vector<Mat>{primal, shaped}, result);
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


void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    mode_ = index;
    DrawImage();
}


void MainWindow::on_comboBox_3_currentIndexChanged(int index)
{
    method_ = index+1;
    DrawImage();
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    L2Gradient_ = arg1;
    DrawImage();
}

