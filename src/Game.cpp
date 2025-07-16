#include "../include/Game.h"
#include "../include/CatchMode.h"
#include "../include/DodgeMode.h"
#include <iostream>


Game::Game(const std::string& cascadePath) : m_camera() {
    if (!m_faceCascade.load(cascadePath)) {
        std::cerr << "Fehler: Datei konnte nicht geladen werden." << std::endl;
    }

}

Game::~Game() {
    cv::destroyAllWindows();
}

//Initialiseirung der Gesichtserkennung, Prüfen auf Fehler beim laden
bool Game::initialize() {

    if (m_faceCascade.empty()) {
        std::cerr << "Gesichtserkennung konnte nicht geladen werden" << std::endl;
        return false;
    }

    if (!m_camera.isOpen()) {
        std::cerr << "Kamera konnte nicht geöffnet werden" << std::endl;
        return false;
    }

    cv::namedWindow(m_windowName, cv::WINDOW_AUTOSIZE);
    return true;
}

// Menu auf der Konsole anzeigen
void Game::displayMenu() {
    std::cout << "=== Reaktionsspiel ===" << std::endl;
    std::cout << "Trage deinen Namen ein: ";
    std::string playerName;
    std::getline(std::cin, playerName);

    m_player = std::make_shared<Player>(playerName);

    int choice = 0;
    while (choice < 1 || choice > 2) {
        std::cout << "\nSpielmodus auswählen:\n";
        std::cout << "1. Bälle ausweichen\n";
        std::cout << "2. Quadrate einfangen\n";
        std::cout << "Deine Wahl: ";

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

//verarbeitet ein Kameraframe und ruft die GUI Funktionen zum zeichnen auf
void Game::processFrame(cv::Mat &frame) {
    cv::flip(frame, frame, 1);  //Spiegelt das Frame horizontal

    std::vector<cv::Rect> faces;
    m_faceCascade.detectMultiScale(frame, faces, 1.1, 3, 0, cv::Size(60, 60));

    if (!faces.empty()) {
        cv::rectangle(frame, faces[0], cv::Scalar(0, 255, 0), 2);
        m_currentMode->update(faces[0], frame);
    }

    //GUI Elemente aufrufen
    m_gui.drawFrame(frame);
    m_gui.drawObjects(m_currentMode->getObjects());
    m_gui.drawText(Constants::Score + std::to_string(m_player->getScore()), 10, 30);
    m_gui.showFrame();
}

//startet das Spiel und ruft die Initisalisierung der Kamera sowie Menu Anzeige auf
void Game::run() {
    if (!initialize()) return;
    displayMenu();

    //wiederholt Kamera Frames laden
    while (true) {
        cv::Mat frame = m_camera.captureFrame();
        if (frame.empty()) break;

        processFrame(frame);
        cv::imshow(m_windowName, frame);

        if (m_gui.isEscapePressed()) break;     //beenden falls ESC gedrükt wird

        if (m_currentMode->isGameOver()) {  //beenden falls Game Over
            endGame();
            cv::waitKey(500);
            break;
        }
    }
}

// wird beim GameOver aufgerufen und zeigt die Spielstatistik
void Game::endGame() {
    cv::Mat frame;
    while (true) {
        frame = m_camera.captureFrame();
        if (frame.empty()) break;
        cv::flip(frame, frame, 1);

        //GUI Funktionen für die Anzeige der Spielstatistik nach einem Game Over
        m_gui.drawFrame(frame);
        m_gui.drawText(Constants::GameOver, frame.cols / 2 - 100, frame.rows / 2 - 80);
        m_gui.drawText(Constants::Score + std::to_string(m_player->getScore()), frame.cols / 2 - 100, frame.rows / 2);
        m_gui.drawText(Constants::Player + m_player->getName(), frame.cols / 2 - 100, frame.rows / 2 + 40);
        m_gui.drawText("Mit ESC Taste schliessen!" ,frame.cols / 2 - 100, frame.rows / 2 + 80);

        m_gui.showFrame();

        if (m_gui.isEscapePressed() == true) break; // ESC zum Beenden
    }
}
