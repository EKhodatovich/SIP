#include "grayimageshaper.h"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

grayImageShaper::grayImageShaper(const std::string& imageName)
{
    auto image = cv::imread(imageName);
    if (image.empty()) {
        throw (std::invalid_argument("Bad image name"));
    }
    image.copyTo(grayImage_);
    cvtColor(image, grayImage_, cv::COLOR_RGB2GRAY);
    //cv::imshow("Primal Image", grayImage_);

    Mat normalNoise(grayImage_.size(), grayImage_.type()),
        uniformNoise(grayImage_.size(), grayImage_.type());

    grayImage_.copyTo(normalNoiseImage_);
    randn(normalNoise, 0, 100);
    normalNoiseImage_ += normalNoise;

    grayImage_.copyTo(uniformNoiseImage_);
    randu(uniformNoise, -100, 100);
    uniformNoiseImage_ += uniformNoise;
}

Mat grayImageShaper::shapedImages(int ksize, double scale, double delta)
{
    Mat result, normalResult, uniformResult;

    std::array<Mat, 5>normalNoiseImages, uniformNoiseImages;

    normalNoiseImages.at(0) = normalNoiseImage_;
    uniformNoiseImages.at(0) = uniformNoiseImage_;

    Sobel(normalNoiseImages.at(0), normalNoiseImages.at(1), -1, 1, 0);
    Sobel(normalNoiseImages.at(0), normalNoiseImages.at(2), -1, 0, 1);
    Sobel(normalNoiseImages.at(0), normalNoiseImages.at(3), -1, 1, 1);
    Laplacian(normalNoiseImages.at(0), normalNoiseImages.at(4), -1, ksize, scale, delta);

    Sobel(uniformNoiseImages.at(0), uniformNoiseImages.at(1), -1, 1, 0);
    Sobel(uniformNoiseImages.at(0), uniformNoiseImages.at(2), -1, 0, 1);
    Sobel(uniformNoiseImages.at(0), uniformNoiseImages.at(3), -1, 1, 1);
    Laplacian(uniformNoiseImages.at(0), uniformNoiseImages.at(4), -1, ksize, scale, delta);

    hconcat(normalNoiseImages, normalResult);
    hconcat(uniformNoiseImages, uniformResult);

    //imshow("tmp", normalResult);
    vconcat(std::vector<Mat>{normalResult, uniformResult}, result);

    return result;
}
