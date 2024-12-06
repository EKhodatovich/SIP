#pragma once

#include <opencv2/imgproc.hpp>

class grayImageFilter
{
public:
    grayImageFilter(const std::string &imageName);

    cv::Mat filteredImages();
private:
    cv::Mat grayImage_;
};


