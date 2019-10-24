#include <cstring>
#include "models/ship.hpp"
#include "std/string.hpp"

Ship::Ship(String name, int price, int maxHealth, int cargoSpace,
           int cannonCapacity, ShipWeight weight, ShipSize size) : 
           name(name), price(price), 
           cargoSpace(cargoSpace),
           cannonCapacity(cannonCapacity),
           maxHealth(maxHealth),
           weight(weight), size(size) {
    this->cargo = unique_ptr<Vector<Good*>>(new Vector<Good*>(true));
    this->cannons = unique_ptr<Vector<Cannon*>>(new Vector<Cannon*>(true));
    this->currentHarbor = nullptr;
    this->health = maxHealth;
}

ShipWeight Ship::getShipWeight() const noexcept {
    return this->weight;
}
ShipSize Ship::getShipSize() const noexcept {
    return this->size;
}
Vector<Cannon*>& Ship::getCannons() const {
    return *this->cannons;
}
void Ship::applyDamage(int damage) noexcept {
    this->health -= damage;
}
void Ship::repair(int amount) noexcept {
    if (this->health + amount >= this->maxHealth)
        this->health = maxHealth;
    else
        this->health += amount;
}

void Ship::addCannon(Cannon* cannon) {
    this->cannons->append(cannon);
}

bool Ship::isSunken() const noexcept {
    return this->health <= 0;
}

bool Ship::isDocked() const noexcept {
    return this->currentHarbor != nullptr;
}

void Ship::sail(int distance) noexcept {
    this->destinationDistance -= distance;
}

void Ship::dock() noexcept {
    this->destinationDistance = 0;
    this->currentHarbor = this->destination;
}

String Ship::getName() const noexcept {
    return this->name;
}

Harbor* Ship::getCurrentHarbor() const noexcept {
    return this->currentHarbor;
}

Harbor* Ship::getDestination() const noexcept {
    return this->destination;
}

Vector<Good*>& Ship::getCargo() const {
    return *this->cargo;
}

int Ship::getDestinationDistance() const noexcept {
    return this->destinationDistance;
}

void Ship::setDestination(Harbor* destination) noexcept {
    this->destination = destination;
}
void Ship::setCurrentHarbor(Harbor* harbor) noexcept {
    this->currentHarbor = harbor;
}

void Ship::setDestinationDistance(int destinationDistance) noexcept {
    this->destinationDistance = destinationDistance;
}

void Ship::setHealth(int health) noexcept {
    if (this->health + health > this->maxHealth)
        this->health = maxHealth;
    this->health += health;
}

size_t Ship::getCargoAmount() const {
    size_t total { 0 };
    for (size_t i = 0; i < cargo->getSize(); i++) {
        total += cargo->get(i)->getAmount();
    }
    return total;
}

int Ship::getHealth() const noexcept {
    return this->health;
}

int Ship::getMaxHealth() const noexcept {
    return this->maxHealth;
}

size_t Ship::getCargoSpace() const noexcept {
    return this->cargoSpace;
}

int Ship::getPrice() const noexcept {
    return this->price;
}

size_t Ship::getCannonCapacity() const noexcept {
    return this->cannonCapacity;
}