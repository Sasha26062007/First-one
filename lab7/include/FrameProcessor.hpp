#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <string>

enum class Mode {
    NORMAL,
    INVERT,
    BLUR,
    CANNY,
    FACE
};

class FrameProcessor {
public:
    FrameProcessor();
    void loadNetwork(const std::string& prototxt, const std::string& model);
    cv::Mat process(const cv::Mat& frame, Mode mode, int brightness);

private:
    cv::dnn::Net net;
};
