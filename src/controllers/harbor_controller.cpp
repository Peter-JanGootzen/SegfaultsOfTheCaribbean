#include "controllers/harbor_controller.hpp"
#include "view_controllers/cli_view_controller.hpp"
#include "std/string.hpp"
#include <sstream>

HarborController::HarborController(World& w, CliViewController& cliViewController) : world(w), cliViewController(cliViewController) {
}

void HarborController::dockShip() {
    world.getPlayer().getShip()->dock();

    for (int i = 0; i < world.getHarborsSize(); i++) {
        Harbor* h = &world.getHarbors()[i];
        for (int o = 0; o < h->getGoodsForSaleSize(); o++) {
            h->getGoodsForSale()[i].randomizeAmount();
            h->getGoodsForSale()[i].randomizePrice();
        }
    }
}

void HarborController::repairShip() {
    world.getPlayer().getShip()->repair(10);
    world.getPlayer().payMoney(1);
}

void HarborController::setSail() {
    Player& player = world.getPlayer();
    Ship* ship = player.getShip();
    bool input_failed = false;
    do {
        if (input_failed == true) {
            cliViewController.writeOutput(String("The given input was incorrect!"));
            input_failed = false;
        }

        cliViewController.writeOutput(String("You are currently in: ") << world.getPlayer().getShip()->getCurrentHarbor()->getName());

        cliViewController.writeOutput(String("These are your sailing options:"));
        for(int i = 0; i < world.getHarborDistancesSize(); i++) {
            if (world.getHarborDistances()[i].from == world.getPlayer().getShip()->getCurrentHarbor())
                cliViewController.writeOutput(String() << i << ": " << world.getHarborDistances()[i].to->getName());
        }

        try {
            int input = std::stoi(cliViewController.getInput().c_str());
            if(input >= 0 && input < world.getHarborDistancesSize() && world.getHarborDistances()[input].from == ship->getCurrentHarbor()) {
                ship->setDestinationDistance(world.getHarborDistances()[input].distance);
                ship->setDestination(world.getHarborDistances()[input].to);
                ship->setCurrentHarbor(nullptr);
                cliViewController.writeOutput(String("Destination set to: ") << world.getHarborDistances()[input].to->getName());
            }
        }
        catch(std::invalid_argument) {
            input_failed = true;
        };
    } while(input_failed == true);
}

bool HarborController::presentOptions() {
    Player* player = &world.getPlayer();
    Ship* ship = player->getShip();
    cliViewController.writeOutput(String() << "You are currently in: " << ship->getCurrentHarbor()->getName());

    bool input_failed = false;
    do {
        if (input_failed == true) {
            cliViewController.writeOutput(String("The given input was incorrect!"));
            input_failed = false;
        }

        cliViewController.writeOutput(String("You have: ") << player->getMoney() << " money");
        cliViewController.writeOutput(String("Your ship has: ") << player->getShip()->getHealth() << " health");
        cliViewController.writeOutput(String("Inventory:"));

        for(int i = 0; i < ship->getCargoSize(); i++) {
            auto g = ship->getCargo()[i];
            cliViewController.writeOutput(g.getName() << ": " << g.getAmount() << "x");
        }

        cliViewController.writeOutput(String("Your options are:"));
        cliViewController.writeOutput(String("buy_cannons, sell_cannons, buy_goods, sell_goods, buy_ship, sell_ship, set_sail, repair, quit"));
        String input = cliViewController.getInput();
        if (input == String("buy_cannons")) {
            //buyCannons();
        } else if (input == String("buy_goods")) {
            //buyGoods();
        } else if (input == String("buy_ship")) {
            //buyShip();
        } else if (input == String("set_sail")) {
            setSail();
        } else if (input == String("repair")) {
            repairShip();
        } else if (input == String("quit")) {
            return true;
        } else {
            input_failed = true;
        }
    } while(input_failed == true);
    return false;
}
