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
    // This returns the old ship so it can be sold.
    Ship* setShip(Ship* ship);
    // This returns a ptr because there can be no ship, so it should be able to return nullptr
    Ship* getShip() const;
    int getMoney() const;
    void payMoney(int amount);
private:
    Ship* ship;
    int money;
};

#endif