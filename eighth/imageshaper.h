#pragma once
#include <string>

#include <opencv2/imgproc/imgproc.hpp>


class imageShaper
{
public:
    imageShaper(const std::string& imageName);
    std::vector<cv::Mat> shapedImage(double thresh1 = 100,
                        double thresh2 = 200,
                        int apertureSize = 3,
                        bool L2Gradient = false,
                        double rho = 1,
                        double theta = CV_PI/180,
                        int thresh = 50
                        );

    cv::Mat cannyImage(double thresh1 = 100,
                       double thresh2 = 200,
                       int apertureSize = 3,
                       bool L2Gradient = false);

    cv::Mat getImage() const { return image_;};
private:
    cv::Mat image_;
    cv::Mat grayImage_;

};
