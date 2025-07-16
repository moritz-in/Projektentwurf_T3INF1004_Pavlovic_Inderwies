#include <gtest/gtest.h>
#include "../include/DodgeMode.h"
#include "../include/Player.h"
#include "../include/Circle.h"

class DodgeModeTest : public ::testing::Test {
protected:
    // Wird vor jedem Test ausgeführt
    void SetUp() override {
        player = std::make_shared<Player>("TestPlayer");
        mode = std::make_unique<DodgeMode>(player, 800, 600);
    }

    std::shared_ptr<Player> player;
    std::unique_ptr<DodgeMode> mode;
};

// Testet Punktevergabe bei passierten Objekten
TEST_F(DodgeModeTest, ObjectPassing) {
    auto circle = std::make_shared<Circle>(cv::Point(0, 600), cv::Size(30, 30), cv::Scalar(255, 0, 0), 1);
    mode->addObject(circle);

    mode->handleObjectPassed();
    EXPECT_EQ(player->getScore(), 1);          // Punkt sollte hinzugefügt sein
    EXPECT_TRUE(circle->shouldBeRemoved());    // Objekt sollte zur Entfernung markiert sein
}

// Testet Spielende bei Kollision
TEST_F(DodgeModeTest, GameOverCondition) {
    auto circle = std::make_shared<Circle>(cv::Point(0, 0), cv::Size(30, 30), cv::Scalar(255, 0, 0), 1);
    mode->handleCollision(circle);
    EXPECT_TRUE(mode->isGameOver());  // Spiel sollte beendet sein
}

// Testet das Spawnen von zufälligen Bällen
TEST_F(DodgeModeTest, ObjectSpawning) {
    EXPECT_EQ(mode->getObjects().size(), 0);  // Anfangs keine Objekte
    mode->spawnRandomBall();
    EXPECT_EQ(mode->getObjects().size(), 1);  // Nach Spawn ein Objekt
}