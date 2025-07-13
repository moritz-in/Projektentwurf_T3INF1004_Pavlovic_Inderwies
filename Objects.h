//
// Created by Stefan Pavlovic on 26.06.25.
//

#ifndef OBJECTS_H
#define OBJECTS_H
#include <opencv2/opencv.hpp>

enum class Shape{
   SQUARE,
   CIRCLE
};

//Objects Klasse als Interface implemetiert

class Objects {
public:
   virtual ~Objects() = default;

   virtual cv::Rect getRect() const = 0;
   virtual cv::Scalar getColor() const = 0;
   virtual Shape getType() const = 0;
   virtual cv::Mat& getFrame() = 0;

   virtual void update() = 0;
   virtual void markForRemoval() = 0;
   virtual bool shouldBeRemoved() const = 0;
   virtual void draw(cv::Mat& frame) const = 0;
};



#endif //OBJECTS_H
