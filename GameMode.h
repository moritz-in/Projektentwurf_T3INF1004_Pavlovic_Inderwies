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
    virtual void draw(cv::Mat& frame);        //wird in den Kinderklassen überschrieben
    virtual bool isGameOver() const = 0;      //wird in den Kinderklassen überschrieben

protected:
    std::shared_ptr<Player> m_player;
    int m_frameWidth;
    int m_frameHeight;
    std::vector<std::unique_ptr<Objects>> objects;

    void spawnObject(int type, const cv::Scalar& color, Shape shape);
    void updateObjects();

};



#endif //GAMEMODE_H