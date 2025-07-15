#ifndef GUI_H
#define GUI_H
#include <vector>
#include "Object.h"
#include "Circle.h"
#include "Square.h"


class Gui {
public:
    void drawFrame(cv::Mat mat);
    // Helferfunktion, die für alle Objekte, die richtige DRaw funktion aufruft
    void drawObjects(std::vector<std::shared_ptr<Object>> objects);
    void drawSquare(std::shared_ptr<Square> square);
    void drawCircle(std::shared_ptr<Circle> circle);
    void drawText(std::string text, int x, int y);
    void showFrame();
    bool isEscapePressed();

protected:
    cv::Mat currentFrame;
};

#endif //GUI_H
