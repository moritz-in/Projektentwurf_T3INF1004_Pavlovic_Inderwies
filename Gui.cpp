//
// Created by Stefan Pavlovic on 02.07.25.
//

#include "Gui.h"
#include <opencv2/opencv.hpp>

cv::Mat currentFrame; // Hält den aktuellen Frame

void Gui::drawFrame(cv::Mat mat) {
    currentFrame = mat;
}

void Gui::drawSquare(std::shared_ptr<Square> square) {
    cv::rectangle(currentFrame,
                square->getRect(),
                square->getColor(),
                -1); // -1 für gefülltes Rechteck
}

void Gui::drawCircle(std::shared_ptr<Circle> circle) {
    cv::Point center(circle->getRect().x + circle->getRect().width/2,
                    circle->getRect().y + circle->getRect().height/2);
    cv::circle(currentFrame,
              center,
              circle->getRect().width/2,
              circle->getColor(),
              -1); // -1 für gefüllten Kreis
}

void Gui::drawText(std::string text, int x, int y) {
    cv::putText(currentFrame, text, cv::Point(x, y), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 255, 255), 2);
}

void Gui::showFrame() {
    cv::imshow("Face Game", currentFrame);
}

bool Gui::isEscapePressed() {
    return cv::waitKey(1) == 27;  // 27 ist ASCII für ESC Taste
}
