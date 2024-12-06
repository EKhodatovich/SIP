#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Функция для определения длительности по шаблону
cv::Mat detect_duration(const cv::Mat& image, const cv::Mat& duration_template) {
    // Преобразование изображений в оттенки серого
    cv::Mat image_gray, template_gray;
    cv::cvtColor(image, image_gray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(duration_template, template_gray, cv::COLOR_BGR2GRAY);

    // Шаблонное сопоставление
    cv::Mat result;
    cv::matchTemplate(image_gray, template_gray, result, cv::TM_CCOEFF_NORMED);

    // Поиск максимального значения
    double minVal, maxVal;
    cv::Point minLoc, maxLoc;
    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

    // Определение координат для выделения результата
    int h = template_gray.rows;
    int w = template_gray.cols;
    cv::Point top_left(maxLoc.x, maxLoc.y + 20);
    cv::Point bottom_right(top_left.x + w, top_left.y + h + 10);

    // Возврат обрезанного изображения
    return image(cv::Rect(top_left.x, top_left.y, w, h + 10)).clone();
}

// Функция для сопоставления времени по шаблонам
std::string match_time_templates(const cv::Mat& duration_image, const std::vector<std::string>& template_paths) {
    cv::Mat img_gray;
    cv::cvtColor(duration_image, img_gray, cv::COLOR_BGR2GRAY);

    std::vector<std::tuple<int, int, std::string>> detected_times;

    for (const auto& template_path : template_paths) {
        // Загрузка шаблона
        cv::Mat template_img = cv::imread(template_path, cv::IMREAD_GRAYSCALE);
        if (template_img.empty()) {
            std::cerr << "Error loading template: " << template_path << std::endl;
            continue;
        }

        int w = template_img.cols;
        int h = template_img.rows;

        // Шаблонное сопоставление
        cv::Mat result;
        cv::matchTemplate(img_gray, template_img, result, cv::TM_CCOEFF_NORMED);

        // Установка порога
        double threshold = 0.9;
        for (int y = 0; y < result.rows; ++y) {
            for (int x = 0; x < result.cols; ++x) {
                if (result.at<float>(y, x) >= threshold) {
                    detected_times.emplace_back(x, y, template_path);
                }
            }
        }
    }

    // Сортировка по координате x
    std::sort(detected_times.begin(), detected_times.end(), [](const auto& a, const auto& b) {
        return std::get<0>(a) < std::get<0>(b);
    });

    // Сбор распознанного времени
    std::string recognized_time;
    for (const auto& [x, y, template_path] : detected_times) {
        // Извлечение цифры из имени файла (например, templateX.jpg)
        char digit = template_path[template_path.size() - 5];  // Предполагается формат "templateX.jpg"
        recognized_time += digit;
    }

    return recognized_time;
}

int main() {
    // Загрузка изображения и шаблона
    cv::Mat image = cv::imread("images/scr4.jpg");
    cv::Mat duration_template = cv::imread("images/duration.jpg");

    if (image.empty() || duration_template.empty()) {
        std::cerr << "Error loading images!" << std::endl;
        return -1;
    }

    // Определение области длительности
    cv::Mat duration_image = detect_duration(image, duration_template);

    // Загрузка шаблонов цифр
    std::vector<std::string> template_filenames;
    for (int i = 0; i < 10; ++i) {
        template_filenames.push_back("images/template" + std::to_string(i) + ".jpg");
    }

    // Распознавание времени
    std::string detected_time_string = match_time_templates(duration_image, template_filenames);

    // Форматирование времени
    std::string formatted_time;
    if (detected_time_string.length() == 4) {
        formatted_time = detected_time_string.substr(0, 2) + ":" + detected_time_string.substr(2);  // MM:SS
    } else if (detected_time_string.length() == 5) {
        formatted_time = detected_time_string.substr(0, 1) + ":" + detected_time_string.substr(1, 2) + ":" + detected_time_string.substr(3);  // H:MM:SS
    } else if (detected_time_string.length() == 6) {
        formatted_time = detected_time_string.substr(0, 2) + ":" + detected_time_string.substr(2, 2) + ":" + detected_time_string.substr(4);  // HH:MM:SS
    } else {
        formatted_time = detected_time_string;
    }

    // Вывод результата
    std::cout << formatted_time << std::endl;

    // Визуализация результата (опционально)
    cv::imshow("Duration Image", duration_image);
    cv::waitKey(0);

    return 0;
}
