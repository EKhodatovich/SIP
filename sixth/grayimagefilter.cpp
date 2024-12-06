#include "grayimagefilter.h"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

grayImageFilter::grayImageFilter(const std::string &imageName)
{
    auto image = cv::imread(imageName);
    if (image.empty()) {
        throw (std::invalid_argument("Bad image name"));
    }
    image.copyTo(grayImage_);
    cvtColor(image, grayImage_, cv::COLOR_RGB2GRAY);
    //cv::imshow("Primal Image" ,grayImage_);
}

Mat grayImageFilter::filteredImages()
{
    Mat result, normalResult, uniformResult;

    std::array<Mat, 5>normalNoiseImages, uniformNoiseImages;

    Mat normalNoiseImage,
        normalNoise(grayImage_.size(), grayImage_.type()),
        uniformNoiseImage,
        uniformNoise(grayImage_.size(), grayImage_.type());


    grayImage_.copyTo(normalNoiseImage);
    randn(normalNoise, 0, 100);
    normalNoiseImages.at(0) = normalNoiseImage + normalNoise;

    grayImage_.copyTo(uniformNoiseImage);
    randu(uniformNoise, -100, 100);
    uniformNoiseImages.at(0) = uniformNoiseImage + uniformNoise;

    GaussianBlur(normalNoiseImages.at(0), normalNoiseImages.at(1), Size{7, 7}, 50);
    GaussianBlur(uniformNoiseImages.at(0), uniformNoiseImages.at(1), Size{7, 7}, 50);

    blur(normalNoiseImages.at(0), normalNoiseImages.at(2), Size{7, 7});
    blur(uniformNoiseImages.at(0), uniformNoiseImages.at(2), Size{7, 7});

    medianBlur(normalNoiseImages.at(0), normalNoiseImages.at(3), 7);
    medianBlur(uniformNoiseImages.at(0), uniformNoiseImages.at(3), 7);

    double m[3][3] = {{0.2, 0.2, 0.2},
                      {0.2, 0.2, 0.2},
                      {0.2, 0.2, 0.2}};
    Mat kernel = Mat(3, 3, CV_32F, m);

    filter2D(normalNoiseImages.at(0), normalNoiseImages.at(4), -1, kernel);
    filter2D(uniformNoiseImages.at(0), uniformNoiseImages.at(4), -1, kernel);

    hconcat(normalNoiseImages, normalResult);
    hconcat(uniformNoiseImages, uniformResult);

    vconcat(std::vector<Mat>{normalResult, uniformResult}, result);
    return result;
};
