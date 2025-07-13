//
// Created by Stefan Pavlovic on 27.06.25.
//

#include "GameMode.h"

#include "Circle.h"
#include "Square.h"

GameMode::GameMode(std::shared_ptr<Player> player, int frameWidth, int frameHeight) : m_player(player), m_frameWidth(frameWidth), m_frameHeight(frameHeight){}

// erstellt ein neues Objekt
void GameMode::spawnObject(int type, const cv::Scalar& color, Shape shape){
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned>(time(nullptr)));
        seeded = true;
    }
    // TODO bessere Randomfunktion suchen
// größe, geschwindigkeit und position werden zufällig bestimmt
    int size = 20 + rand() % 21;
    int x = rand() % m_frameWidth;
    int speed = 3 + rand() % 4;
//erstellte objekte in dem Vektor speichern
    if (type == Shape::SQUARE) {
        m_objects.push_back(std::make_shared<Square>(pos, size, speed, color));
    } else if (type == Shape::CIRCLE) {
        m_objects.push_back(std::make_shared<Circle>(pos, size, speed, color));
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
void GameMode::checkCollisions(const cv::Rect& faceRect) {
    for (auto& object : m_objects) {
        if (object->getRect().y > m_frameHeight) {
            // Nur markieren zum Entfernen, keine Punkte vergeben
            object->markForRemoval();
            continue;
        }

        if ((faceRect & object->getRect()).area() > 0) {
            handleCollision(object.get());
        }
    }
}
//entfernt nichtmehr benötigte objekte
void GameMode::removeOffscreenObjects() {
    m_objects.erase(
        std::remove_if(m_objects.begin(), m_objects.end(),
            [](const std::shared_ptr<Objects>& obj) {
                return obj->shouldBeRemoved();
            }),
        m_objects.end()
    );
}
