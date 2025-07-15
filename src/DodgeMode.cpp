#include "../include/DodgeMode.h"
#include <chrono>
#include <random>

DodgeMode::DodgeMode(std::shared_ptr<Player> player, const int width, const int height)
    : GameMode(player, width, height) {
}

//Erzeugung eines zufälligen Objekts
void DodgeMode::spawnRandomBall() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> colorDist(0, 2);

    int colorChoice = colorDist(generator);
    cv::Scalar color;

    switch (colorChoice) {
        // TODO Konstanten
        case 0: color = cv::Scalar(0, 0, 255); break; // Rot
        case 1: color = cv::Scalar(0, 255, 0); break; // Grün
        case 2: color = cv::Scalar(255, 0, 0); break; // Blau
    }

    spawnObject(1, color, Shape::CIRCLE);
}

//Wenn objekt getroffen --> Spiel zuende
void DodgeMode::handleCollision(std::shared_ptr<Object> obj) {
    m_gameOver = true;
}

//Wenn objekt am Boden angekommen +1 Punkt
void DodgeMode::handleObjectPassed() {
    m_player->addScore(1);
}

const std::vector<std::shared_ptr<Object>> & DodgeMode::getObjects() const {
    return m_objects;
}

void DodgeMode::update(const cv::Rect& faceRect, cv::Mat& frame) {
    // Neue Bälle alle 1.5-3 sekunden
    double currentTime = static_cast<double>(cv::getTickCount()) / cv::getTickFrequency();
    if (currentTime - m_lastSpawnTime >= m_spawnDelay) {
        spawnRandomBall();
        m_lastSpawnTime = static_cast<int>(std::round(currentTime));
        // Neue Verzögerung für nächsten Spawn setzen
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);
        m_spawnDelay = m_spawnDelayDist(generator) / 1000.0; // Convert ms to seconds
    }

    // Zuerst Objekte updaten (Positionen aktualisieren)
    updateObjects();

    // Dann auf Kollisionen und durchgefallene Bälle prüfen
    for (auto& obj : m_objects) {
        if (obj->getRect().y > m_frameHeight && !obj->shouldBeRemoved()) {
            handleObjectPassed();
            obj->markForRemoval();
        }
    }

    // Dann Kollisionen mit dem Gesicht prüfen
    checkCollisions(faceRect);

    // Zum Schluss Objekte entfernen
    removeOffscreenObjects();
}

bool DodgeMode::isGameOver() const {
    return m_gameOver;
}
