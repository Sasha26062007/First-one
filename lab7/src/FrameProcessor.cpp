#include "FrameProcessor.hpp"

FrameProcessor::FrameProcessor() {}

void FrameProcessor::loadNetwork(const std::string& prototxt, const std::string& model) {
    net = cv::dnn::readNetFromCaffe(prototxt, model);
}

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
        case Mode::FACE: {
            result = brightFrame.clone();
            if (!net.empty()) {
                cv::Mat blob = cv::dnn::blobFromImage(brightFrame, 1.0, cv::Size(300, 300), cv::Scalar(104.0, 177.0, 123.0), false, false);
                net.setInput(blob);
                cv::Mat detection = net.forward();
                cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

                for (int i = 0; i < detectionMat.rows; i++) {
                    float confidence = detectionMat.at<float>(i, 2);
                    if (confidence > 0.5) {
                        int xLeftBottom = static_cast<int>(detectionMat.at<float>(i, 3) * brightFrame.cols);
                        int yLeftBottom = static_cast<int>(detectionMat.at<float>(i, 4) * brightFrame.rows);
                        int xRightTop = static_cast<int>(detectionMat.at<float>(i, 5) * brightFrame.cols);
                        int yRightTop = static_cast<int>(detectionMat.at<float>(i, 6) * brightFrame.rows);

                        cv::rectangle(result, cv::Point(xLeftBottom, yLeftBottom), cv::Point(xRightTop, yRightTop), cv::Scalar(0, 255, 0), 2);
                    }
                }
            }
            break;
        }
        case Mode::NORMAL:
        default:
            result = brightFrame.clone();
            break;
    }
    
    return result;
}
