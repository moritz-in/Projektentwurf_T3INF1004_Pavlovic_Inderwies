#include "Game.h"
#include <iostream>

Game::Game(const std::string& cascadePath) : m_camera() {
    if (!m_faceCascade.load(cascadePath)) {
        std::cerr << "Fehler: Datei konnte nicht geladen werden." << std::endl;
    }

}

Game::~Game() {
    cv::destroyAllWindows();
}

//Initialiseirung der Gesichtserkennung
bool Game::initialize() {

    if (m_faceCascade.empty()) {
        std::cerr << "Error: Face detection not loaded." << std::endl;
        return false;
    }

    if (!m_camera.isOpen()) {
        std::cerr << "Error: Camera not opened." << std::endl;
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

    int choice = 0;
    while (choice < 1 || choice > 2) {
        std::cout << "\nSpielmodus auswählen:\n";
        std::cout << "1. Ausweichen\n";
        std::cout << "2. Einfangen\n";
        std::cout << "Deine Wahl: ";   // kurze Anleitung wie Modus funktioniert (Erweiterung später)

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Falsche Eingabe. Bitte 1 oder 2 eingeben!.\n";
            choice = 0;
        }
    }

    if (choice == 1) {
        m_currentMode = std::make_unique<DodgeMode>(m_player, m_camera.getWidth(), m_camera.getHeight());
    } else {
        int objectCount = 0;
        while (objectCount <= 0) {
            std::cout << "Anzahl der gewünschten Objekte angeben: ";
            if (!(std::cin >> objectCount)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Falsche Eingabe. Bitte nur positive Zahlen eingeben!\n";
            }
        }
        m_currentMode = std::make_unique<CatchMode>(m_player, m_camera.getWidth(), m_camera.getHeight(), objectCount);
    }
}

void Game::processFrame(cv::Mat &frame) {
    cv::flip(frame, frame, 1);

    std::vector<cv::Rect> faces;
    m_faceCascade.detectMultiScale(frame, faces, 1.1, 3, 0, cv::Size(60, 60));

    if (!faces.empty()) {
        cv::rectangle(frame, faces[0], cv::Scalar(0, 255, 0), 2);
        m_currentMode->update(faces[0], frame);
    }

    m_gui.drawObjects(m_currentMode->getObjects());

    std::string scoreText = "Score: " + std::to_string(m_player->getScore());
    m_gui.drawText(scoreText, 10, 30);
}


void Game::run() {
    if (!initialize()) return;
    displayMenu();

    while (true) {
        cv::Mat frame = m_camera.captureFrame();
        if (frame.empty()) break;

        processFrame(frame);
        cv::imshow(m_windowName, frame);

        if (m_gui.isEscapePressed()) break;

        if (m_currentMode->isGameOver()) {
            endGame();
            cv::waitKey(3000);
            break;
        }
    }
}

void Game::endGame() {
    std::cout << "\nGame Over!\n";
    std::cout << "Your score " << m_player->getName() << ": " << m_player->getScore() << std::endl;

    cv::Mat frame;
    if (m_camera.readFrame(frame) && !frame.empty()) {
        cv::flip(frame, frame, 1);
        m_gui.drawText("Game Over", cv::Point(frame.cols/4, frame.rows/2),
                      cv::Scalar(0, 0, 255), 1.5, 3, frame);
        m_gui.drawText("Score: " + std::to_string(m_player->getScore()),
                      cv::Point(frame.cols/4, frame.rows/2 + 50),
                      cv::Scalar(255, 255, 255), 1, 2, frame);
        m_gui.drawText("Player: " + m_player->getName(),
                      cv::Point(frame.cols/4, frame.rows/2 + 100),
                      cv::Scalar(255, 255, 255), 1, 2, frame);
        cv::imshow(m_windowName, frame);
        cv::waitKey(3000);
    }
}
