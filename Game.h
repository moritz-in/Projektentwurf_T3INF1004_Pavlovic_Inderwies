#ifndef GAME_H
#define GAME_H

#include <opencv2/opencv.hpp>
#include <string>
#include "Player.h"


class Game {
public:
    Game(const std::string& cascadePath);
    ~Game();

    bool initialize();
    void displayMenu();
    bool setupCamera();
    void processFrame(cv::Mat& frame);
    void startGame();
    void endGame();
    void run();

private:
    cv::VideoCapture m_cap;
    cv::CascadeClassifier m_faceCascade;
    const std::string m_windowName = "Face Detection";
    int m_frameWidth;
    int m_frameHeight;
    std::shared_ptr<Player> m_player;
};

#endif // GAME_H