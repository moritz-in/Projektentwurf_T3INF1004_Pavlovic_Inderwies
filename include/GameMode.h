//
// Created by Stefan Pavlovic on 27.06.25.
//
#ifndef GAMEMODE_H
#define GAMEMODE_H
#include "Player.h"
#include "Object.h"



class GameMode {
public:
    GameMode(std::shared_ptr<Player> player, int frameWidth, int frameHeight);
    virtual ~GameMode() = default;

    virtual void update(const cv::Rect& faceRect, cv::Mat& frame) = 0;    //wird in den Kinderklassen überschrieben
    virtual bool isGameOver() const = 0;      //wird in den Kinderklassen überschrieben
    virtual const std::vector<std::shared_ptr<Object>>& getObjects() const = 0;
protected:
    std::shared_ptr<Player> m_player;
    int m_frameWidth;
    int m_frameHeight;
    std::vector<std::shared_ptr<Object>> m_objects;

    void spawnObject(int type, const cv::Scalar& color, Shape shape);
    void updateObjects();
    virtual void handleCollision(std::shared_ptr<Object> obj) = 0;
    void checkCollisions(const cv::Rect& faceRect);
    void removeOffscreenObjects();

};



#endif //GAMEMODE_H