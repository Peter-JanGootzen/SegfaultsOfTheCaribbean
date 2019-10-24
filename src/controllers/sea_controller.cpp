#include <stdexcept>	
#include <sstream>
#include "controllers/sea_controller.hpp"
#include "view_controllers/cli_view_controller.hpp"
#include "std/random.hpp"
#include "std/string.hpp"

SeaController::SeaController(World& w, CliViewController& cliViewController) : world(w), cliViewController(cliViewController), battleController(BattleController(w, cliViewController)) {
}

bool SeaController::sail() {
    Ship* s { world.getPlayer().getShip() };
    //Sea changes
    cliViewController.writeOutput(String("Destination is: ") << s->getDestination()->getName());
    cliViewController.writeOutput(String("Destination distance is: ") << s->getDestinationDistance());
    cliViewController.writeOutput(String("Your ship has ") << s->getHealth() << " health left.");
    cliViewController.writeOutput(String("You are at sea, press enter to continue."));
    cliViewController.getInput();
    const int battle { Random::getInstance().getRandomInt(1, 100) };
    if (battle >= 1 && battle <= 20) {
        battleController.battle(s);
    } else if (battle >= 21 && battle <= 100) {
        move();
        if(s->getDestinationDistance() <= 0) {
            cliViewController.writeOutput("You have arrived at your destination!");
            return true;
        }
    } else {
        throw std::out_of_range("This shouldn't have happend...");
    }
    return false;
}

void SeaController::move() {
    Ship* s { world.getPlayer().getShip() };
    const int seaRandom { Random::getInstance().getRandomInt(1, 20) };
    if (seaRandom >= 1 && seaRandom <= 2) {
        // No wind so you cannot move.
        cliViewController.writeOutput(String("Your ship did not move, there is no wind."));
    } else if (seaRandom >= 3 && seaRandom <= 4) {
        // Slight wind, move one step closer if the ship is light.
        if(s->getShipWeight() == ShipWeight::Light) {
            s->sail(1);
            cliViewController.writeOutput(String("Slight wind but your ship is light so your ship moved one step closer to destination!"));
        } else
            cliViewController.writeOutput(String("Slight wind which did not move your ship."));
    } else if (seaRandom >= 5 && seaRandom <= 7) {
        if(s->getShipWeight() == ShipWeight::Heavy) {
            // If your ship is heavy, you cannot move.
            cliViewController.writeOutput(String("Light wind but your ship is heavy so it does not move."));
        } else {
            cliViewController.writeOutput(String("Light wind, your ship moves one step closer to destination."));
            s->sail(1);
        }
    } else if (seaRandom >= 8 && seaRandom <= 17) {
        // Normal wind, move one step closer
        s->sail(1);
        cliViewController.writeOutput(String("Normal wind, your ship moves one step closer to destination."));
    } else if (seaRandom >= 18 && seaRandom <= 19) {
        // There is a lot of wind, move two steps closer.
        s->sail(2);
        cliViewController.writeOutput(String("A lot of wind moved your ship 2 steps closer!"));
    } else if (seaRandom == 20) {
        cliViewController.writeOutput(String("Your ship got caught in a storm"));
        // STORM!!!
        // 40% Chance that the ship has gotten off course.
        // 40% Chance that the ship did not move.
        // 20% Chance that the ship moved in the right direction.
        // Because ship was stuck in the storm it is also damaged 1-100%.
        const int storm { Random::getInstance().getRandomInt(1,100) };
        if (storm >= 1 && storm <= 40) {
            // Ship has gone off course.
            s->sail(-1);
            cliViewController.writeOutput(String("Your ship has gone off course!"));
        } else if (storm >= 41 && storm <= 80) {
            // Ship did not move.
            cliViewController.writeOutput(String("Your ship did not move."));
        } else if (storm >= 81 && storm <= 100) {
            // Ship moved in the right direction.
            s->sail(1);
            cliViewController.writeOutput(String("Your ship moved one step closer in the right direction!"));
        }

        // Apply damage
        const int damage { Random::getInstance().getRandomInt(1, 100) };
        s->applyDamage(damage);
        cliViewController.writeOutput(String("Your ship got ") << damage << " damage.");
    } else {
        throw std::out_of_range("This shouldn't have happend...");
    }
}