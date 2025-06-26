#include "Player.h"

//Konstruktor mit namensübergabe
Player::Player(const std::string& name) : m_name(name) {
};

//Getterfunktion Name
const std::string& Player::getName() const
{
    return m_name;
};

//Getterfunktion Score
int Player::getScore() const
{
    return m_score;
};

//Hochzählen des Score
void Player::addScore(int points)
{
    m_score += points;
};

//Setterfunktion Score
void Player::setScore(int newScore)
{
    m_score = newScore;
};

