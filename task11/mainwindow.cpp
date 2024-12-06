#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "opencv2/highgui.hpp"

using namespace cv;

MainWindow::MainWindow(std::string imageName, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    wts(new watershedSegmenter())
{
    ui->setupUi(this);
    wts->load(imageName);

    namedWindow("Shed Image", WINDOW_NORMAL);
    drawImage();
}

void MainWindow::drawImage()
{
    Mat image = wts->getPrimalImage();
    //Mat harrisImage = shp->getHarrisImage();
    Mat shedImage = wts->getWatershedImage();
    Mat result;

    // imshow("Transormed Image", image);
    // //imshow("Harris angles", harrisImage);
    // imshow("Good Features To Track", GFTTImage);

    hconcat(std::vector<Mat>{image, shedImage}, result);
    imshow("Shed Image", result);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete wts;
}

void MainWindow::on_shapeBox_currentIndexChanged(int index)
{
    wts->setDilateAttrs(static_cast<cv::MorphShapes>(index),
                        ui->sizeBox->value(),
                        ui->iterationsBox->value(),
                        static_cast<cv::BorderTypes>(ui->borderTypeBox->currentIndex()));
    drawImage();
}


void MainWindow::on_sizeBox_valueChanged(int arg1)
{
    wts->setDilateAttrs(static_cast<cv::MorphShapes>(ui->shapeBox->currentIndex()),
                        arg1,
                        ui->iterationsBox->value(),
                        static_cast<cv::BorderTypes>(ui->borderTypeBox->currentIndex()));
}


void MainWindow::on_iterationsBox_valueChanged(int arg1)
{
    wts->setDilateAttrs(static_cast<cv::MorphShapes>(ui->shapeBox->currentIndex()),
                        ui->sizeBox->value(),
                        arg1,
                        static_cast<cv::BorderTypes>(ui->borderTypeBox->currentIndex()));
    drawImage();
}


void MainWindow::on_borderTypeBox_currentIndexChanged(int index)
{
    wts->setDilateAttrs(static_cast<cv::MorphShapes>(ui->shapeBox->currentIndex()),
                        ui->sizeBox->value(),
                        ui->iterationsBox->value(),
                        static_cast<cv::BorderTypes>(index));
    drawImage();
}


void MainWindow::on_distTypeBox_currentIndexChanged(int index)
{
    std::unordered_map <int, DistanceTransformMasks> map = {{0, cv::DIST_MASK_3},
                                                           {1, cv::DIST_MASK_5},
                                                           {2, cv::DIST_MASK_PRECISE}};

    wts->setDistTransAttrs(static_cast<cv::DistanceTypes>(index + 1),
                           map.find(ui->borderMaskBox->currentIndex())->second,
                           ui->FGThreshBox->value());
    drawImage();
}


void MainWindow::on_borderMaskBox_currentIndexChanged(int index)
{
    std::unordered_map <int, DistanceTransformMasks> map = {{0, cv::DIST_MASK_3},
                                                           {1, cv::DIST_MASK_5},
                                                           {2, cv::DIST_MASK_PRECISE}};

    wts->setDistTransAttrs(static_cast<cv::DistanceTypes>(ui->distTypeBox->currentIndex() + 1),
                           map.find(index)->second,
                           ui->FGThreshBox->value());
    drawImage();
}

void MainWindow::on_FGThreshBox_valueChanged(int arg1)
{
    std::unordered_map <int, DistanceTransformMasks> map = {{0, cv::DIST_MASK_3},
                                                           {1, cv::DIST_MASK_5},
                                                           {2, cv::DIST_MASK_PRECISE}};

    wts->setDistTransAttrs(static_cast<cv::DistanceTypes>(ui->distTypeBox->currentIndex() + 1),
                           map.find(ui->borderMaskBox->currentIndex())->second,
                           arg1);
    drawImage();
}


void MainWindow::on_connBox_valueChanged(int arg1)
{
    wts->setConnCompAttrs(arg1);
    drawImage();
}



