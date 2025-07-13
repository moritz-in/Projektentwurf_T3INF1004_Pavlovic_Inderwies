//
// Created by Stefan Pavlovic on 27.06.25.
//
#ifndef GAMEMODE_H
#define GAMEMODE_H
#include "Player.h"
#include "Objects.h"



class GameMode {
public:
    GameMode(std::shared_ptr<Player> player, int frameWidth, int frameHeight);
    virtual ~GameMode() = default;

    virtual void update(const cv::Rect& faceRect, cv::Mat& frame) = 0;    //wird in den Kinderklassen überschrieben
    // TODO Draw kommt komplett weg, stattdesse aus Game get_objects aufgerufen und GUI->drawObjects(ausgeführt) im Game ausgeführt
    virtual void draw(cv::Mat& frame) = 0;        //wird in den Kinderklassen überschrieben
    virtual bool isGameOver() const = 0;      //wird in den Kinderklassen überschrieben

protected:
    std::shared_ptr<Player> m_player;
    int m_frameWidth;
    int m_frameHeight;
    // TODO Wirklich unique und net shared_ptr
    std::vector<std::unique_ptr<Objects>> m_objects;

    void spawnObject(int type, const cv::Scalar& color, Shape shape);
    void updateObjects();
    // TODO Collisionen bei Objektklasse checken
    virtual void handleCollision(Objects* obj) = 0;
    void checkCollisions(const cv::Rect& faceRect);
    void removeOffscreenObjects();


};



#endif //GAMEMODE_H