#include "controllers/battle_controller.hpp"
#include "models/ship.hpp"
#include "view_controllers/cli_view_controller.hpp"
#include "std/string.hpp"
#include "std/random.hpp"
#include "std/unique_ptr.hpp"

BattleController::BattleController(World& w, CliViewController& cliViewController) : world(w), cliViewController(cliViewController) {
}

void BattleController::battle(Ship* s) {
    cliViewController.writeOutput(String("You have encountered a pirate ship."));
    const auto pirateShip { spawnPirateShip() };
    bool fledOrSurrendered { false };
    bool input_failed { false };
    while (!pirateShip->isSunken() && !fledOrSurrendered && !s->isSunken()) {
        do {
            if (input_failed == true) {
                cliViewController.writeOutput(String("The given input was incorrect!"));
                input_failed = false;
            }
            cliViewController.writeOutput(String("Your ship has ") << s->getHealth() << " health left");
            cliViewController.writeOutput(String("The pirate ship has ") << pirateShip->getHealth() << " health left");
            cliViewController.writeOutput(String("These are your battling options:"));
            cliViewController.writeOutput(String("shoot, flee or surrender"));
            const String input { cliViewController.getInput() };
            if (input == String("shoot")) {
                shoot(*s, *pirateShip);
            } else if (input == String("flee")) {
                fledOrSurrendered = flee(*s, *pirateShip);
                // if you flee, you will still be shot at
            } else if (input == String("surrender")) {
                fledOrSurrendered = true;
                surrender(*s, *pirateShip); 
            } else {
                input_failed = true;
            }
        } while (input_failed);
    }
}

void BattleController::shoot(Ship& ship, Ship& pirateShip) {
    const int damage { calculateDamage(ship) };
    pirateShip.applyDamage(damage);
    cliViewController.writeOutput(String("Your ship did ") << damage << " damage");

    if(!pirateShip.isSunken()) {
        cliViewController.writeOutput(String("The pirate ship is still alive and shoots back!"));
        const int pirateDamage = calculateDamage(pirateShip);
        ship.applyDamage(pirateDamage);
        cliViewController.writeOutput(String("Your ship got ") << pirateDamage << " damage");
    }

    if(pirateShip.isSunken()) {
        cliViewController.writeOutput(String("You defeated the pirate ship!"));
    }
}

int BattleController::calculateDamage(Ship& ship) {
    Random& random  { Random::getInstance() };
    int damage { 0 };
    if(ship.getCannons().getSize() == 0) {
        cliViewController.writeOutput(String("This ") << ship.getName() << String("does not have any cannons!"));
    }
    for(size_t i = 0; i < ship.getCannons().getSize(); i++) {
        switch (ship.getCannons().get(i)->getCannonType())
        {
            case CannonType::Light:
                damage += random.getRandomInt(0,2);
                break;
            case CannonType::Medium: 
                damage += random.getRandomInt(0,4);
                break;
            case CannonType::Heavy:
                damage += random.getRandomInt(0,6);
                break;
            default:
                break;
        }
    }
    return damage;
}

bool BattleController::flee(Ship& s, Ship& pirateShip) {
    Random& random { Random::getInstance() };
    int fleeChance;
    switch (pirateShip.getShipWeight())
    {
        case ShipWeight::Light:
            switch (s.getShipWeight())
            {
                case ShipWeight::Light:
                    fleeChance = 50;
                    break;
                case ShipWeight::Normal:
                    fleeChance = 30;
                    break;
                case ShipWeight::Heavy:
                    fleeChance = 5;
            }
            break;
        case ShipWeight::Normal:
            switch (s.getShipWeight())
            {
                case ShipWeight::Light:
                    fleeChance = 60;
                    break;
                case ShipWeight::Normal:
                    fleeChance = 40;
                    break;
                case ShipWeight::Heavy:
                    fleeChance = 15;
            }
            break;
        case ShipWeight::Heavy:
            switch (s.getShipWeight())
            {
                case ShipWeight::Light:
                    fleeChance = 75;
                    break;
                case ShipWeight::Normal:
                    fleeChance = 55;
                    break;
                case ShipWeight::Heavy:
                    fleeChance = 30;
            }
            break;
    }

    const int chance { random.getRandomInt(1,100) };
    if(chance <= fleeChance) {
        cliViewController.writeOutput("You fled!");
        return true;
    }
    cliViewController.writeOutput("Fled attempt failed");
    cliViewController.writeOutput("The pirate ship shoots at you!");
    const int damage { calculateDamage(pirateShip) };
    s.applyDamage(damage);
    cliViewController.writeOutput(String("Your ship got ") << damage << " damage");
    return false;
}

void BattleController::surrender(Ship& s, Ship& pirateShip) {
    for (size_t i = 0; i < s.getCargo().getSize(); i++) {
        if(pirateShip.getCargo().getSize() >= pirateShip.getCargoSpace())
            pirateShip.getCargo().append(s.getCargo().remove_index(i));
        else
            unique_ptr<Good> c { s.getCargo().remove_index(i) };
    }
}

unique_ptr<Ship> BattleController::spawnPirateShip() {
    Random& random { Random::getInstance() };
    const int health { random.getRandomInt(1, 300) };
    const int cannons { random.getRandomInt(0, 15) };
    const int shipWeight { random.getRandomInt(0, 2) };
    const int shipSize { random.getRandomInt(0,1) };

    unique_ptr<Ship> ship { new Ship(String("PirateShip"), 0, health, 250, 25, ShipWeight(shipWeight), ShipSize(shipSize)) };

    for(int i = 0; i < cannons; i++) {
        int cannonType { random.getRandomInt(0,2) };
        Cannon* cannon { new Cannon(CannonType(cannonType)) };
        ship->addCannon(cannon);
    }
    return ship;
}