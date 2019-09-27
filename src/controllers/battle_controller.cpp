#include "controllers/battle_controller.hpp"
#include "models/ship.hpp"
#include "view_controllers/cli_view_controller.hpp"
#include "std/random.hpp"

BattleController::BattleController(World& w, CliViewController& cliViewController) : world(w), cliViewController(cliViewController) {
}

void BattleController::battle(Ship* s) {
    cliViewController.writeOutput(String("You have encountered a pirate ship."));
    Ship pirateShip = spawnPirateShip();

};

Ship BattleController::spawnPirateShip() {
    Random& random = Random::getInstance();
    int health = random.getRandomInt(1, 300);
    int cannons = random.getRandomInt(0, 25);
    int cargoSpace = random.getRandomInt(25, 200);
    int shipWeight = random.getRandomInt(0, 2);
    int shipSize = random.getRandomInt(0,1);

    Ship ship(String("PirateShip"), 0, health, 250, 25, ShipWeight(shipWeight), ShipSize(shipSize));

    for(int i = 0; i < cannons; i++) {
        int cannonType = random.getRandomInt(0,2);
        Cannon cannon = Cannon(CannonType(cannonType));
        //ship.addCannon(cannon);
    }
    return std::move(ship);
}