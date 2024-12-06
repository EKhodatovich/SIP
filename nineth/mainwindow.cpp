#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "opencv2/highgui.hpp"

using namespace cv;

MainWindow::MainWindow(std::string imageName, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    shp(new imageShaper())
{
    ui->setupUi(this);
    shp->load(imageName);

    ui->XBox->setMaximum(shp->getPrimalImage().cols - 1);
    ui->XBox->setMinimum(-shp->getPrimalImage().cols + 1);

    ui->YBox->setMaximum(shp->getPrimalImage().rows - 1);
    ui->YBox->setMinimum(-shp->getPrimalImage().rows + 1);

    shp->setBrightCont(ui->alphaBox->value(), ui->betaBox->value());
    //imshow("Transormed Image 1", shp->getImage());
    shp->setAngle(ui->angleBox->value());
    //imshow("Transormed Image 2", shp->getImage());
    shp->setScaling(ui->scaleBox->value());
    //imshow("Transormed Image 3", shp->getImage());
    shp->setTranslation(ui->XBox->value(), ui->YBox->value());
    //imshow("Transormed Image 4", shp->getImage());

    shp->setHarrisAttrs(ui->blockSizeBox->currentText().toInt(), ui->KSizeBox->currentText().toInt(), ui->KBox->value());
    shp->setGFTTAttrs(ui->maxCornersBox->value(), ui->qualityBox->value(), ui->minDistBox->value());

    //imshow ("Primal image",  shp->getPrimalImage());
    drawImage();
}

void MainWindow::drawImage()
{
    Mat image = shp->getImage();
    //Mat harrisImage = shp->getHarrisImage();
    Mat GFTTImage = shp->getGFTTImage();
    Mat result;

    // imshow("Transormed Image", image);
    // //imshow("Harris angles", harrisImage);
    // imshow("Good Features To Track", GFTTImage);

    hconcat(std::vector<Mat>{image, GFTTImage}, result);
    imshow("Good Features To Track", result);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete shp;
}


void MainWindow::on_alphaBox_valueChanged(double arg1)
{
    shp->setBrightCont(ui->alphaBox->value(), ui->betaBox->value());
    drawImage();
}

void MainWindow::on_betaBox_valueChanged(double arg1)
{
    shp->setBrightCont(ui->alphaBox->value(), ui->betaBox->value());
    drawImage();
}



void MainWindow::on_XBox_valueChanged(int arg1)
{
    shp->setTranslation(ui->XBox->value(), ui->YBox->value());
    drawImage();
}


void MainWindow::on_YBox_valueChanged(int arg1)
{
    shp->setTranslation(ui->XBox->value(), ui->YBox->value());
    drawImage();
}



void MainWindow::on_angleBox_valueChanged(double arg1)
{
    shp->setAngle(ui->angleBox->value());
    drawImage();
}


void MainWindow::on_scaleBox_valueChanged(double arg1)
{
    shp->setScaling(ui->scaleBox->value());
    drawImage();
}




void MainWindow::on_blockSizeBox_currentTextChanged(const QString &arg1)
{
    shp->setHarrisAttrs(ui->blockSizeBox->currentText().toInt(), ui->KSizeBox->currentText().toInt(), ui->KBox->value());
    drawImage();
}

void MainWindow::on_KSizeBox_currentTextChanged(const QString &arg1)
{
    shp->setHarrisAttrs(ui->blockSizeBox->currentText().toInt(), ui->KSizeBox->currentText().toInt(), ui->KBox->value());
    drawImage();
}

void MainWindow::on_KBox_valueChanged(double arg1)
{
    shp->setHarrisAttrs(ui->blockSizeBox->currentText().toInt(), ui->KSizeBox->currentText().toInt(), ui->KBox->value());
    drawImage();
}


void MainWindow::on_maxCornersBox_valueChanged(int arg1)
{
    shp->setGFTTAttrs(ui->maxCornersBox->value(), ui->qualityBox->value(), ui->minDistBox->value());
    drawImage();
}


void MainWindow::on_qualityBox_valueChanged(double arg1)
{
    shp->setGFTTAttrs(ui->maxCornersBox->value(), ui->qualityBox->value(), ui->minDistBox->value());
    drawImage();
}


void MainWindow::on_minDistBox_valueChanged(double arg1)
{
    shp->setGFTTAttrs(ui->maxCornersBox->value(), ui->qualityBox->value(), ui->minDistBox->value());
    drawImage();
}

void MainWindow::on_XPerspBox_valueChanged(double arg1)
{
    shp->setPerspective(ui->XPerspBox->value(), ui->YPerspBox->value());
    drawImage();
}

void MainWindow::on_YPerspBox_valueChanged(double arg1)
{
    shp->setPerspective(ui->XPerspBox->value(), ui->YPerspBox->value());
    drawImage();
}

