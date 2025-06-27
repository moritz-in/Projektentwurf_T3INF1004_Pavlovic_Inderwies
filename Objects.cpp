//
// Created by Stefan Pavlovic on 26.06.25.
//
#include "Objects.h"

Objects::Objects(cv::Point position, cv::Size size, int speed, int type, const cv::Scalar& color, Shape shape)
    : m_boundingRect(position, size), m_speed(speed), m_type(type), m_color(color), m_shape(shape){}

// erhöhen der y-Koordinate um Objekt nach unten zu bewegen
void Objects::update()
{
    m_boundingRect.y += m_speed;
}

//zeichen des Objekts (entweder Kreis oder Quadrat)
void Objects::drawObject(cv::Mat& frame) const
{
    cv::Point center(m_boundingRect.x + m_boundingRect.width/2,
                    m_boundingRect.y + m_boundingRect.height/2);

    if (m_shape == Shape::circle) {
        cv::circle(frame, center, m_boundingRect.width/2, m_color, -1);
    } else {
        cv::rectangle(frame, m_boundingRect, m_color, -1);
    }
}

//Objekt wird markiert um es später zu löschen
void Objects::markForRemoval(){
    m_shouldRemove = true;
}

//Objekt löschen
bool Objects::shouldBeRemoved() const {
    return m_shouldRemove;
}

//getter Methode
const cv::Rect& Objects::getRect() const{
    return m_boundingRect;
}

// getter Methode
int Objects::getType() const{
    return m_type;
}