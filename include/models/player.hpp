#ifndef FILE_PLAYER_HPP
#define FILE_PLAYER_HPP
#include "models/player.hpp"
#include "models/ship.hpp"

class Player {
public:
    Player();
    Player(Player&& other);
    Player(const Player& other) = delete;
    Player& operator=(Player&& other);
    Player& operator=(const Player& other) = delete;
    ~Player();
    Ship* getShip() const;
    int getMoney() const;
private:
    Ship* ship;
    int money;
};

#endif