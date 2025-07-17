#ifndef CATCHMODE_H
#define CATCHMODE_H
#include "GameMode.h"
#include <random>
#include "../include/Constants.h"


class CatchMode : public GameMode {
public:
    CatchMode(std::shared_ptr<Player> player, int width, int height, int totalObjects);

    void update(const cv::Rect& faceRect, cv::Mat& frame) override;
    bool isGameOver() const override;
    void handleCollision(std::shared_ptr<Object> object) override;
    void spawnNextObject();
    int getObjectsSpawned() const;

    const std::vector<std::shared_ptr<Object>>& getObjects() const override;

private:
    int m_totalObjects;
    int m_objectsSpawned = 0;
    int m_lastSpawnTime = 0;

};



#endif //CATCHMODE_H
