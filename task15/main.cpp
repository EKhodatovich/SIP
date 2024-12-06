#include "mainwindow.h"
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // return a.exec();

    // Путь к видеофайлу или использование камеры
    std::string video_path = "pedestrians2.mp4";  // Замените на путь к видео или 0 для камеры
    cv::VideoCapture cap(video_path);

    cv::namedWindow("Pedestrian Detection", cv::WINDOW_NORMAL);
    if (!cap.isOpened()) {
        std::cerr << "Error opening file" << std::endl;
        return -1;
    }

    // Инициализация HOG детектора
    cv::HOGDescriptor hog;
    hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());

    cv::Mat frame;

    while (cap.read(frame)) {
        // Изменяем размер кадра для ускорения обработки (опционально)
        // cv::resize(frame, frame, cv::Size(640, 480));

        // Обнаружение пешеходов
        std::vector<cv::Rect> detections;
        std::vector<double> weights;
        hog.detectMultiScale(frame, detections, weights, 0, cv::Size(8, 8), cv::Size(16, 16), 1.05);

        // Рисуем рамки вокруг обнаруженных пешеходов
        for (size_t i = 0; i < detections.size(); i++) {
            cv::rectangle(frame, detections[i], cv::Scalar(0, 255, 0), 2);
        }

        // Показ кадра с обнаруженными пешеходами
        cv::imshow("Pedestrian Detection", frame);

        // Нажмите 'q' для выхода
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
