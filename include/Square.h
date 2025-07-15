#ifndef SQUARE_H
#define SQUARE_H
#include "Object.h"


class Square : public Object {
public:
    Square(cv::Point position, cv::Size size, cv::Scalar color, int speed);

    cv::Rect getRect() const override;
    cv::Scalar getColor() const override;
    Shape getType() const override;
    cv::Mat& getFrame() override;

    void update() override;
    void markForRemoval() override;
    bool shouldBeRemoved() const override;
    void draw(cv::Mat& frame) const override;

private:
    cv::Rect m_rect;
    cv::Scalar m_color;
    int m_speed;
    bool m_markedForRemoval = false;
    cv::Mat m_frame;
};



#endif //SQUARE_H
