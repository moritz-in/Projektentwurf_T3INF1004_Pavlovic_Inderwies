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
    // TODO Do it in the Constructor for RAII
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

// Menu auf der Konsole zeigen  // TODO auf falsche eingaben prüfen
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
        currentMode = std::make_unique<DodgeMode>(m_player, m_frameWidth, m_frameHeight);
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
        currentMode = std::make_unique<CatchMode>(m_player, m_frameWidth, m_frameHeight, objectCount);
    }
}

//Kamera öffnen und einstellen
bool Game::setupCamera() {
    m_cap.open(0);
    if (!m_cap.isOpened()) {
        std::cerr << "Fehler: Kamera konnte nicht geöffnet werden." << std::endl;
        return false;
    }

    m_frameWidth = 1280;
    m_frameHeight = 720;
    m_cap.set(cv::CAP_PROP_FRAME_WIDTH, m_frameWidth);
    m_cap.set(cv::CAP_PROP_FRAME_HEIGHT, m_frameHeight);

    return true;
}

void Game::processFrame(cv::Mat &frame) {
    cv::flip(frame, frame, 1);

    // TODO Nur größtes Gesicht erkennen
    std::vector<cv::Rect> faces;
    m_faceCascade.detectMultiScale(frame, faces, 1.1, 3, 0, cv::Size(60, 60));

    if (!faces.empty()) {
        // Draw green square around the face
        cv::rectangle(frame, faces[0], cv::Scalar(0, 255, 0), 2);

        currentMode->update(faces[0], frame);
    }

    currentMode->draw(frame);
    // TODO Stattdessen currentMode->get_objects und damit GUI->drawObjects, GUI->drawFrame und GUI->drawText
    //auto objects = currentMode->get_objects();
    //gui->drawObjects(objects);

    // Display score // TODO drawText funktion
    std::string scoreText = "Dein Ergebnis: " + std::to_string(m_player->getScore());
    cv::putText(frame, scoreText, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX,
                0.8, cv::Scalar(255, 255, 255), 2);

    // Check if game is over
    // TODO Game over bitte nur in Run checken
    /*if (currentMode->isGameOver()) {
        endGame();
        cv::waitKey(3000);
        exit(0);
    }*/
}


void Game::run() {
    if (!initialize()) return;

    displayMenu();

    cv::Mat frame;
    while (true) {
        m_cap >> frame;
        if (frame.empty()) break;


        processFrame(frame);

        // TODO Wo werden hier die Spielobjekte gezeichnet

        cv::imshow(m_windowName, frame);

        // Wichtig: Hier die Tastenabfrage // kommt in die getKeyboard funktion
        int key = cv::waitKey(10);
        if (key == 27) {  // ESC-Taste
            std::cout << "Spiel wurde durch ESC-Taste beendet." << std::endl;
            break;
        }

        if (currentMode->isGameOver()) {
            endGame();
            cv::waitKey(3000);  // 3 Sekunden warten
            break;
        }
    }

    endGame();
}

void Game::endGame() {
    std::cout << "\nSpiel Ende!\n";
    std::cout << "Dein Ergebnis " << m_player->getName() << ": " << m_player->getScore() << std::endl;

    // Display game over on screen for 3 seconds
    cv::Mat frame;
    m_cap >> frame;
    if (!frame.empty()) {
        cv::flip(frame, frame, 1);
        cv::putText(frame, "Spiel Ende", cv::Point(frame.cols/4, frame.rows/2),
                    cv::FONT_HERSHEY_SIMPLEX, 1.5, cv::Scalar(0, 0, 255), 3);
        cv::putText(frame, "Dein Ergebnis: " + std::to_string(m_player->getScore()),
                    cv::Point(frame.cols/4, frame.rows/2 + 50),
                    cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
        cv::putText(frame, "Spieler: " + m_player->getName(),
                    cv::Point(frame.cols/4, frame.rows/2 + 100),
                    cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
        cv::imshow(m_windowName, frame);
        cv::waitKey(3000);
    }
}
