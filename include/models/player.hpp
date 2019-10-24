#ifndef FILE_PLAYER_HPP
#define FILE_PLAYER_HPP
#include "models/player.hpp"
#include "models/ship.hpp"

class Player {
public:
    Player() noexcept;
    Player(Player&& other) = delete;
    Player(const Player& other) = delete;
    Player& operator=(Player&& other) = delete;
    Player& operator=(const Player& other) = delete;
    ~Player() = default;
    // This returns the old ship so it can be sold.
    unique_ptr<Ship> setShip(unique_ptr<Ship> ship) noexcept;
    // This returns a ptr because there can be no ship, so it should be able to return nullptr
    Ship* getShip() const noexcept;
    int getMoney() const noexcept;
    void payMoney(int amount) noexcept;
    void receiveMoney(int amount) noexcept;
private:
    unique_ptr<Ship> ship;
    int money;
};

#endif