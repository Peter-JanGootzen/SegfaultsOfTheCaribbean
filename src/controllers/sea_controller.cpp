#include <stdexcept>	
#include "controllers/sea_controller.hpp"
#include "std/random.hpp"

SeaController::SeaController() {
}

void SeaController::sail(Ship& s) {
    //Sea changes
    int seaRandom = Random::getInstance().getRandomInt(0, 20);
    switch (seaRandom)
    {
        case 1 ... 2:
            // No wind so you cannot move.
            break;
        case 3 ... 4:
            // Slight wind, move one step closer if the ship is light.
            if(s.getShipWeight() == ShipWeight::Light) {
                s.sail(1);
            }
            break;
        case 5 ... 7: 
            // If your ship is heavy, you cannot move.
            if(s.getShipWeight() != ShipWeight::Heavy) {
                s.sail(1);
            }
            break;
        case 8 ... 17: 
            // Normal wind, move one step closer
            s.sail(1);
            break;
        case 18 ... 19:
            // There is a lot of wind, move two steps closer.
            s.sail(2);
            break;
        case 20:
        {
            // STORM!!!
            // 40% Chance that the ship has gotten off course.
            // 40% Chance that the ship did not move.
            // 20% Chance that the ship moved in the right direction.
            // Because ship was stuck in the storm it is also damaged 1-100%.
            int storm = Random::getInstance().getRandomInt(0,100);
            switch (storm)
            {
                case 1 ... 40:
                    // Ship has gone off course.
                    s.sail(-1);
                    break;
                case 41 ... 80:
                    // Ship did not move.
                case 81 ... 100:
                    // Ship moved in the right direction.
                    s.sail(1);
                    break;
            }

            // Apply damage
            int damage = Random::getInstance().getRandomInt(1, 100);
            s.applyDamage(damage);
            break;
        }
        default:
            throw std::out_of_range("This shouldn't have happend...");
            break;
    }
}