#include <gtest/gtest.h>
#include "../include/Player.h"

// Testet die Initialisierung des Player-Objekts
TEST(PlayerTest, Initialization) {
    Player player("TestPlayer");
    EXPECT_EQ(player.getName(), "TestPlayer");  //Name sollte korrekt gesetzt sein
    EXPECT_EQ(player.getScore(), 0);            //Start-Score sollte 0 sein
}

// Testet verschiedene Score-Operationen
TEST(PlayerTest, ScoreOperations) {
    Player player("TestPlayer");

    player.addScore(5);
    EXPECT_EQ(player.getScore(), 5);  //Score nach Addition prüfen

    player.addScore(-3);
    EXPECT_EQ(player.getScore(), 2);  // Score nach Subtraktion prüfen

    player.setScore(10);
    EXPECT_EQ(player.getScore(), 10); // Score nach explizitem Setzen prüfen

    player.addScore(-5);
    EXPECT_EQ(player.getScore(), 5);  // Verhindert Score unter 0
}