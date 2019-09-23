#ifndef FILE_PLAYER_HPP
#define FILE_PLAYER_HPP
#include "models/player.hpp"
#include "models/ship.hpp"

class Player {
public:
    Ship& getShip() const;
    int getMoney() const;
private:
    Ship* ship;
    int money;
};

#endif