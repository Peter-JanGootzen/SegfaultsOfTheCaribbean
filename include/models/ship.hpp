#ifndef FILE_SHIP_HPP
#define FILE_SHIP_HPP
#include "models/enums/ship_size.hpp"
#include "models/enums/ship_weight.hpp"
#include "models/good.hpp"
#include "models/harbor.hpp"
#include "models/cannon.hpp"
#include "std/string.hpp"
#include "std/vector.hpp"

class Harbor;

class Ship
{
public:
    Ship();
    Ship(String name, int price, int maxHealth, int cargoSpace,
        int cannonCapacity, ShipWeight weight, ShipSize size);
    Ship(Ship&& other);
    Ship(const Ship& other) = delete;
    Ship& operator=(Ship&& other);
    Ship& operator=(const Ship& other) = delete;
    ~Ship();

    // Getters
    String getName() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getPrice() const;
    size_t getCargoSpace() const;
    size_t getCannonCapacity() const;
    int getDestinationDistance() const;
    Vector<Cannon*>& getCannons() const;
    ShipWeight getShipWeight() const;
    ShipSize getShipSize() const;
    Harbor* getCurrentHarbor() const;
    Harbor* getDestination() const;
    Vector<Good*>& getCargo() const;
    size_t getCargoAmount() const;
    bool isSunken() const;
    bool isDocked() const;
    // Setters
    void setName(String name);
    void setHealth(int health);
    void setDestinationDistance(int destinationDistance);
    void setCurrentHarbor(Harbor* const harbor);
    void setDestination(Harbor* const destination);
    void setShipWeight(ShipWeight weight);
    void setShipSize(ShipSize size);
    // Other
    void addCannon(Cannon* cannon);
    void applyDamage(int damage);
    void sail(int distance);
    void dock();
    void repair(int amount);
private:
    String name;
    int price;
    size_t cargoSpace;
    size_t cannonCapacity;
    int maxHealth;
    int health;
    int destinationDistance;
    // Not the owner!
    Harbor* destination;
    ShipWeight weight;
    ShipSize size;
    Vector<Good*>* cargo;
    Vector<Cannon*>* cannons;
    // Not the owner!
    Harbor* currentHarbor;
};

#endif