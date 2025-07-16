#include <gtest/gtest.h>
#include "../include/CatchMode.h"
#include "../include/Player.h"
#include "../include/Square.h"
#include "../include/Circle.h"

class CatchModeTest : public ::testing::Test {
protected:
    // Wird vor jedem Test ausgeführt
    void SetUp() override {
        player = std::make_shared<Player>("TestPlayer");
        mode = std::make_unique<CatchMode>(player, 800, 600, 5);
    }

    std::shared_ptr<Player> player;
    std::unique_ptr<CatchMode> mode;
};

// Testet das Spawnen von Objekten
TEST_F(CatchModeTest, ObjectSpawn) {
    EXPECT_EQ(mode->getObjects().size(), 0);  // Anfangs keine Objekte
    mode->spawnNextObject();
    EXPECT_EQ(mode->getObjects().size(), 1);  // Nach Spawn ein Objekt
    EXPECT_EQ(mode->getObjectsSpawned(), 1);  // Zähler sollte inkrementiert sein
}

// Testet Kollisionsbehandlung und Score-Berechnung
TEST_F(CatchModeTest, CollisionHandling) {
    auto square = std::make_shared<Square>(cv::Point(0, 0), cv::Size(30, 30), cv::Scalar(0, 255, 0), 1);
    auto circle = std::make_shared<Circle>(cv::Point(0, 0), cv::Size(30, 30), cv::Scalar(0, 0, 255), 1);

    mode->handleCollision(square);
    EXPECT_EQ(player->getScore(), 1);  // Quadrat gibt +1 Punkt

    mode->handleCollision(circle);
    EXPECT_EQ(player->getScore(), 0);  // Kreis gibt -1 Punkt

    // Testet Schutz vor negativem Score
    mode->handleCollision(circle);
    EXPECT_EQ(player->getScore(), 0);  // Score darf nicht unter 0 fallen
}

// Testet Spielende-Bedingung
TEST_F(CatchModeTest, GameCompletion) {
    // Spawnt alle benötigten Objekte
    for (int i = 0; i < 5; i++) {
        mode->spawnNextObject();
    }
    EXPECT_FALSE(mode->isGameOver());  // Spiel sollte noch laufen

    // Entfernt alle Objekte
    for (auto& obj : mode->getObjects()) {
        obj->markForRemoval();
    }
    mode->removeOffscreenObjects();

    EXPECT_TRUE(mode->isGameOver());  // Spiel sollte beendet sein
}