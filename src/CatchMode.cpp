#include "../include/CatchMode.h"

CatchMode::CatchMode(std::shared_ptr<Player> player, const int width, const int height, const int totalObjects)
    : GameMode(std::move(player), width, height), m_totalObjects(totalObjects) {}

//aktualisiert alle Objekte
void CatchMode::update(const cv::Rect &faceRect, cv::Mat &frame)
{
    // Aktuelle Zeit in Sekunden berechnen
    double currentTime = static_cast<double>(cv::getTickCount()) / cv::getTickFrequency();

    if (m_lastSpawnTime == 0) {
        m_lastSpawnTime = static_cast<int>(std::round(currentTime));
    }

    //neue Objekte spawnen falls die maxAnzahl nicht erreicht und mindestens eine Sekunde vergangen
    if ((m_objectsSpawned < m_totalObjects) && (currentTime - m_lastSpawnTime >= 1.0)) {
        spawnNextObject();
        m_lastSpawnTime = static_cast<int>(std::round(currentTime));
    }

    updateObjects();
    checkCollisions(faceRect);
    removeOffscreenObjects();
}

bool CatchMode::isGameOver() const
{
    return m_objectsSpawned >= m_totalObjects && m_objects.empty();
}


// Falls das Objekt gefangen wird +1 Punkt
void CatchMode::handleCollision(std::shared_ptr<Object> object)
{
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
void CatchMode::spawnNextObject()
{
    if (m_objectsSpawned >= m_totalObjects) return;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> typeDist(0, 1);
    // 50% Chance auf rot (Kreis) oder grün (Quadrat)
    bool isRed = (typeDist(generator) % 2) == 0;
    if (isRed) {
        spawnObject(1, Constants::RED, Shape::CIRCLE);
    } else {
        spawnObject(1, Constants::GREEN, Shape::SQUARE);
    }

    m_objectsSpawned++;
}
int CatchMode::getObjectsSpawned() const
{
    return m_objectsSpawned;
}


const std::vector<std::shared_ptr<Object>> &CatchMode::getObjects() const
{
    return m_objects;
}


