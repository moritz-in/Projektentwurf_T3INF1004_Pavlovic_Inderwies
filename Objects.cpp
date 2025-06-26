//
// Created by Stefan Pavlovic on 26.06.25.
//
#include "Objects.h"

Objects::Objects(cv::Point position, cv::Size size, int speed,
                       int type, const cv::Scalar& color, Shape shape)
    : m_boundingRect(position, size), m_speed(speed), m_type(type),
      m_color(color), m_shape(shape){
}

void Objects::update() {
    m_boundingRect.y += m_speed;
}

void Objects::draw(cv::Mat& frame) const {
    //TODO!!
}

void Objects::markForRemoval(){
    m_shouldRemove = true;
}


const cv::Rect& Objects::getRect() const{
    return m_boundingRect;
}

int Objects::getType() const{
    return m_type;
}