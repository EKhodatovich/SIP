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

Mat imageShaper::cannyImage(const double thresh1,
                   const double thresh2,
                   const int apertureSize,
                   const bool L2Gradient)
{
    Mat edges;
    Canny(grayImage_, edges, thresh1, thresh2, apertureSize, L2Gradient);

    // Обнаружение контуров
    std::vector<std::vector<Point>> contours;
    findContours(edges, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

    // Отрисовка контуров на исходном изображении
    Mat contourImage = image_.clone();
    drawContours(contourImage, contours, -1, Scalar(0, 255, 0), 2);

    return contourImage;
}

std::vector<Mat> imageShaper::shapedImage(const double thresh1,
                                 const double thresh2,
                                 const int apertureSize,
                                 const bool L2Gradient,
                                 const double rho,
                                 const double theta,
                                 const int thresh)
{
    // Применяем гауссово размытие
    Mat blurred;
    GaussianBlur(grayImage_, blurred, Size(5, 5), 0);

    Mat edges;
    Canny(blurred, edges, thresh1, thresh2, apertureSize, L2Gradient);


    // Применяем преобразование Хафа для поиска линий
    std::vector<Vec2f> lines;
    HoughLines(edges, lines, rho, theta, thresh); // параметры подбирайте под свои данные

    // Подготовка данных для контуров
    Mat imgContours = Mat::zeros(image_.size(), CV_8UC3);
    cvtColor(edges, imgContours, COLOR_GRAY2BGR);
    for (size_t i = 0; i < lines.size(); i++) {
        double rho = lines[i][0];
        double theta = lines[i][1];

        // Вычисляем начальные и конечные координаты линии
        double a = cos(theta);
        double b = sin(theta);
        double x0 = a * rho;
        double y0 = b * rho;

        Point pt1(cvRound(x0 + 1000 * (-b)), cvRound(y0 + 1000 * (a)));
        Point pt2(cvRound(x0 - 1000 * (-b)), cvRound(y0 - 1000 * (a)));

        line(imgContours, pt1, pt2, Scalar(0, 0, 255), 2, LINE_AA);
    }



    // Применяем преобразование Хафа для поиска линий
    std::vector<Vec4i> linesP;
    HoughLinesP(edges, linesP, rho, theta, thresh, 30, 10); // параметры подбирайте под свои данные

    // Подготовка данных для контуров
    Mat imgContoursP = Mat::zeros(image_.size(), CV_8UC3);
    cvtColor(edges, imgContoursP, COLOR_GRAY2BGR);
    for (size_t i = 0; i < linesP.size(); i++) {
        line(imgContoursP, Point(linesP[i][0], linesP[i][1]),
                 Point(linesP[i][2], linesP[i][3]),
                 Scalar(0, 0, 255), 2, LINE_AA);
    }



    return {imgContours, imgContoursP};
}
