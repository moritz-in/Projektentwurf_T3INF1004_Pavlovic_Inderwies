//
// Created by Stefan Pavlovic on 27.06.25.
//

#ifndef CATCHMODE_H
#define CATCHMODE_H
#include "GameMode.h"

class CatchMode : GameMode {
public:
    CatchMode(std::shared_ptr<Player> player, int width, int height, int totalObjects);

    void update(const cv::Rect& faceRect, cv::Mat& frame) override;
    void draw(cv::Mat& frame) override;
    bool isGameOver() const override;
    void handleCollision(Objects* object) override; // override hinzugefügt
    void spawnNextObject();

private:
    int m_totalObjects;
    int m_objectsSpawned = 0;
    int m_lastSpawnTime = 0;

};



#endif //CATCHMODE_H
