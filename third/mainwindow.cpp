#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

static const std::unordered_map<int, cv::ThresholdTypes> types = {{0, cv::ThresholdTypes::THRESH_BINARY},
                                                     {1, cv::ThresholdTypes::THRESH_BINARY_INV},
                                                     {2, cv::ThresholdTypes::THRESH_TRUNC},
                                                     {3, cv::ThresholdTypes::THRESH_TOZERO},
                                                     {4, cv::ThresholdTypes::THRESH_TOZERO_INV}};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cv::Mat image = cv::imread("c:\\image.jpg");
    if (image.empty()) {
        std::cout << "Could not open or find the image";
        throw std::invalid_argument("Bad iamge");
    }
    image_ = image;

    cv::ThresholdTypes type = cv::ThresholdTypes::THRESH_BINARY;
    cv::threshold(image_, new_image_, 128, 256, type);

    show_images();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    cv::ThresholdTypes type = types.find(index)->second;
    if (mode_ == 0) {
        cv::threshold(image_, new_image_, threshold_, 254, type);
    } else {
        cv::Mat gray_image;
        cv::cvtColor(image_, gray_image, cv::COLOR_BGR2GRAY);
        cv::adaptiveThreshold(gray_image, new_image_, 255, cv::AdaptiveThresholdTypes::ADAPTIVE_THRESH_GAUSSIAN_C, type, 11, 2);
    }
    show_images();
}

void MainWindow::show_images() const
{
    cv::namedWindow("old image", cv::WINDOW_NORMAL);
    imshow("old image", image_);
    cv::namedWindow("new image", cv::WINDOW_NORMAL);
    imshow("new image", new_image_);
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    mode_ = arg1;
    if (mode_ == Qt::Checked) {
        for (int i = 4; i>1; i--) {
            ui->comboBox->removeItem(i);
        }
    }
    else {
        ui->comboBox->addItem("TRUNC");
        ui->comboBox->addItem("TO_ZERO");
        ui->comboBox->addItem("TO_ZERO_INV");
    }
    emit on_comboBox_currentIndexChanged(ui->comboBox->currentIndex());
}

