#include <gtest/gtest.h>
#include "../include/Circle.h"
#include "../include/Square.h"

// Testet Bewegung und Markierung zur Entfernung für Kreise
TEST(CircleTest, MovementAndRemoval) {
    Circle circle(cv::Point(100, 100), cv::Size(30, 30), cv::Scalar(255, 0, 0), 5);

    circle.update();
    EXPECT_EQ(circle.getRect().y, 105);  // Y-Position nach Bewegung prüfen

    circle.markForRemoval();
    EXPECT_TRUE(circle.shouldBeRemoved());  // Entfernungsmarkierung sollte gesetzt sein
}

// Testet Bewegung und Markierung zur Entfernung für Quadrate
TEST(SquareTest, MovementAndRemoval) {
    Square square(cv::Point(50, 50), cv::Size(40, 40), cv::Scalar(0, 255, 0), 3);

    square.update();
    EXPECT_EQ(square.getRect().y, 53);  // Y-Position nach Bewegung prüfen

    EXPECT_FALSE(square.shouldBeRemoved());  // Sollte anfangs nicht markiert sein
    square.markForRemoval();
    EXPECT_TRUE(square.shouldBeRemoved());   // Entfernungsmarkierung sollte gesetzt sein
}