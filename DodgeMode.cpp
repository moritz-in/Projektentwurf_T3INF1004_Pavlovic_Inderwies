#include "DodgeMode.h"
#include <chrono>
#include <random>

DodgeMode::DodgeMode(std::shared_ptr<Player> player, int width, int height)
    : GameMode(player, width, height) {
}

//Erszeugung eines zufälligen Objekts
void DodgeMode::spawnRandomBall()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> colorDist(0, 2);
    std::uniform_int_distribution<int> spawnDelayDist(1000, 3000); // 1-3 Sekunden zwischen Spawns

    int colorChoice = colorDist(generator);
    cv::Scalar color;

    switch (colorChoice) {
        case 0: color = cv::Scalar(0, 0, 255); break; // Rot
        case 1: color = cv::Scalar(0, 255, 0); break; // Grün
        case 2: color = cv::Scalar(255, 0, 0); break; // Blau
    }

    spawnObject(1, color, Shape::circle);
}

//Wenn objekt getroffen --> Spiel zuende
void DodgeMode::handleCollision(Objects* object)
{
    m_gameOver = true;
}

//Wenn objekt am Boden angekommen +1 Punkt
void DodgeMode::handleObjectPassed() {
    m_player->addScore(1);
}

void DodgeMode::update(const cv::Rect& faceRect, cv::Mat& frame) {
    int currentTime = static_cast<int>(cv::getTickCount() / cv::getTickFrequency());

    static std::default_random_engine generator(std::random_device{}());
    static std::uniform_int_distribution<int> delayDist(1000, 3000);  // 1 bis 3 Sekunden in ms

    //wenn genug Zeit seit dem letzten Spawn vergeht wird ein neuer Ball gespawnt
    if (currentTime - m_lastSpawnTime >= m_spawnDelay) {
        spawnRandomBall();
        m_lastSpawnTime = currentTime;

        m_spawnDelay = delayDist(generator) / 1000;  // zufällige Wartezeit in Sekunden
    }

    updateObjects();

    for (auto& object : objects) {
      //falls Objekt auf Gesicht trifft oder auf den "Boden" wird das entfernt
        if (object->getRect().y > m_frameHeight && !object->shouldBeRemoved()) {
            handleObjectPassed();
            object->markForRemoval(); //zum Entfernen markieren
        }
    }

    checkCollisions(faceRect);  //prüfen auf Kollision mit dem Spieler
    removeOffscreenObjects();    // Objekte entfernen die nicht mehr benötigt werden
}

void DodgeMode::draw(cv::Mat& frame)
{
  //Zeichnet alle Objekte (wird von GameMode::draw gehandelt)
    GameMode::draw(frame);
}