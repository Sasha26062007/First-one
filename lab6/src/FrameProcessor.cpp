#include "FrameProcessor.hpp"

cv::Mat FrameProcessor::process(const cv::Mat& frame, Mode mode, int brightness) {
    cv::Mat result;
    
    int adjustedBrightness = brightness - 100;
    cv::Mat brightFrame;
    frame.convertTo(brightFrame, -1, 1, adjustedBrightness);

    switch (mode) {
        case Mode::INVERT:
            cv::bitwise_not(brightFrame, result);
            break;
        case Mode::BLUR:
            cv::GaussianBlur(brightFrame, result, cv::Size(15, 15), 0);
            break;
        case Mode::CANNY: {
            cv::Mat gray;
            cv::cvtColor(brightFrame, gray, cv::COLOR_BGR2GRAY);
            cv::Canny(gray, result, 100, 200);
            cv::cvtColor(result, result, cv::COLOR_GRAY2BGR);
            break;
        }
        case Mode::NORMAL:
        default:
            result = brightFrame.clone();
            break;
    }
    
    return result;
}
