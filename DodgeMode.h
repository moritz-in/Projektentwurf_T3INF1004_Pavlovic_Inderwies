#ifndef DODGEMODE_H
#define DODGEMODE_H

#include "GameMode.h"

//Klasse erbt von GameMode
class DodgeMode : public GameMode {
public:
    DodgeMode(std::shared_ptr<Player> player, int width, int height);

    void update(const cv::Rect& faceRect, cv::Mat& frame) override;
    void draw(cv::Mat& frame) override;
    bool isGameOver() const override { return m_gameOver; }
    void handleCollision(Objects* object) override;
    void spawnRandomBall();
    void handleObjectPassed();

private:
    bool m_gameOver = false;
    double m_lastSpawnTime = 0;
    double m_spawnDelay = 2.0; // Standardverzögerung in Sekunden
    std::uniform_int_distribution<int> m_spawnDelayDist{1000, 3000}; // 1-3 Sekunden

};
#endif // DODGEMODE_H