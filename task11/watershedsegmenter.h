#include <opencv2/imgproc/imgproc.hpp>

#include <string>
class watershedSegmenter
{
public:
    watershedSegmenter();
    void load(const std::string& filename);

    cv::Mat getPrimalImage() const {return primalImage_.clone();};
    cv::Mat getWatershedImage();

    // For Dilatation
    void setDilateAttrs(cv::MorphShapes shape, int size, int iterations, cv::BorderTypes borderType);

    // For Distance Tranformation
    void setDistTransAttrs(cv::DistanceTypes distanceType, cv::DistanceTransformMasks maskSize, int FGThreshold);

    // For Connected Components
    void setConnCompAttrs(int connectivity);


private:
    cv::Mat primalImage_;

    cv::MorphShapes shape_ = cv::MORPH_RECT;
    int size_ = 3;
    int iterations_ = 1;
    cv::BorderTypes borderType_ = cv::BORDER_CONSTANT;

    cv::DistanceTypes distanceType_ = cv::DIST_L2;
    cv::DistanceTransformMasks maskSize_ = cv::DIST_MASK_3;
    double FGThreshold_ = 0.7;

    int connectivity_ = 8;
};
