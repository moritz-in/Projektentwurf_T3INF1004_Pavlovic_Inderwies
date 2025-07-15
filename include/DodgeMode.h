#ifndef DODGEMODE_H
#define DODGEMODE_H

#include "GameMode.h"

//Klasse erbt von GameMode
class DodgeMode : public GameMode {
public:
    DodgeMode(std::shared_ptr<Player> player, int width, int height);

    void update(const cv::Rect& faceRect, cv::Mat& frame) override;
    bool isGameOver() const override;
    void handleCollision(std::shared_ptr<Object> object) override;
    void spawnRandomBall();
    void handleObjectPassed();
    const std::vector<std::shared_ptr<Object>>& getObjects() const override;

private:
    bool m_gameOver = false;
    int m_lastSpawnTime = 0;
    double m_spawnDelay = 2.0; // Standardverzögerung in Sekunden
    std::uniform_int_distribution<int> m_spawnDelayDist{1000, 3000}; // 1-3 Sekunden

};
#endif // DODGEMODE_H