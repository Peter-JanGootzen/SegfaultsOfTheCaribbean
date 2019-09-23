#ifndef FILE_SHIP_HPP
#define FILE_SHIP_HPP
#include "models/enums/ship_weight.hpp"
#include "models/enums/ship_size.hpp"
#include "models/good.hpp"
#include "std/string.hpp"

class Ship
{
public:
    Ship() = default;
    Ship(String name, int price, int health, int cargoSpace,
        int cannonCapacity, ShipWeight weight, ShipSize size);
    Ship(Ship&& other);
    Ship(const Ship& other);
    Ship &operator=(Ship&& other);
    Ship &operator=(const Ship& other);
    ~Ship();

    // Getters
    String getName() const;
    int getHealth() const;
    int getPrice() const;
    int getCargoSpace() const;
    int getCannonCapacity() const;
    int getDestinationDistance() const;
    ShipWeight getShipWeight() const;
    ShipSize getShipSize() const;
    bool isSunken() const;
    // Setters
    void setName(String name);
    void setHealth(int health);
    void setPrice(int price);
    void setCargoSpace(int cargoSpace);
    void setCannonCapacity(int cannonCapacity);
    void setDestinationDistance(int destinationDistance);
    void setShipWeight(ShipWeight weight);
    void setShipSize(ShipSize size);
    // Other
    void applyDamage(int damage);
private:
    String name;
    int price;
    int cargoSpace;
    int cannonCapacity;
    int health;
    int destinationDistance;
    ShipWeight weight;
    ShipSize size;
    Good* cargo;
    unsigned int cargoSize;
};

#endif