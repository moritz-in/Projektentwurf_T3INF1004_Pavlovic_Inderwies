//
// Created by Stefan Pavlovic on 27.06.25.
//

#include <utility>

#include "../include/CatchMode.h"

#include <random>

// TODO Rearrange entries to match header order

CatchMode::CatchMode(std::shared_ptr<Player> player, const int width, const int height, const int totalObjects)
    : GameMode(std::move(player), width, height), m_totalObjects(totalObjects) {
}

// Falls das Objekt gefangen wird +1 Punkt
void CatchMode::handleCollision(std::shared_ptr<Object> object) {
    int pointsDiff;
    if (object->getType() == Shape::SQUARE) {
        pointsDiff = 1;
    } else {
        pointsDiff = -1;
    }
    m_player->addScore(pointsDiff);
    if (m_player->getScore() < 0) {
        //negative Punkte sind verboten
        m_player->setScore(0);
    }
    object->markForRemoval(); // Objekt zur Entfernung markieren
}

//neue Objekte spawnen bis maximale Anzahl an Objekten erreicht wird
void CatchMode::spawnNextObject() {
    if (m_objectsSpawned >= m_totalObjects) return;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> typeDist(0, 1);
    // 50% Chance auf rot (Kreis) oder grün (Quadrat)
    bool isRed = (typeDist(generator) % 2) == 0; // 50% rot, 50% grün
    if (isRed) {
        spawnObject(1, cv::Scalar(0, 0, 255), Shape::CIRCLE); // Roter Kreis
    } else {
        spawnObject(1, cv::Scalar(0, 255, 0), Shape::SQUARE); // Grünes Quadrat
    }

    m_objectsSpawned++;
}

const std::vector<std::shared_ptr<Object>> &CatchMode::getObjects() const {
    return m_objects;
}

void CatchMode::update(const cv::Rect &faceRect, cv::Mat &frame) {
    double currentTime = static_cast<double>(cv::getTickCount()) / cv::getTickFrequency();

    if (m_lastSpawnTime == 0) {
        m_lastSpawnTime = static_cast<int>(std::round(currentTime));
    }

    if ((m_objectsSpawned < m_totalObjects) && (currentTime - m_lastSpawnTime >= 1.0)) {
        spawnNextObject();
        m_lastSpawnTime = static_cast<int>(std::round(currentTime));
    }

    updateObjects();
    checkCollisions(faceRect);
    removeOffscreenObjects();
}

bool CatchMode::isGameOver() const {
    return m_objectsSpawned >= m_totalObjects && m_objects.empty();
}

