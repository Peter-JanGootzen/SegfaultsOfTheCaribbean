#include <cstring>
#include "models/ship.hpp"
#include "std/string.hpp"

Ship::Ship(String name, int price, int health, int cargoSpace,
           int cannonCapacity, ShipWeight weight, ShipSize size) : 
           name(name), price(price), health(health), 
           cargoSpace(cargoSpace), cannonCapacity(cannonCapacity),
           weight(weight), size(size) {

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
    this->cargo = other.cargo;
    this->cargoSize = other.size;

    // heap
    other.cargo = nullptr;
};

Ship::Ship(const Ship& other) {
    this->name = other.name;
    this->price = other.price;
    this->cargoSpace = other.cargoSpace;
    this->cannonCapacity = other.cannonCapacity;
    this->health = other.health;
    this->destinationDistance = other.destinationDistance;
    this->weight = other.weight;
    this->size = other.size;
    this->cargo = new Good[other.size];
    this->cargoSize = other.size;

    // heap
    std::memcpy(this->cargo, other.cargo, other.size);
};

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
        this->cargoSize = other.size;

        // heap
        delete[] this->cargo;
        this->cargo = other.cargo;
        other.cargo = nullptr;
    }
    return *this;
}

Ship& Ship::operator=(const Ship& other) {
    if(this != &other) {
        this->name = other.name;
        this->price = other.price;
        this->cargoSpace = other.cargoSpace;
        this->cannonCapacity = other.cannonCapacity;
        this->health = other.health;
        this->destinationDistance = other.destinationDistance;
        this->weight = other.weight;
        this->size = other.size;
        this->cargoSize = other.size;

        // heap
        delete[] this->cargo;
        this->cargo = new Good[other.size];
        std::memcpy(this->cargo, other.cargo, other.size);
    }
}

Ship::~Ship() {
    delete[] this->cargo;
}
