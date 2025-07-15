#include "include/Game.h"
#include <string>

// TODO Spiellogik zusammen mit Grafik (GUI und Logik trennen)
// TODO Verflechtung der Klassen reduzieren (Kamera, Square, Circle, GUI)

int main() {
    const std::string cascadeFilePath = "haarcascade_frontalface_default.xml";
    Game game(cascadeFilePath);
    game.run();
    return 0;
}