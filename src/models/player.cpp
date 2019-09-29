#include "models/player.hpp"

int Player::getMoney() const {
    return this->money;
}

Ship* Player::getShip() const {
    return this->ship;
}

Ship& Player::setShip(Ship* other) {
    Ship& oldShip = *this->ship;
    this->ship = other;
    return oldShip; 
}

Player::Player() {
    this->ship = nullptr;
    this->money = 5000;
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

void Player::payMoney(int amount) {
    this->money -= amount;
}