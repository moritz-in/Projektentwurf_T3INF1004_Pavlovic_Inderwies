#include "Player.h"

//Konstruktor mit namensübergabe
Player::Player(const std::string& name) : name(name) {
};

//Getterfunktion Name
const std::string& Player::getName() const
{
    return name;
};

//Getterfunktion Score
int Player::getScore() const
{
  return score;
};

//Hochzählen des Score
void Player::addScore(int points)
{
  score += points;
};

//Setterfunktion Score
void Player::setScore(int newScore)
{
  score = newScore;
};

