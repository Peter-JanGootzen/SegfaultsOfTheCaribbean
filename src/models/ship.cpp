#include <cstring>
#include "models/ship.hpp"
#include "std/string.hpp"

Ship::Ship(String name, int price, int health, int cargoSpace,
           int cannonCapacity, ShipWeight weight, ShipSize size) : 
           name(name), price(price), health(health), 
           cargoSpace(cargoSpace), cannonCapacity(cannonCapacity),
           weight(weight), size(size) {
    this->cargo = nullptr;
}

Ship::Ship() {
    this->cargo = nullptr;
}

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
        if (this->cargo != nullptr)
            delete[] this->cargo;
        this->cargo = other.cargo;
        other.cargo = nullptr;
    }
    return *this;
}

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
}

ShipWeight Ship::getShipWeight() const {
    return this->weight;
}
ShipSize Ship::getShipSize() const {
    return this->size;
}
void Ship::applyDamage(int damage) {
    this->health -= damage;
}

bool Ship::isSunken() const {
    return this->health <= 0;
}

void Ship::sail(int distance) {
    this->destinationDistance -= distance;
}
