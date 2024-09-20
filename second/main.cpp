#include <iostream>

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main()
{
    cv::Mat image = cv::imread("c:\\151089.jpg");
    if (image.empty()) {
        std::cout << "Could not open or find the image";
        return 0;
    }
    std::cout << image.size << std::endl;
    // create image window named "My Image"
    cv::Scalar GREEN{0, 255, 0};
    cv::Scalar RED{0, 0, 255};
    cv::Scalar BLUE(255, 0, 0);
    cv::Scalar VULCAN(12, 21, 140);
    cv::Scalar PINK(255, 0, 255);
    cv::Scalar PURPLE(255, 51, 51);
    cv::Scalar CYAN(255, 255, 0);
    cv::Scalar YELLOW(0, 255, 255);
    cv::Scalar FOREST_GREEN(0, 102, 51);
    cv::Scalar ORANGE(0, 128, 255);

    cv::Point center{125, 500};
    cv::circle(image, center, 70, GREEN, 3);

    cv::Point p1 {20, 20};
    cv::Point p2 {900, 900};
    cv::rectangle(image, p1, p2, RED, 10);

    cv::Point p3 {350, 420};
    cv::Point p4 {30, 350};
    cv::line(image, p3, p4, BLUE, 5);

    cv::Size size(50, 100);
    cv::ellipse(image, p3, size, 30, 0, 270, YELLOW, 4);

    cv::Point rhombus[1][4];
    rhombus[0][0] = cv::Point(726, 30);
    rhombus[0][1] = cv::Point(550, 270);
    rhombus[0][2] = cv::Point(726, 513);
    rhombus[0][3] = cv::Point(850, 270);
    const cv::Point* ppt[1] = { rhombus[0] };
    const int npt[] = { 4 };
    cv::fillPoly(image, ppt, npt , 1, PURPLE);

    cv::namedWindow("My Image", cv::WINDOW_NORMAL);
    // show the image on window
    cv::imshow("My Image", image);


    cv::waitKey(0);
    return 0;
}
