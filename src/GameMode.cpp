#include "../include/GameMode.h"
#include "../include/Circle.h"
#include "../include/Square.h"


GameMode::GameMode(std::shared_ptr<Player> player, int frameWidth, int frameHeight) : m_player(player), m_frameWidth(frameWidth), m_frameHeight(frameHeight){}

// erstellt ein neues Objekt
void GameMode::spawnObject(int speed, const cv::Scalar& color, Shape shape)
{
    int size = 40; // Feste Größe für bessere Sichtbarkeit
    int x = rand() % (m_frameWidth - size);
    cv::Point pos(x, -size); // Startet oberhalb des Bildschirms

    if (shape == Shape::SQUARE) {
        m_objects.push_back(std::make_shared<Square>(pos, cv::Size(size, size), color, speed));
    } else {
        m_objects.push_back(std::make_shared<Circle>(pos, cv::Size(size, size), color, speed));
    }
}

//objekte werden mit der update() Funkion aus Objects aktualisiert (bewegen sich nach unten)
void GameMode::updateObjects()
{
    for(auto& object : m_objects){
        object->update();
    }
}

//Checkt ob kollision, je nachdem welche art von kollision entfernen oder Handlecolision aufrufen
void GameMode::checkCollisions(const cv::Rect& faceRect)
{
    for (auto& object : m_objects) {
        if (object->getRect().y > m_frameHeight) {
            // Nur markieren zum Entfernen, keine Punkte vergeben
            object->markForRemoval();
            continue;
        }

        if ((faceRect & object->getRect()).area() > 0) {
            handleCollision(object);
        }
    }
}
void GameMode::addObject(const std::shared_ptr<Object>& object)
{
    m_objects.push_back(object);
};

//entfernt nichtmehr benötigte objekte
void GameMode::removeOffscreenObjects()
{
    m_objects.erase(
        std::remove_if(m_objects.begin(), m_objects.end(),
            [](const std::shared_ptr<Object>& obj) {
                return obj->shouldBeRemoved();
            }),
        m_objects.end()
    );
}
