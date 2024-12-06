#include <iostream>

#include <opencv2/imgproc.hpp>
#include "mainwindow.h"
#include "opencv2/highgui.hpp"

#include "grayimagefilter.h"
#include "grayimageshaper.h"
#include "qapplication.h"

using namespace cv;

int main(int argc, char** argv)
{
    std::string filename = argc >= 2 ? argv[1] : "image.jpeg";
    grayImageFilter flt(filename);
    cv::namedWindow("Images", cv::WINDOW_NORMAL);
    imshow("Images", flt.filteredImages());

    filename = argc >= 3 ? argv[2] : "polygon_shapes.jpg";
    QApplication app{argc, argv};
    MainWindow window{filename};
    window.show();
    return app.exec();
}
