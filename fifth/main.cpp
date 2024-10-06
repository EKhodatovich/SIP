#include <iostream>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"


int main(int argc, char *argv[])
{
    cv::Mat image = cv::imread("c:\\image.jpeg");
    if (image.empty()) {
        std::cerr << "Could not open or find the image";
        throw std::invalid_argument("Bad iamge");
    }

    cv::Mat primalImage_;
    cvtColor(image, primalImage_, cv::COLOR_RGB2GRAY);
    imshow("PrimalImage", primalImage_);
    int numOfImages = 5;
    srand((unsigned)time(0));

    std::vector<cv::Mat> images_;
    //imshow("Image", newImage);
    for (int n = 0; n < numOfImages; n++)
    {
        cv::Mat newImage;
        primalImage_.copyTo(newImage);
        for( int y = 0; y < primalImage_.rows-2; y++ ) {
            for( int x = 0; x < primalImage_.cols-2; x++ ) {
                for( int c = 0; c < primalImage_.channels(); c++ ) {
                    int k = rand()%100 - 50;
                    // auto beta = ;
                    // if (beta > 254) beta = 254;
                    // else if (beta < 2) beta = 1;
                    newImage.at<cv::Vec3b>(y,x)[c] =
                        cv::saturate_cast<uchar>(primalImage_.at<cv::Vec3b>(y,x)[c] - k );
                }
            }
        }
        //imshow("Image" + std::to_string(n), newImage);
        images_.push_back(newImage);
    }

    cv::Mat resultImage;
    primalImage_.copyTo(resultImage);
    for( int y = 0; y < primalImage_.rows-2; y++ ) {
        for( int x = 0; x < primalImage_.cols-2; x++ ) {
            for( int c = 0; c < primalImage_.channels(); c++ ) {
                int color = 0;
                for (int n = 0; n < numOfImages; n++) {

                    color += cv::saturate_cast<uchar>(images_[n].at<cv::Vec3b>(y,x)[c]);
                }
                color /= numOfImages;
                resultImage.at<cv::Vec3b>(y,x)[c] = color;
            }
        }
    }
    imshow("Result" , resultImage);
    while (true)
    {
        cv::waitKey(100);
        if (cv::getWindowProperty("Result", cv::WND_PROP_VISIBLE) == 0 && cv::getWindowProperty("PrimalImage", cv::WND_PROP_VISIBLE) == 0) {
            break;
        }
    }
    return 0;
}
