//
// Created by Stefan Pavlovic on 27.06.25.
//

#include "GameMode.h"

GameMode::GameMode(std::shared_ptr<Player> player, int frameWidth, int frameHeight) : m_player(player), m_frameWidth(frameWidth), m_frameHeight(frameHeight){}

// erstellt ein neues Objekt
void GameMode::spawnObject(int type, const cv::Scalar& color, Shape shape){
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned>(time(nullptr)));
        seeded = true;
    }
// größe, geschwindigkeit und position werden zufällig bestimmt
    int size = 20 + rand() % 21;
    int x = rand() % m_frameWidth;
    int speed = 3 + rand() % 4;
//erstellte objekte in dem Vektor speichern
    objects.push_back(std::make_unique<Objects>(
        cv::Point(x, -size), cv::Size(size, size),
        speed, type, color, shape
    ));
}

//objekte werden mit der update() Funkion aus Objects aktualisiert (bewegen sich nach unten)
void GameMode::updateObjects()
{
    for(auto& object : objects){
        object->update();
    }
}

//ruft die drawObjectFunktion
void GameMode::draw(cv::Mat& frame) {
    for (auto& obj : objects) {
        obj->drawObject(frame);
    }
}
//Checkt ob kollision, je nachdem welche art von kollision entfernen oder Handlecolision aufrufen
void GameMode::checkCollisions(const cv::Rect& faceRect) {
    for (auto& obj : objects) {
        if (obj->getRect().y > m_frameHeight) {
            // Nur markieren zum Entfernen, keine Punkte vergeben
            obj->markForRemoval();
            continue;
        }

        if ((faceRect & obj->getRect()).area() > 0) {
            handleCollision(obj.get());
        }
    }
}
//entfernt nichtmehr benötigte objekte
void GameMode::removeOffscreenObjects() {
    objects.erase(
        std::remove_if(objects.begin(), objects.end(),
            [](const std::unique_ptr<Objects>& obj) {
                return obj->shouldBeRemoved();
            }),
        objects.end()
    );
}
