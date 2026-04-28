#include "Display.hpp"

Display::Display(const std::string& winName) : windowName(winName) {
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("Brightness", windowName, nullptr, 200);
    cv::setTrackbarPos("Brightness", windowName, 100);
}

void Display::show(const cv::Mat& frame) {
    cv::imshow(windowName, frame);
}

int Display::getBrightness() const {
    return cv::getTrackbarPos("Brightness", windowName);
}
