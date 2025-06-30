//
// Created by Stefan Pavlovic on 27.06.25.
//

#include "CatchMode.h"

CatchMode::CatchMode(std::shared_ptr<Player> player, int width, int height, int totalObjects)
    : GameMode(player, width, height), m_totalObjects(totalObjects) {}

// Falls das Objekt gefangen wird +1 Punkt
void CatchMode::handleCollision(Objects* object)
{
    m_player->addScore(object->getType());
    if (m_player->getScore() < 0) {  //negative Punkte sind verboten
        m_player->setScore(0);
    }
    object->markForRemoval();  // Objekt zur Entfernung markieren
}

//neue Objekte spawnen bis maximale Anzahl an Objekten erreicht wird
void CatchMode::spawnNextObject()
{
    if (m_objectsSpawned >= m_totalObjects) return;

// abwechselnd Objekte spawnen, einmal Kreis, einmal Quadrat
    if (m_objectsSpawned % 2 == 0) {
        spawnObject(-1, cv::Scalar(0, 0, 255), Shape::circle);
    } else {
        spawnObject(1, cv::Scalar(0, 255, 0), Shape::square);
    }

    m_objectsSpawned++;
}

void CatchMode::update(const cv::Rect& faceRect, cv::Mat& frame)
{
    //prüfen ob maximale Anzahl an Objekten erreicht wurde
    if (m_objectsSpawned < m_totalObjects) {
        unsigned int currentTime = cv::getTickCount() / cv::getTickFrequency();
        // jede Sekunde neues Objekt spawnen
        if (currentTime - m_lastSpawnTime >= 1) {
            spawnNextObject();
            m_lastSpawnTime = currentTime; // m_lastSpawnTime aktualisieren
        }
    }

    updateObjects();
    checkCollisions(faceRect);
    removeOffscreenObjects();
}

bool CatchMode::isGameOver() const
{
    return m_objectsSpawned >= m_totalObjects && m_objects.empty();
}

void CatchMode::draw(cv::Mat& frame)
{
    // Zeichnet alle Objekte (wird von GameMode::draw() gehandelt)
    GameMode::draw(frame);
}
