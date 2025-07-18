#ifndef GUI_H
#define GUI_H
#include <vector>
#include <opencv2/opencv.hpp>
#include "Constants.h"
#include "Object.h"
#include "Circle.h"
#include "Square.h"


class Gui {
public:
    void drawFrame(cv::Mat mat);
    // Helferfunktion, die für alle Objekte, die richtige Draw funktion aufruft
    void drawObjects(std::vector<std::shared_ptr<Object>> objects);
    void drawSquare(std::shared_ptr<Square> square);
    void drawCircle(std::shared_ptr<Circle> circle);
    void drawText(std::string text, int x, int y);
    void showFrame();
    bool isEscapePressed();
    const cv::Mat& getCurrentFrame() const;
protected:
    cv::Mat currentFrame;
};

#endif //GUI_H
