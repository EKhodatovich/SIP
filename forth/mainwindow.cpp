#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
    // image_(new (Mat)),
    // new_image_(new (Mat))
{
    ui->setupUi(this);
    Mat image = imread("c:\\image.jpeg");
    if (image.empty()) {
        std::cout << "Could not open or find the image";
        throw std::invalid_argument("Bad iamge");
    }
    // *image_ = image;
    // *new_image_ = image;

    image_ = image;
    image_.copyTo(new_image_);

    show_image();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    alpha_ = value / 100.0;
    ui->alpha_label->setText(QString::number(alpha_));
    show_image();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    beta_ = value;
    ui->beta_label->setText(QString::number(beta_));
    show_image();
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    gamma_ = value;
    ui->gamma_label->setText(QString::number(gamma_));
    show_image();
}


void MainWindow::show_image()
{
    Mat inter_image;
    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.ptr();
    for( int i = 0; i < 256; ++i) {
        p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma_/100.0) * 255.0);
    }

    LUT(image_, lookUpTable, inter_image);

    for( int y = 0; y < inter_image.rows; y++ ) {
        for( int x = 0; x < inter_image.cols; x++ ) {
            for( int c = 0; c < inter_image.channels(); c++ ) {
                new_image_.at<Vec3b>(y,x)[c] =
                    saturate_cast<uchar>( alpha_*inter_image.at<Vec3b>(y,x)[c] + beta_ );
            }
        }
    }
    Mat show_colored;
    std::vector<Mat> colored = {image_, new_image_};
    cv::vconcat(colored, show_colored);
    imshow("colored", show_colored);

    show_eq_image();
    show_histograms();
}

void MainWindow::show_eq_image()
{
    Mat gray_image;
    cvtColor(new_image_, gray_image, COLOR_RGB2GRAY);
        // Check if the image is grayscale

    Mat eq_gray_image;
    equalizeHist(gray_image, eq_gray_image);

    Mat show_gray;
    std::vector<Mat> colored = {image_, new_image_};
    std::vector<Mat> gray = {gray_image, eq_gray_image};

    cv::vconcat(gray, show_gray);
    imshow("gray", show_gray);

    // std::vector<Mat> all = {show_colored, show_gray};
    // cv::hconcat(all, show);
    // imshow("Images", show);
}

Mat histogram(const Mat& image)
{
    if (image.channels() != 1) {
        std::cerr << "Error: The image is not grayscale!" << std::endl;
        throw std::invalid_argument("bad image");
    }

    int histSize = 256; // number of bins
    float range[] = {0, 256}; // range of values
    const float* histRange = {range};
    cv::Mat histogram;

    cv::calcHist(&image, 1, 0, cv::Mat(), histogram, 1, &histSize, &histRange);

    // Normalize the histogram
    cv::normalize(histogram, histogram, 0, 255, cv::NORM_MINMAX);

    // Create an image to display the histogram
    int histWidth = 512;
    int histHeight = 300;
    cv::Mat histImage(histHeight, histWidth, CV_8UC1, cv::Scalar(255));

    // Draw the histogram
    for (int i = 1; i < histSize; i++) {
        cv::line(histImage,
                 cv::Point((i - 1) * histWidth / histSize, histHeight - cvRound(histogram.at<float>(i - 1))),
                 cv::Point(i * histWidth / histSize, histHeight - cvRound(histogram.at<float>(i))),
                 cv::Scalar(0), 2, 8, 0);
    }

    // Show the histogram
    return histImage;
}

void MainWindow::show_histograms() const
{
    Mat gray_image;
    cvtColor(new_image_, gray_image, COLOR_RGB2GRAY);
    auto hist = histogram(gray_image);

    Mat eq_gray_image;
    equalizeHist(gray_image, eq_gray_image);
    auto eq_hist = histogram(eq_gray_image);

    Mat show;
    Mat _[2] = {hist, eq_hist};
    cv::vconcat(_, 2, show);
    imshow("Histograms", show);
}
