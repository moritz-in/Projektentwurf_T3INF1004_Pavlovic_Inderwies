#include "Game.h"
#include <iostream>

Game::Game(const std::string& cascadePath) : m_frameWidth(0), m_frameHeight(0) {
    if (!m_faceCascade.load(cascadePath)) {
        std::cerr << "Fehler: Datei konnte nicht geladen werden." << std::endl;
    }
}

Game::~Game() {
    if (m_cap.isOpened()) {
        m_cap.release();
    }
    cv::destroyAllWindows();
}

//Initialiseirung der Gesichtserkennung
bool Game::initialize() {
    if (m_faceCascade.empty()) {
        std::cerr << "Fehler: Gesichtserkennung nicht geladen." << std::endl;
        return false;
    }

    if (!setupCamera()) {
        return false;
    }

    cv::namedWindow(m_windowName, cv::WINDOW_AUTOSIZE);
    return true;
}

// Menu auf der Konsole zeigen
void Game::displayMenu() {
    std::cout << "=== Reaktionsspiel ===" << std::endl;
    std::cout << "Trage deinen Namen ein: ";
    std::string playerName;
    std::getline(std::cin, playerName);

    m_player = std::make_shared<Player>(playerName);
}

//Kamera öffnen und einstellen
bool Game::setupCamera() {
    m_cap.open(0);
    if (!m_cap.isOpened()) {
        std::cerr << "Fehler: Kamera konnte nicht geöffnet werden." << std::endl;
        return false;
    }

    m_frameWidth = static_cast<int>(m_cap.get(cv::CAP_PROP_FRAME_WIDTH));
    m_frameHeight = static_cast<int>(m_cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    if (m_frameWidth == 0 || m_frameHeight == 0) {
        m_frameWidth = 640;
        m_frameHeight = 480;
        m_cap.set(cv::CAP_PROP_FRAME_WIDTH, m_frameWidth);
        m_cap.set(cv::CAP_PROP_FRAME_HEIGHT, m_frameHeight);
    }

    return true;
}

void Game::processFrame(cv::Mat &frame) {
    //TODO!!
}


void Game::startGame() {
    //TODO!!
}

void Game::endGame() {
    //TODO!!
}

// Spiel ausführen
void Game::run() {
    if (!initialize()) return;
    cv::Mat frame;
    while (true) {
        m_cap >> frame;
        if (frame.empty()) break;
        cv::flip(frame, frame, 1);
        std::vector<cv::Rect> faces;
        m_faceCascade.detectMultiScale(frame, faces, 1.1, 3, 0, cv::Size(60, 60));
        for (const auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
        }
        cv::imshow(m_windowName, frame);
        int key = cv::waitKey(10);
        if (key == 27) break; // ESC to exit
    }
}
