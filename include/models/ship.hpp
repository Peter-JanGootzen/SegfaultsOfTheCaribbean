#ifndef FILE_SHIP_HPP
#define FILE_SHIP_HPP
#include "models/enums/ship_weight.hpp"
#include "models/enums/ship_size.hpp"

class Ship
{
public:
    Ship();
    Ship(Ship &&) = default;
    Ship(const Ship &) = default;
    Ship &operator=(Ship &&) = default;
    Ship &operator=(const Ship &) = default;
    ~Ship();
private:
    int Money;
    int Price;
    int CargoSpace;
    int Health;
    int DestinationDistance;
    ShipWeight weight;
    ShipSize size;
};

Ship::Ship()
{
}

Ship::~Ship()
{
}
#endif