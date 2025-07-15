#ifndef OBJECT_H
#define OBJECT_H
#include <opencv2/opencv.hpp>
#include "Shape.h"

//Objects Klasse als Interface implemetiert

class Object {
public:
   virtual ~Object() = default;

   virtual cv::Rect getRect() const = 0;
   virtual cv::Scalar getColor() const = 0;
   virtual Shape getType() const = 0;
   virtual cv::Mat& getFrame() = 0;

   virtual void update() = 0;
   virtual void markForRemoval() = 0;
   virtual bool shouldBeRemoved() const = 0;
   virtual void draw(cv::Mat& frame) const = 0;
};



#endif //OBJECT_H
