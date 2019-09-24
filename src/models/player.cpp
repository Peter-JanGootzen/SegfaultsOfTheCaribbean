#include "models/player.hpp"

int Player::getMoney() const {
    return this->money;
}

Ship* Player::getShip() const {
    return this->ship;
}

Player::Player() {
    this->ship = nullptr;
}

Player::~Player() {
    delete this->ship;  
}

Player::Player(Player&& other) {
    this->money = other.money;

    this->ship = other.ship;
    other.ship = nullptr;
}
Player& Player::operator=(Player&& other) {
    if (this != &other) {
        this->money = other.money;

        if (this->ship != nullptr)
            delete this->ship;
        this->ship = other.ship;
        other.ship = nullptr;
    }
    return *this;
}
