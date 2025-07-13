//
// Created by Stefan Pavlovic on 26.06.25.
//

#ifndef OBJECTS_H
#define OBJECTS_H
#include <opencv2/opencv.hpp>

// TODO Eigene Datei und ALL CAPS
enum class Shape{
   square,
   circle
};

// TODO als Interface definieren und Kindklassen Square und Circle
class Objects {
public:

    Objects(cv::Point position, cv::Size size, int speed, int type,
               const cv::Scalar& color, Shape shape);

    // TODO Alles virtual
    void update();
    // TODO GUI in Guiklasse verschieben
    void drawObject(cv::Mat& frame) const;
    void markForRemoval();
    bool shouldBeRemoved() const;

    const cv::Rect& getRect() const;
    // TODO Bitte behalten, sonst machst du dir das Leben viel schwerer
    int getType() const;

private:
    cv::Rect m_positionRect;
    cv::Scalar m_color;
    Shape m_shape;

    int m_speed;
    int m_type;
    bool m_shouldRemove = false;
};



#endif //OBJECTS_H
