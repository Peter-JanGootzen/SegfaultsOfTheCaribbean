#include "controllers/battle_controller.hpp"
#include "models/ship.hpp"
#include "view_controllers/cli_view_controller.hpp"
#include "std/string.hpp"
#include "std/random.hpp"

BattleController::BattleController(World& w, CliViewController& cliViewController) : world(w), cliViewController(cliViewController) {
}

void BattleController::battle(Ship* s) {
    cliViewController.writeOutput(String("You have encountered a pirate ship."));
    Ship* pirateShip = spawnPirateShip();
    bool fledOrSurrendered = false;
    while (!s->isSunken() && !fledOrSurrendered) {
        String input = presentOptions();
        if (input == String("shoot")) {
            shoot(s, pirateShip);
        } else if (input == String("flee")) {
            fledOrSurrendered = flee(s, pirateShip);
            // if you flee, you will still be shot at
            shoot(s, pirateShip);
        } else if (input == String("surrender")) {
            fledOrSurrendered = true;
            surrender(s, pirateShip); 
        }
    }
    delete pirateShip;
};

String BattleController::presentOptions()
{
    bool input_failed = false;
    do { 
        if (input_failed == true) {
            cliViewController.writeOutput(String("The given input was incorrect!"));
            input_failed = false;
        }
        cliViewController.writeOutput(String("These are your battling options:"));
        cliViewController.writeOutput(String("shoot, flee or surrender"));
        return cliViewController.getInput();
    } while(input_failed);
};

void BattleController::shoot(Ship* ship, Ship* pirateShip) {
    Random& random = Random::getInstance();
    for(int i = 0; i < pirateShip->getCannons().getSize(); i++) {
        switch (pirateShip->getCannons().get(i)->getCannonType())
        {
        case CannonType::Light:
            ship->applyDamage(random.getRandomInt(0,2));
            break;
        case CannonType::Medium: 
            ship->applyDamage(random.getRandomInt(0,4));
            break;
        case CannonType::Heavy:
            ship->applyDamage(random.getRandomInt(0,6));
            break;
        default:
            break;
        }
    }
};

bool BattleController::flee(Ship* s, Ship* pirateShip) {
    Random& random = Random::getInstance();
    int fleeChance;
    switch (pirateShip->getShipWeight())
    {
        case ShipWeight::Light:
            switch (s->getShipWeight())
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
            switch (s->getShipWeight())
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
            switch (s->getShipWeight())
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

    int chance = random.getRandomInt(1,100);
    if(chance <= fleeChance)
        return true;
    return false;
};

void BattleController::surrender(Ship* s, Ship* pirateShip) {
    for (int i = 0; i < s->getCargo().getSize(); i++) {
        if(pirateShip->getCargo().getSize() >= pirateShip->getCargoSpace())
            pirateShip->getCargo().append(s->getCargo().remove_index(i));
        else
            s->getCargo().remove_index(i);
    }
};

Ship* BattleController::spawnPirateShip() {
    Random& random = Random::getInstance();
    const int health = random.getRandomInt(1, 300);
    const int cannons = random.getRandomInt(0, 25);
    const int cargoSpace = random.getRandomInt(25, 200);
    const int shipWeight = random.getRandomInt(0, 2);
    const int shipSize = random.getRandomInt(0,1);

    Ship* ship = new Ship(String("PirateShip"), 0, health, 250, 25, ShipWeight(shipWeight), ShipSize(shipSize));

    for(int i = 0; i < cannons; i++) {
        int cannonType = random.getRandomInt(0,2);
        Cannon* cannon = new Cannon(CannonType(cannonType));
        ship->addCannon(cannon);
    }
    return ship;
};