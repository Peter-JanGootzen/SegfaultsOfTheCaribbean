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
    this->cargo = new Vector<Good*>(true);
    this->cannons = new Vector<Cannon*>(true);
    this->currentHarbor = nullptr;
    this->health = maxHealth;
};

Ship::Ship() {
    this->cargo = new Vector<Good*>(true);
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

    // heap
    this->destination = other.destination;
    other.destination = nullptr;
    this->currentHarbor = other.currentHarbor;
    other.currentHarbor = nullptr;
    this->cargo = other.cargo;
    other.cargo = nullptr;
    this->cannons = other.cannons;
    other.cannons = nullptr;
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

        // heap
        this->destination = other.destination;
        other.destination = nullptr;
        this->currentHarbor = other.currentHarbor;
        other.currentHarbor = nullptr;
        if (this->cargo != nullptr)
            delete this->cargo;
        this->cargo = other.cargo;
        other.cargo = nullptr;
        if (this->cannons != nullptr)
            delete this->cannons;
        this->cannons = other.cannons;
        other.cannons = nullptr;
    }
    return *this;
};

Ship::~Ship() {
    if (this->cargo != nullptr)
        delete this->cargo;
    if (this->cannons != nullptr)
        delete this->cannons;
};

ShipWeight Ship::getShipWeight() const {
    return this->weight;
};
ShipSize Ship::getShipSize() const {
    return this->size;
};
Vector<Cannon*>& Ship::getCannons() const {
    return *this->cannons;
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

void Ship::addCannon(Cannon* cannon) {
    this->cannons->append(cannon);
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

String Ship::getName() const {
    return this->name;
}

Harbor* Ship::getCurrentHarbor() const {
    return this->currentHarbor;
}

Harbor* Ship::getDestination() const {
    return this->destination;
}

Vector<Good*>& Ship::getCargo() const {
    return *this->cargo;
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

void Ship::setHealth(int health) {
    if (this->health + health > this->maxHealth)
        this->health = maxHealth;
    this->health += health;
}

size_t Ship::getCargoAmount() const {
    size_t total = 0;
    for (size_t i = 0; i < cargo->getSize(); i++) {
        total += cargo->get(i)->getAmount();
    }
    return total;
}

int Ship::getHealth() const {
    return this->health;
}

int Ship::getMaxHealth() const {
    return this->maxHealth;
}

size_t Ship::getCargoSpace() const {
    return this->cargoSpace;
}

int Ship::getPrice() const {
    return this->price;
}

