//
// Created by Stefan Pavlovic on 02.07.25.
//

#include "Square.h"

#include "Square.h"

Square::Square(cv::Point position, cv::Size size, cv::Scalar color, int speed)
    : m_rect(position, size), m_color(color), m_speed(speed) {}

cv::Rect Square::getRect() const {
    return m_rect;
}

cv::Scalar Square::getColor() const {
    return m_color;
}

Shape Square::getType() const {
    return Shape::SQUARE;
}

cv::Mat& Square::getFrame() {
    return m_frame;
}

void Square::update() {
    m_rect.y += m_speed;
}

void Square::markForRemoval() {
    m_markedForRemoval = true;
}

bool Square::shouldBeRemoved() const {
    return m_markedForRemoval;
}

void Square::draw(cv::Mat& frame) const {
    cv::rectangle(frame, m_rect, m_color, -1);
}