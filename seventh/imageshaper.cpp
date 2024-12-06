#include "imageshaper.h"
#include "opencv2/imgcodecs.hpp"

using namespace cv;

imageShaper::imageShaper(const std::string& imageName)
{
    Mat image = imread(imageName);
    if (image.empty()) {
        throw std::invalid_argument("Bad image name");
    }
    image.copyTo(image_);
    cvtColor(image_, grayImage_, COLOR_RGB2GRAY);
}

cv::Mat imageShaper::shapedImage(double thresh1,
                    const double thresh2,
                    const int apertureSize,
                    const bool L2Gradient,
                    const int mode,
                    const int method
                    )
{
    cv::Mat edges;
    cv::Canny(grayImage_, edges, thresh1, thresh2, apertureSize, L2Gradient);

    // Обнаружение контуров
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(edges, contours, mode, method);

    // Отрисовка контуров на исходном изображении
    cv::Mat contourImage = image_.clone();
    cv::drawContours(contourImage, contours, -1, cv::Scalar(0, 255, 0), 2);

    return contourImage;
}
