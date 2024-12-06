#include <QApplication>

#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <opencv2/features2d.hpp>

using namespace cv;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Mat image = imread("image.png", IMREAD_GRAYSCALE);
    Mat smallImage = imread("small_image.png", IMREAD_GRAYSCALE);
    if (image.empty() || smallImage.empty()) {
        throw std::invalid_argument("Bad image name");
    }

    int numKeypoints = 1000;
    Ptr<ORB> orb = ORB::create(numKeypoints);

    // Обнаружение ключевых точек и вычисление дескрипторов
    std::vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;
    orb->detectAndCompute(image, noArray(), keypoints1, descriptors1);
    orb->detectAndCompute(smallImage, noArray(), keypoints2, descriptors2);

    // Сопоставление дескрипторов
    // Лучше использовать BFMatcher или FLANN
    std::vector<DMatch> matches;
    BFMatcher matcher(NORM_HAMMING);
    matcher.match(descriptors1, descriptors2, matches);

    // Отфильтровываем совпадения по расстоянию
    double max_dist = 0;
    double min_dist = 100;

    for (int i = 0; i < matches.size(); i++) {
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }

    std::vector<DMatch> good_matches;
    for (int i = 0; i < matches.size(); i++) {
        if (matches[i].distance <= std::max(2 * min_dist, 30.0)) {
            good_matches.push_back(matches[i]);
        }
    }

    // Отображение соответствий
    Mat img_matches;
    drawMatches(image, keypoints1, smallImage, keypoints2, good_matches, img_matches,
                Scalar::all(-1), Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    // Показ изображений
    namedWindow("Matches", WINDOW_NORMAL);
    imshow("Matches", img_matches);
    waitKey(0);

    return QApplication::exec();
}
