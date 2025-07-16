#include <gtest/gtest.h>
#include "../include/GameMode.h"
#include "../include/Player.h"
#include "../include/Circle.h"

// Mock-Klasse zum Testen der abstrakten GameMode-Klasse
class MockGameMode : public GameMode {
public:
    using GameMode::GameMode;

    // Öffentliche Wrapper für geschützte Methoden
    void publicSpawnObject(int type, const cv::Scalar& color, Shape shape) {
        spawnObject(type, color, shape);
    }

    void publicCheckCollisions(const cv::Rect& faceRect) {
        checkCollisions(faceRect);
    }

    // Fügt Objekt direkt hinzu
    void addObject(const std::shared_ptr<Object>& object) {
        m_objects.push_back(object);
    }

    // Dummy-Implementierungen für abstrakte Methoden
    void update(const cv::Rect& faceRect, cv::Mat& frame) override {}
    bool isGameOver() const override { return false; }
    const std::vector<std::shared_ptr<Object>>& getObjects() const override { return m_objects; }
    void handleCollision(std::shared_ptr<Object> obj) override { obj->markForRemoval(); }
};

// Testet Objektverwaltung (Spawn und Entfernung)
TEST(GameModeTest, ObjectManagement) {
    auto player = std::make_shared<Player>("Test");
    MockGameMode mode(player, 800, 600);

    mode.publicSpawnObject(1, cv::Scalar(255, 0, 0), Shape::CIRCLE);
    EXPECT_EQ(mode.getObjects().size(), 1);  // Objekt sollte gespawnt sein

    mode.getObjects()[0]->markForRemoval();
    mode.removeOffscreenObjects();
    EXPECT_TRUE(mode.getObjects().empty());  // Objekt sollte entfernt sein
}

// Testet Kollisionserkennung
TEST(GameModeTest, CollisionDetection) {
    auto player = std::make_shared<Player>("Test");
    MockGameMode mode(player, 800, 600);

    // Teil 1: Kollision testen
    auto obj1 = std::make_shared<Circle>(cv::Point(100, 100), cv::Size(50, 50), cv::Scalar(0, 0, 255), 1);
    mode.addObject(obj1);
    cv::Rect collidingRect(110, 110, 30, 30);
    mode.publicCheckCollisions(collidingRect);
    EXPECT_TRUE(obj1->shouldBeRemoved());  // Kollision sollte erkannt werden

    // Teil 2: Keine Kollision testen
    auto obj2 = std::make_shared<Circle>(cv::Point(100, 100), cv::Size(50, 50), cv::Scalar(0, 0, 255), 1);
    mode.addObject(obj2);
    cv::Rect nonCollidingRect(0, 0, 30, 30);
    mode.publicCheckCollisions(nonCollidingRect);
    EXPECT_FALSE(obj2->shouldBeRemoved());  // Keine Kollision sollte vorliegen
}