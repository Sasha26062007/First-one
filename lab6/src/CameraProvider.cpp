#include "CameraProvider.hpp"
#include <stdexcept>

CameraProvider::CameraProvider() {
    cap.open("/home/admin1/system_eng/lab_2/lab6/test_video.mp4", cv::CAP_FFMPEG);
    if (!cap.isOpened()) {
        throw std::runtime_error("Cannot open camera");
    }
}

CameraProvider::~CameraProvider() {
    cap.release();
}

cv::Mat CameraProvider::getFrame() {
    cv::Mat frame;
    cap >> frame;
    return frame;
}
