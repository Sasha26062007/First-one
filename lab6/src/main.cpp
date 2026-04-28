#include <opencv2/opencv.hpp>
#include <iostream>
#include "CameraProvider.hpp"
#include "FrameProcessor.hpp"

int main() {
    cv::VideoCapture cap("/home/admin1/system_eng/lab_2/lab6/test_video.mp4", cv::CAP_FFMPEG);
    if (!cap.isOpened()) {
        std::cerr << "Error: Cannot open video file" << std::endl;
        return -1;
    }

    FrameProcessor processor;
    Mode currentMode = Mode::NORMAL;
    int brightness = 100; // По умолчанию яркость 100 (без изменений)

    // Создаем окно ДО цикла, чтобы прикрепить к нему ползунок
    cv::namedWindow("Video", cv::WINDOW_AUTOSIZE);
    
    // Создаем ползунок (Trackbar) в окне "Video"
    cv::createTrackbar("Brightness", "Video", &brightness, 200);

    cv::Mat frame, processedFrame;

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cout << "End of video." << std::endl;
            break;
        }

        // Передаем кадр, текущий режим и значение ползунка в твой идеальный процессор
        processedFrame = processor.process(frame, currentMode, brightness);

        cv::imshow("Video", processedFrame);

        // Ждем 30 мс и считываем нажатие клавиши
        int key = cv::waitKey(30);
        
        // Логика переключения (KeyProcessor)
        if (key == 27 || key == 'q') break; // ESC или Q для выхода
        if (key == '0') currentMode = Mode::NORMAL;
        if (key == '1') currentMode = Mode::INVERT;
        if (key == '2') currentMode = Mode::BLUR;
        if (key == '3') currentMode = Mode::CANNY;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
