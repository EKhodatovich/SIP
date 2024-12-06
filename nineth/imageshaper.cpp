#include "imageshaper.h"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"

using namespace cv;

imageShaper::imageShaper() {}

void imageShaper::load(const std::string& filename)
{
    Mat image = imread(filename);
    if (image.empty()) {
        throw std::invalid_argument("Bad image name");
    }
    image.copyTo(primalImage_);
}

void imageShaper::applyChanges()
{
    image_ = Mat::zeros(primalImage_.size(), primalImage_.type());
    // Увеличение контраста и яркости
    Mat brightContrastImg;
    primalImage_.convertTo(brightContrastImg, -1, alpha_, beta_);

    // Применяем аффинное преобразование
    Mat imgAffine;
    resize(brightContrastImg, imgAffine, {0,0}, k_, k_);
    Mat M = getRotationMatrix2D(  { (imgAffine.cols-1)/2.0F , (imgAffine.rows-1)/2.0F} , angle_ , k_);
    warpAffine(imgAffine, imgAffine, M, imgAffine.size());
    M = (Mat_<double>(2,3) << 1, 0, x_, 0, 1, y_);
    warpAffine(imgAffine, imgAffine, M, imgAffine.size());

    // Применяем перспективное преобразование
    Point2f srcPoints[4] = { Point(0, 0), Point(imgAffine.cols, 0), Point(0, imgAffine.rows), Point(imgAffine.cols, imgAffine.rows) };
    Point2f dstPoints[4] = { Point(0, 0), Point(imgAffine.cols * xpersp_, 100), Point(100, imgAffine.rows), Point(imgAffine.cols * ypersp_, imgAffine.rows * 0.8) };
    Mat perspectiveMat = getPerspectiveTransform(srcPoints, dstPoints);
    warpPerspective(imgAffine, image_, perspectiveMat, imgAffine.size());

}
cv::Mat imageShaper::getHarrisImage()
{
    Mat imgHarris, imgHarrisNorm;
    cvtColor(image_, imgHarris, COLOR_BGR2GRAY);
    Mat harrisCorners;
    cornerHarris(imgHarris, harrisCorners, BS_, kSize_, k_);
    //normalize(harrisCorners, imgHarrisNorm, 0, 255, NORM_MINMAX, CV_32FC1);
    return imgHarris;
}
cv::Mat imageShaper::getGFTTImage()
{
    Mat result = image_.clone();
    Mat imgHarris = getHarrisImage();
    std::vector<Point2f> shiTomasiCorners;
    goodFeaturesToTrack(imgHarris, shiTomasiCorners, maxCorners_, qualityLevel_, minDistance_);
    for (size_t i = 0; i < shiTomasiCorners.size(); i++) {
        circle(result, shiTomasiCorners[i], 5, Scalar(0, 255, 0), -1);
    }
    return result;
}

// For Brightness and Contrast
void imageShaper::setBrightCont(double alpha, double beta)
{
    alpha_ = alpha;
    beta_ = beta;
    applyChanges();
}

// For Affine transformations
void imageShaper::setTranslation(int x, int y)
{
    x_ = x;
    y_ = y;
    applyChanges();
}
void imageShaper::setAngle(double angle)
{
    angle_ = angle;
    applyChanges();
}
void imageShaper::setScaling(double k)
{
    k_ = k;
    applyChanges();
}

void imageShaper::setPerspective(double xpersp, double ypersp)
{
    xpersp_ = xpersp;
    ypersp_ = ypersp;
    applyChanges();
}

// For Harris angles
void imageShaper::setHarrisAttrs(int blockSize, int kSize, double K)
{
    if (blockSize < 3 || blockSize > 7 || !(blockSize%2)) {
        throw std::invalid_argument("Bad blockSize: must be 3, 5 or 7");
    }
    if (kSize < 3 || kSize > 7 || !(kSize%2)) {
        throw std::invalid_argument("Bad kSize: must be 3, 5 or 7");
    }
    BS_ = blockSize;
    kSize_ = kSize;
    K_ = K;
}

// For goodFeaturesToTrack
void imageShaper::setGFTTAttrs(int maxCorners, double qualityLevel, double minDistance)
{
    if (maxCorners < 0) {
        throw std::invalid_argument("Bad maxCorners: must be positive");
    }
    if (qualityLevel >= 1 || qualityLevel <= 0) {
        throw std::invalid_argument("Bad qualityLevel: must be in range (0,1)");
    }

    maxCorners_ = maxCorners;
    qualityLevel_ = qualityLevel;
    minDistance_ = minDistance;
}
