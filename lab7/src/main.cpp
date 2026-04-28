#include <opencv2/opencv.hpp>
#include <iostream>
#include "CameraProvider.hpp"
#include "FrameProcessor.hpp"

int main() {
    cv::VideoCapture cap("/home/admin1/system_eng/lab_2/lab7/face_video.mp4", cv::CAP_FFMPEG);
    if (!cap.isOpened()) {
        std::cerr << "Error" << std::endl;
        return -1;
    }

    FrameProcessor processor;
    processor.loadNetwork("/home/admin1/system_eng/lab_2/lab7/deploy.prototxt", "/home/admin1/system_eng/lab_2/lab7/res10_300x300_ssd_iter_140000.caffemodel");

    Mode currentMode = Mode::NORMAL;
    int brightness = 100;

    cv::namedWindow("Video", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("Brightness", "Video", &brightness, 200);

    cv::Mat frame, processedFrame;

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            break;
        }

        processedFrame = processor.process(frame, currentMode, brightness);

        cv::imshow("Video", processedFrame);

        int key = cv::waitKey(30);
        
        if (key == 27 || key == 'q') break; 
        if (key == '0') currentMode = Mode::NORMAL;
        if (key == '1') currentMode = Mode::INVERT;
        if (key == '2') currentMode = Mode::BLUR;
        if (key == '3') currentMode = Mode::CANNY;
        if (key == 'f' || key == 'F') currentMode = Mode::FACE;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
