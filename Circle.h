//
// Created by Stefan Pavlovic on 13.07.25.
//

#ifndef CIRCLE_H
#define CIRCLE_H

#include "Objects.h"

class Circle : public Objects {
public:
    Circle(cv::Point position, cv::Size size, cv::Scalar color, int speed);

    // Interface implementations
    cv::Rect getRect() const override;
    cv::Scalar getColor() const override;
    Shape getType() const override;
    cv::Mat& getFrame() override;

    void update() override;
    void markForRemoval() override;
    bool shouldBeRemoved() const override;

    // Originalmethoden
    void draw(cv::Mat& frame) const override;

private:
    cv::Rect m_rect;
    cv::Scalar m_color;
    int m_speed;
    bool m_markedForRemoval = false;
    cv::Mat m_frame;
};

#endif // CIRCLE_H
