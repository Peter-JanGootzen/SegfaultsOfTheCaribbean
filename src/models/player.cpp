#include "models/player.hpp"

int Player::getMoney() const noexcept {
    return this->money;
}

Ship* Player::getShip() const noexcept {
    return this->ship.get();
}

unique_ptr<Ship> Player::setShip(unique_ptr<Ship> other) noexcept {
    unique_ptr<Ship> oldShip { std::move(this->ship) };
    this->ship = std::move(other);
    return oldShip; 
}

Player::Player() noexcept {
    this->ship = nullptr;
    this->money = 900'000;
}

void Player::payMoney(int amount) noexcept {
    this->money -= amount;
}

void Player::receiveMoney(int amount) noexcept {
    this->money += amount;
}