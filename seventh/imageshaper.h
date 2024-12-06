#pragma once
#include <string>

#include <opencv2/imgproc/imgproc.hpp>


class imageShaper
{
public:
    imageShaper(const std::string& imageName);
    cv::Mat shapedImage(double thresh1 = 100,
                        double thresh2 = 200,
                        int apertureSize = 3,
                        bool L2Gradient = false,
                        int mode = cv::RETR_EXTERNAL,
                        int method = cv::CHAIN_APPROX_SIMPLE
                        );
    const cv::Mat getImage() const { return image_;};
private:
    cv::Mat image_;
    cv::Mat grayImage_;

};
