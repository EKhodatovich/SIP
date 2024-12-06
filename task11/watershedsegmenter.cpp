#include "watershedsegmenter.h"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>

using namespace cv;

watershedSegmenter::watershedSegmenter() {}



void watershedSegmenter::load(const std::string& filename)
{
    Mat image = imread(filename);
    if (image.empty()) {
        throw std::invalid_argument("Bad image name");
    }
    image.copyTo(primalImage_);
}


cv::Mat watershedSegmenter::getWatershedImage()
{
    // Преобразование в оттенки серого
    Mat gray;
    cvtColor(primalImage_, gray, COLOR_BGR2GRAY);
    //imshow("gray", gray);

        // // Применение гауссового размытия для снижения шума
        // GaussianBlur(gray, gray, Size(5, 5), 0);
        // imshow("blurred", gray);

    // Применение бинаризации с помощью порогового преобразования
    Mat binary;
    threshold(gray, binary, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);
    imshow("binary", binary);

    // Поиск фона с помощью морфологических операций
    Mat kernel = Mat::ones(3, 3, CV_8U);//Mat kernel = getStructuringElement(shape_, {size_, size_});
    Mat background;

    // Избавляемся от шума
    morphologyEx(binary, binary, MORPH_OPEN, kernel, Point(-1, -1), iterations_);

    // Область фона
    dilate(binary, background, kernel, Point(-1, -1), iterations_, borderType_);
    imshow("background", background);

    // Поиск областей переднего плана
    Mat distTransform;
    distanceTransform(binary, distTransform, distanceType_, maskSize_);
    normalize(distTransform, distTransform, 0, 1.0, NORM_MINMAX);

    Mat foreground;
    threshold(distTransform, foreground, FGThreshold_, 255, THRESH_BINARY);
    foreground.convertTo(foreground, CV_8U);
    imshow("foreground", foreground);

    Mat unknown;
    subtract(background, foreground, unknown);

    // Определение маркеров
    Mat markers;
    connectedComponents(foreground, markers, connectivity_);
    markers = markers + 1;


    // Обработка фона
    for (int i = 0; i < binary.rows; i++) {
        for (int j = 0; j < binary.cols; j++) {
            if (unknown.at<uchar>(i, j) == 255) {
                markers.at<int>(i, j) = 0;
            }
        }
    }

    // Применение алгоритма Watershed
    watershed(primalImage_, markers);

    // Отображение результатов
    Mat result = primalImage_.clone();
    for (int i = 0; i < markers.rows; i++) {
        for (int j = 0; j < markers.cols; j++) {
            if (markers.at<int>(i, j) == -1) {
                result.at<Vec3b>(i, j) = Vec3b(0, 0, 255); // Граница сегмента
            }
        }
    }

    return result;
}

// For Dilatation
void watershedSegmenter::setDilateAttrs(cv::MorphShapes shape, int size, int iterations, cv::BorderTypes borderType) {
    if (size < 2) {
        std::cerr << "Wrong /'size/' value for dilation: must be >= 2" << std::endl;
        size_ = 3;
    } else {
        size_ = size;
    }

    if (iterations < 1) {
        std::cerr << "Wrong /'iterations/' value for dilation: must be > 0" << std::endl;
        iterations_ = 1;
    } else {
        iterations_ = iterations;
    }
    shape_ = shape;
    borderType_ = borderType;
}

// For Distance Tranformation
void watershedSegmenter::setDistTransAttrs(cv::DistanceTypes distanceType, cv::DistanceTransformMasks maskSize, int FGThreshold) {
    distanceType_ = distanceType;
    maskSize_ = maskSize;
    if (FGThreshold < 0 || FGThreshold > 255) {
        std::cerr << "Wrong /'FGThreshold/' value for foreground detection: must be 255 > FGThreshold > 0 " << std::endl;
        FGThreshold_ = 0.7;
    } else {
        FGThreshold_ = FGThreshold / 255.0;
    }


}

// For Connected Components
void watershedSegmenter::setConnCompAttrs(int connectivity) {
    if (connectivity != 4 && connectivity != 8) {
        std::cerr << "Wrong /'connectivity/' value for connected components: must be 4 or 8" << std::endl;
        connectivity_ = 8;
    } else {
        connectivity_ = connectivity;
    }
}
