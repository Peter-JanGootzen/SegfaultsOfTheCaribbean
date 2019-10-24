#ifndef FILE_SHIP_HPP
#define FILE_SHIP_HPP
#include "models/enums/ship_size.hpp"
#include "models/enums/ship_weight.hpp"
#include "models/good.hpp"
#include "models/harbor.hpp"
#include "models/cannon.hpp"
#include "std/string.hpp"
#include "std/vector.hpp"
#include "std/unique_ptr.hpp"

class Harbor;

class Ship {
public:
    Ship(String name, int price, int maxHealth, int cargoSpace,
        int cannonCapacity, ShipWeight weight, ShipSize size);
    Ship(Ship&& other) = delete;
    Ship(const Ship& other) = delete;
    Ship& operator=(Ship&& other) = delete;
    Ship& operator=(const Ship& other) = delete;
    ~Ship() = default;

    // Getters
    String getName() const noexcept;
    int getHealth() const noexcept;
    int getMaxHealth() const noexcept;
    int getPrice() const noexcept;
    size_t getCargoSpace() const noexcept;
    size_t getCannonCapacity() const noexcept;
    int getDestinationDistance() const noexcept;
    Vector<Cannon*>& getCannons() const;
    ShipWeight getShipWeight() const noexcept;
    ShipSize getShipSize() const noexcept;
    Harbor* getCurrentHarbor() const noexcept;
    Harbor* getDestination() const noexcept;
    Vector<Good*>& getCargo() const;
    size_t getCargoAmount() const;
    bool isSunken() const noexcept;
    bool isDocked() const noexcept;
    // Setters
    void setHealth(int health) noexcept;
    void setDestinationDistance(int destinationDistance) noexcept;
    void setCurrentHarbor(Harbor* harbor) noexcept;
    void setDestination(Harbor* harbor) noexcept;
    void setShipWeight(ShipWeight weight) noexcept;
    void setShipSize(ShipSize size) noexcept;
    // Other
    void addCannon(Cannon* cannon);
    void applyDamage(int damage) noexcept;
    void sail(int distance) noexcept;
    void dock() noexcept;
    void repair(int amount) noexcept;
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
    unique_ptr<Vector<Good*>> cargo;
    unique_ptr<Vector<Cannon*>> cannons;
    // Not the owner!
    Harbor* currentHarbor;
};

#endif