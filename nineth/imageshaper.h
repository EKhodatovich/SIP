#pragma once
#include <string>
#include <opencv2/imgproc/imgproc.hpp>

class imageShaper
{
public:
    imageShaper();
    void load(const std::string& filename);

    void applyChanges();
    cv::Mat getPrimalImage() const {return primalImage_.clone();};
    cv::Mat getImage() const {return image_.clone();};
    cv::Mat getHarrisImage();
    cv::Mat getGFTTImage();

    // For Brightness and Contrast
    void setBrightCont(double alpha, double beta);

    // For Affine transformations
    void setTranslation(int x, int y);
    void setAngle(double angle);
    void setScaling(double k);
    void setPerspective(double xpersp, double ypersp);

    // For Harris angles
    void setHarrisAttrs(int BS, int kSize, double K);

    // For goodFeaturesToTrack
    void setGFTTAttrs(int maxCorners, double qualityLevel, double minDistance);


private:
    cv::Mat primalImage_;
    cv::Mat image_;

    double alpha_ = 1, beta_ = 0;
    double xpersp_ = 0.8, ypersp_ = 0.8;
    int x_ = 0, y_ = 0;   double angle_ = 0;   double k_ = 1;
    int BS_ = 3, kSize_ = 3; double K_ = 0.04;

    int maxCorners_ = 100; double qualityLevel_ = 0.1, minDistance_ = 5;
};
