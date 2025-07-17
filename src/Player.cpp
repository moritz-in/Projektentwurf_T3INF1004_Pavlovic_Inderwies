#include "../include/Player.h"

Player::Player(const std::string& name) : m_name(name) {};

const std::string& Player::getName() const
{
    return m_name;
};

int Player::getScore() const
{
    return m_score;
};

//Hochzählen des Score
void Player::addScore(int points)
{
    m_score += points;
};

void Player::setScore(int newScore)
{
    m_score = newScore;
};

