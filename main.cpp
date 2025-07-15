#include "include/Game.h"
#include <string>

int main() {
    const std::string cascadeFilePath = "haarcascade_frontalface_default.xml";
    Game game(cascadeFilePath);
    game.run();
    return 0;
}
