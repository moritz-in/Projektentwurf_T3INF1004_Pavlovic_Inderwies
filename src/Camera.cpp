//
// Created by Stefan Pavlovic on 13.07.25.
//

#include "../include/Camera.h"

Camera::Camera(int deviceIndex, int width, int height)
    : m_width(width), m_height(height) {
    m_cap.open(deviceIndex);
    if (!m_cap.isOpened()) {
        throw std::runtime_error("Could not open camera");
    }
    m_cap.set(cv::CAP_PROP_FRAME_WIDTH, m_width);
    m_cap.set(cv::CAP_PROP_FRAME_HEIGHT, m_height);
}

Camera::~Camera() {
    if (m_cap.isOpened()) {
        m_cap.release();
    }
}

bool Camera::isOpen() const {
    return m_cap.isOpened();
}

bool Camera::readFrame(cv::Mat& frame) {
    return m_cap.read(frame);
}

int Camera::getWidth() const {
    return m_width;
}

int Camera::getHeight() const {
    return m_height;
}

cv::Mat Camera::captureFrame() {
    cv::Mat frame;
    m_cap.read(frame);
    return frame;
}