#ifndef GAME_H
#define GAME_H
#include <opencv2/opencv.hpp>
#include <iostream>
#include "GameMode.h"
#include "Gui.h"
#include "Player.h"
#include "Camera.h"
#include "Constants.h"
#include "CatchMode.h"
#include "DodgeMode.h"


class Game {
public:
    Game(const std::string& cascadePath);
    ~Game();

    bool initialize();
    void displayMenu();
    void processFrame(cv::Mat& frame);
    void run();
    void endGame();

private:
    Camera m_camera;
    cv::CascadeClassifier m_faceCascade;
    const std::string m_windowName = Constants::FaceGame;
    std::unique_ptr<GameMode> m_currentMode;
    std::shared_ptr<Player> m_player;
    Gui m_gui;
};

#endif // GAME_H