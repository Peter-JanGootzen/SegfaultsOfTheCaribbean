#include "controllers/harbor_controller.hpp"
#include "view_controllers/cli_view_controller.hpp"
#include "std/string.hpp"
#include <sstream>

HarborController::HarborController(World& w, CliViewController& cliViewController) : world(w), cliViewController(cliViewController) {
}

void HarborController::dockShip() {
    world.getPlayer().getShip()->dock();

    for (int i = 0; i < world.getHarbors().getUsed(); i++) {
        const Harbor* h = world.getHarbors()[i];
        for (int o = 0; o < h->getGoodsForSale().getUsed(); o++) {
            h->getGoodsForSale()[i]->randomizeAmount();
            h->getGoodsForSale()[i]->randomizePrice();
        }
    }
}

void HarborController::repairShip() {
    if (world.getPlayer().getMoney() - 1 > 0) {
        world.getPlayer().getShip()->repair(10);
        world.getPlayer().payMoney(1);
    } else
    {
        cliViewController.writeOutput(String("You do not have enough money!"));
    }
}

void HarborController::setSail() {
    const Player& player = world.getPlayer();
    Ship* ship = player.getShip();
    bool input_failed = false;
    do {
        if (input_failed == true) {
            cliViewController.writeOutput(String("The given input was incorrect!"));
            input_failed = false;
        }

        cliViewController.writeOutput(String("You are currently in: ") << world.getPlayer().getShip()->getCurrentHarbor()->getName());

        cliViewController.writeOutput(String("These are your sailing options:"));
        for(int i = 0; i < world.getHarborDistances().getUsed(); i++) {
            if (world.getHarborDistances()[i]->from == world.getPlayer().getShip()->getCurrentHarbor())
                cliViewController.writeOutput(String() << i << ": " << world.getHarborDistances()[i]->to->getName());
        }

        try {
            const int input = std::stoi(cliViewController.getInput().c_str());
            if(input >= 0 && input < world.getHarborDistances().getUsed() && world.getHarborDistances()[input]->from == ship->getCurrentHarbor()) {
                ship->setDestinationDistance(world.getHarborDistances()[input]->distance);
                ship->setDestination(world.getHarborDistances()[input]->to);
                ship->setCurrentHarbor(nullptr);
                cliViewController.writeOutput(String("Destination set to: ") << world.getHarborDistances()[input]->to->getName());
            }
        }
        catch(std::invalid_argument) {
            input_failed = true;
        };
    } while(input_failed == true);
}

bool HarborController::presentOptions() {
    const Player* player = &world.getPlayer();
    const Ship* ship = player->getShip();
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

        for(int i = 0; i < ship->getCargo().getUsed(); i++) {
            const auto g = ship->getCargo()[i];
            cliViewController.writeOutput(g->getName() << ": " << g->getAmount() << "x");
        }

        cliViewController.writeOutput(String("Your options are:"));
        cliViewController.writeOutput(String("buy_cannons, sell_cannons, buy_goods, sell_goods, buy_ship, sell_ship, set_sail, repair, quit"));
        const String input = cliViewController.getInput();
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
