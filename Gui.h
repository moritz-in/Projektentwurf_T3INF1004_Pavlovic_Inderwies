//
// Created by Stefan Pavlovic on 02.07.25.
//

#ifndef GUI_H
#define GUI_H
#include <vector>
#include "Objects.h"
#include "Circle.h"
#include "Square.h"


class Gui {
public:
    void drawFrame(cv::Mat mat);
    // Helferfunktion, die für alle Objekte, die richtige DRaw funktion aufruft
    void drawObjects(std::vector<std::shared_ptr<Objects>> objects);
    void drawSquare(std::shared_ptr<Square> square);
    void drawCircle(std::shared_ptr<Circle> circle);
    void drawText(std::string text, int x, int y);
    void showFrame();
    bool isEscapePressed();
};

inline void Gui::drawObjects(std::vector<std::shared_ptr<Objects>> objects) {
    for (auto object: objects) {
        switch (object->getType()) {
            case Shape::SQUARE: {
                std::shared_ptr<Square> square = std::static_pointer_cast<Square>(object);
                drawSquare(square);
                break;
            }
            case Shape::CIRCLE: {
                std::shared_ptr<Circle> circle = std::static_pointer_cast<Circle>(object);
                drawCircle(circle);
                break;
            }
        }
    }
}


#endif //GUI_H
