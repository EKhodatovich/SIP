#pragma once

#include <opencv2/imgproc.hpp>

class grayImageShaper
{
public:
    grayImageShaper(const std::string &imageName);

    cv::Mat shapedImages(int ksize = 1, double scale = 1, double delta = 1);
private:
    cv::Mat grayImage_;

    cv::Mat normalNoiseImage_;
    cv::Mat uniformNoiseImage_;
};

