//
// Created by Stefan Pavlovic on 26.06.25.
//

#ifndef OBJECTS_H
#define OBJECTS_H
#include <opencv2/opencv.hpp>

enum class Shape{
   square,
   circle
};

class Objects {
public:

    Objects(cv::Point position, cv::Size size, int speed, int type,
               const cv::Scalar& color, Shape shape);

    void update();
    void drawObject(cv::Mat& frame) const;
    void markForRemoval();
    bool shouldBeRemoved() const;

    const cv::Rect& getRect() const;
    int getType() const;

private:
    cv::Rect m_boundingRect;
    cv::Scalar m_color;
    Shape m_shape;

    int m_speed;
    int m_type;
    bool m_shouldRemove = false;
};



#endif //OBJECTS_H
