#include "../include/Circle.h"

Circle::Circle(cv::Point position, cv::Size size, cv::Scalar color, int speed)
    : m_rect(position, size), m_color(color), m_speed(speed) {}

cv::Rect Circle::getRect() const
{
    return m_rect;
}

cv::Scalar Circle::getColor() const
{
    return m_color;
}

Shape Circle::getType() const
{
    return Shape::CIRCLE;
}

cv::Mat& Circle::getFrame()
{
    return m_frame;
}

void Circle::update()
{
    m_rect.y += m_speed;
}

void Circle::markForRemoval()
{
    m_markedForRemoval = true;
}

bool Circle::shouldBeRemoved() const
{
    return m_markedForRemoval;
}

void Circle::draw(cv::Mat& frame) const  {
    cv::Point center(m_rect.x + m_rect.width/2, m_rect.y + m_rect.height/2);
    int radius = m_rect.width / 2;
    cv::circle(frame, center, radius, m_color, -1);
}