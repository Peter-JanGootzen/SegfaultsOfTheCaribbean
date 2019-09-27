#include <cstring>
#include "models/ship.hpp"
#include "std/string.hpp"

Ship::Ship(String name, int price, int maxHealth, int cargoSpace,
           int cannonCapacity, ShipWeight weight, ShipSize size) : 
           name(name), price(price), maxHealth(maxHealth), 
           cargoSpace(cargoSpace), cannonCapacity(cannonCapacity),
           weight(weight), size(size) {
    this->cargo = nullptr;
    this->currentHarbor = nullptr;
    this->health = maxHealth;
};

Ship::Ship() {
    this->cargo = nullptr;
    this->currentHarbor = nullptr;
};

Ship::Ship(Ship&& other) {
    // stack
    this->name = other.name;
    this->price = other.price;
    this->cargoSpace = other.cargoSpace;
    this->cannonCapacity = other.cannonCapacity;
    this->health = other.health;
    this->destinationDistance = other.destinationDistance;
    this->weight = other.weight;
    this->size = other.size;
    this->cargoSize = other.cargoSize;

    // heap
    this->destination = other.destination;
    other.destination = nullptr;
    this->currentHarbor = other.currentHarbor;
    other.currentHarbor = nullptr;
    this->cargo = other.cargo;
    other.cargo = nullptr;
};

//Ship::Ship(const Ship& other) {
//    this->name = other.name;
//    this->price = other.price;
//    this->cargoSpace = other.cargoSpace;
//    this->cannonCapacity = other.cannonCapacity;
//    this->health = other.health;
//    this->destinationDistance = other.destinationDistance;
//    this->weight = other.weight;
//    this->size = other.size;
//    this->cargo = new Good[other.cargoSize];
//    this->cargoSize = other.cargoSize;
//
//    // heap
//    std::memcpy(this->cargo, other.cargo, other.cargoSize);
//};

Ship& Ship::operator=(Ship&& other) {
    if(this != &other) {
        // stack
        this->name = other.name;
        this->price = other.price;
        this->cargoSpace = other.cargoSpace;
        this->cannonCapacity = other.cannonCapacity;
        this->health = other.health;
        this->destinationDistance = other.destinationDistance;
        this->weight = other.weight;
        this->size = other.size;
        this->cargoSize = other.cargoSize;

        // heap
        this->destination = other.destination;
        other.destination = nullptr;
        this->currentHarbor = other.currentHarbor;
        other.currentHarbor = nullptr;
        if (this->cargo != nullptr)
            delete[] this->cargo;
        this->cargo = other.cargo;
        other.cargo = nullptr;
    }
    return *this;
};

//Ship& Ship::operator=(const Ship& other) {
//    if(this != &other) {
//        this->name = other.name;
//        this->price = other.price;
//        this->cargoSpace = other.cargoSpace;
//        this->cannonCapacity = other.cannonCapacity;
//        this->health = other.health;
//        this->destinationDistance = other.destinationDistance;
//        this->weight = other.weight;
//        this->size = other.size;
//        this->cargoSize = other.cargoSize;
//
//        // heap
//        //if (this->cargo != nullptr)
//            delete[] this->cargo;
//        this->cargo = new Good[other.cargoSize];
//        std::memcpy(this->cargo, other.cargo, other.cargoSize);
//    }
//    return *this;
//}

Ship::~Ship() {
    if (this->cargo != nullptr)
        delete[] this->cargo;
};

ShipWeight Ship::getShipWeight() const {
    return this->weight;
};
ShipSize Ship::getShipSize() const {
    return this->size;
};
void Ship::applyDamage(int damage) {
    this->health -= damage;
};
void Ship::repair(int amount) {
    if (this->health + amount >= this->maxHealth)
        this->health = maxHealth;
    else
        this->health += amount;
};

bool Ship::isSunken() const {
    return this->health <= 0;
};

bool Ship::isDocked() const {
    return this->currentHarbor != nullptr;
};

void Ship::sail(int distance) {
    this->destinationDistance -= distance;
};

void Ship::dock() {
    this->destinationDistance = 0;
    this->currentHarbor = this->destination;
}

Harbor* const Ship::getCurrentHarbor() const {
    return this->currentHarbor;
}

Harbor* const Ship::getDestination() const {
    return this->destination;
}

int Ship::getDestinationDistance() const {
    return this->destinationDistance;
}

void Ship::setDestination(Harbor* destination) {
    this->destination = destination;
}
void Ship::setCurrentHarbor(Harbor* harbor) {
    this->currentHarbor = harbor;
}

void Ship::setDestinationDistance(int destinationDistance) {
    this->destinationDistance = destinationDistance;
}

Good* const Ship::getCargo() const {
    return this->cargo;
}
int Ship::getCargoSize() const {
    return this->cargoSize;
}

int Ship::getHealth() const {
    return this->health;
}

