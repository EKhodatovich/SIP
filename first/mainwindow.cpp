#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    image_(new (cv::Mat)),
    gray_(new (cv::Mat))
{
    ui->setupUi(this);

    // read an image
    cv::Mat image = cv::imread("c:\\151089.jpg");
    if (image.empty())
    {
        std::cout << "Could not open or find the image";
    }
    else
    {
        *image_ = image;
        currImage_ = image_;
    }
    // create image window named "My Image"
    cv::namedWindow("My Image", cv::WINDOW_NORMAL);
    // show the image on window
    cv::imshow("My Image", *image_);
    cv::cvtColor(*image_, *gray_, cv::COLOR_BGR2GRAY);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    int brightness = 0;
    int bright_image_size = 0;
    int image_size = 0;
    for (int x=0; x < currImage_->rows; x++) {

        for (int y=0; y < currImage_->cols; y++) {

            for (int c=0; c < currImage_->channels(); c++) {
                brightness += static_cast<int>(currImage_->at<cv::Vec3b>(y,x)[c]);
            }
            if (static_cast<float>(brightness)/currImage_->channels() > arg1) {
                bright_image_size +=1;
            }
            image_size += 1;
            brightness = 0;
        }
    }
    ui->label_3->setText(QString::number(static_cast<float>(bright_image_size) / image_size));
    currBright_ = arg1;
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (arg1 == Qt::CheckState::Checked) {
        cv::destroyWindow("My Image");
        cv::namedWindow("My Image", cv::WINDOW_NORMAL);
        cv::imshow("My Image", *gray_);
        currImage_ = gray_;
    } else {
        cv::destroyWindow("My Image");
        cv::namedWindow("My Image", cv::WINDOW_NORMAL);
        cv::imshow("My Image", *image_);
        currImage_ = image_;
    }
    std::cout << currImage_->cols << ' ' <<  currImage_->rows << ' ' << currImage_->channels() << ' ' << currImage_->type() << ' ' << currImage_->size << std::endl;
    emit (on_spinBox_valueChanged(currBright_));
}

