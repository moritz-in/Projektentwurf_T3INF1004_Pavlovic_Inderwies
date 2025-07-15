#ifndef CAMERA_H
#define CAMERA_H
#include <opencv2/opencv.hpp>
#include <stdexcept>

class Camera {
public:
    explicit Camera(int deviceIndex = 0, int width = 1280, int height = 720);

    ~Camera();

    bool isOpen() const;

    bool readFrame(cv::Mat &frame);

    int getWidth() const;

    int getHeight() const;

    cv::Mat captureFrame();

private:
    cv::VideoCapture m_cap;
    int m_width;
    int m_height;
};


#endif //CAMERA_H
