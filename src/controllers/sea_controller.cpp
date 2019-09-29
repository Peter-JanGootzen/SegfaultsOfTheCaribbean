#include <stdexcept>	
#include <sstream>
#include "controllers/sea_controller.hpp"
#include "view_controllers/cli_view_controller.hpp"
#include "std/random.hpp"
#include "std/string.hpp"

SeaController::SeaController(World& w, CliViewController& cliViewController) : world(w), cliViewController(cliViewController), battleController(BattleController(w, cliViewController)) {
}

bool SeaController::sail() {
    const auto s = world.getPlayer().getShip();
    //Sea changes
    cliViewController.writeOutput(String("Destination is: ") << s->getDestination()->getName());
    cliViewController.writeOutput(String("Destination distance is: ") << s->getDestinationDistance());
    cliViewController.writeOutput(String("Your ship has ") << s->getHealth() << " health left.");
    cliViewController.writeOutput(String("You are at sea, press enter to continue."));
    cliViewController.getInput();
    const int battle = Random::getInstance().getRandomInt(1, 100);
    switch (battle)
    {
        case 1 ... 20:
            battleController.battle(s);
            break;
        case 21 ... 100:
            move();
            if(s->getDestinationDistance() <= 0) {
                cliViewController.writeOutput("You have arrived at your destination!");
                return true;
            }
            break;
        default:
            throw std::out_of_range("This shouldn't have happend...");
            break;
    }
    return false;
};

void SeaController::move() {
    auto s = world.getPlayer().getShip();
    const int seaRandom = Random::getInstance().getRandomInt(1, 20);
    switch (seaRandom)
    {
        case 1 ... 2:
            // No wind so you cannot move.
            cliViewController.writeOutput(String("Your ship did not move, there is no wind."));
            break;
        case 3 ... 4:
            // Slight wind, move one step closer if the ship is light.
            if(s->getShipWeight() == ShipWeight::Light) {
                s->sail(1);
                cliViewController.writeOutput(String("Slight wind but your ship is light so your ship moved one step closer to destination!"));
            } else
                cliViewController.writeOutput(String("Slight wind which did not move your ship."));
            break;
        case 5 ... 7: 
            if(s->getShipWeight() == ShipWeight::Heavy) {
                // If your ship is heavy, you cannot move.
                cliViewController.writeOutput(String("Light wind but your ship is heavy so it does not move."));
            } else {
                cliViewController.writeOutput(String("Light wind, your ship moves one step closer to destination."));
                s->sail(1);
            }
            break;
        case 8 ... 17: 
            // Normal wind, move one step closer
            s->sail(1);
            cliViewController.writeOutput(String("Normal wind, your ship moves one step closer to destination."));
            break;
        case 18 ... 19:
            // There is a lot of wind, move two steps closer.
            s->sail(2);
            cliViewController.writeOutput(String("A lot of wind moved your ship 2 steps closer!"));
            break;
        case 20:
        {
            cliViewController.writeOutput(String("Your ship got caught in a storm"));
            // STORM!!!
            // 40% Chance that the ship has gotten off course.
            // 40% Chance that the ship did not move.
            // 20% Chance that the ship moved in the right direction.
            // Because ship was stuck in the storm it is also damaged 1-100%.
            const int storm = Random::getInstance().getRandomInt(1,100);
            switch (storm)
            {
                case 1 ... 40:
                    // Ship has gone off course.
                    s->sail(-1);
                    cliViewController.writeOutput(String("Your ship has gone off course!"));
                    break;
                case 41 ... 80:
                    // Ship did not move.
                    cliViewController.writeOutput(String("Your ship did not move."));
                case 81 ... 100:
                    // Ship moved in the right direction.
                    s->sail(1);
                    cliViewController.writeOutput(String("Your ship moved one step closer in the right direction!"));
                    break;
            }

            // Apply damage
            const int damage = Random::getInstance().getRandomInt(1, 100);
            s->applyDamage(damage);
            cliViewController.writeOutput(String("Your ship got ") << damage << " damage.");
            break;
        }
        default:
            throw std::out_of_range("This shouldn't have happend...");
            break;
    }
}