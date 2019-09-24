#include "models/player.hpp"

int Player::getMoney() const {
    return this->money;
}

Ship& Player::getShip() const {
    return *this->ship;
}