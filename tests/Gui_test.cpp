#include <gtest/gtest.h>
#include "../include/Gui.h"
#include "../include/Constants.h"
#include "../include/Circle.h"
#include "../include/Square.h"

// Testet Zeichenoperationen der GUI
TEST(GuiTest, DrawingOperations) {
    Gui gui;
    cv::Mat testFrame(480, 640, CV_8UC3, cv::Scalar(0, 0, 0));
    gui.drawFrame(testFrame);

    gui.drawText("Test", 100, 100);
    EXPECT_FALSE(gui.getCurrentFrame().empty());  // Frame sollte nicht leer sein

    // Gefüllte Formen erstellen
    auto circle = std::make_shared<Circle>(cv::Point(200, 200), cv::Size(30, 30), Constants::RED, -1);
    auto square = std::make_shared<Square>(cv::Point(300, 300), cv::Size(40, 40), Constants::GREEN, -1);

    std::vector<std::shared_ptr<Object>> objects = {circle, square};
    gui.drawObjects(objects);

    // Pixel an Mittelpunkten prüfen
    cv::Vec3b circlePixel = gui.getCurrentFrame().at<cv::Vec3b>(215, 215);  // Mittelpunkt des Kreises
    cv::Vec3b squarePixel = gui.getCurrentFrame().at<cv::Vec3b>(320, 320);  // Mittelpunkt des Quadrats

    EXPECT_EQ(circlePixel, cv::Vec3b(0, 0, 255));  // Sollte rot sein (BGR)
    EXPECT_EQ(squarePixel, cv::Vec3b(0, 255, 0));  // Sollte grün sein (BGR)
}

// Testet Input-Handling (nur Methodenexistenz)
TEST(GuiTest, InputHandling) {
    Gui gui;
    EXPECT_NO_THROW(gui.isEscapePressed());  // Methode sollte existieren
}