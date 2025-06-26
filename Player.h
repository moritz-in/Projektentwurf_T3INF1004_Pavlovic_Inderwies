#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    Player(const std::string& name);
    
    const std::string& getName() const;
    int getScore() const;
    
    void addScore(int points);
    void setScore(int newScore);
    
private:
    std::string name;
    int score = 0;
};

#endif // PLAYER_H