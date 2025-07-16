#ifndef GAMEMODE_H
#define GAMEMODE_H
#include "Player.h"
#include "Object.h"


class GameMode {
public:
    GameMode(std::shared_ptr<Player> player, int frameWidth, int frameHeight);
    virtual ~GameMode() = default;

    virtual void update(const cv::Rect& faceRect, cv::Mat& frame) = 0;
    virtual bool isGameOver() const = 0;
    virtual const std::vector<std::shared_ptr<Object>>& getObjects() const = 0;
    virtual void handleCollision(std::shared_ptr<Object> obj) = 0;
    void addObject(const std::shared_ptr<Object>& object);
    void removeOffscreenObjects();


protected:
    std::shared_ptr<Player> m_player;
    int m_frameWidth;
    int m_frameHeight;
    std::vector<std::shared_ptr<Object>> m_objects;

    void spawnObject(int type, const cv::Scalar& color, Shape shape);
    void updateObjects();
    void checkCollisions(const cv::Rect& faceRect);
};


#endif //GAMEMODE_H