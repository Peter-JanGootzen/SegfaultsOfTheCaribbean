#include "controllers/harbor_controller.hpp"
#include "view_controllers/cli_view_controller.hpp"
#include "std/string.hpp"
#include <sstream>

HarborController::HarborController(World& w, CliViewController& cliViewController) : world(w), cliViewController(cliViewController) {
}

void HarborController::dockShip() {
    world.getPlayer().getShip()->dock();

    for (int i = 0; i < world.getHarbors().getSize(); i++) {
        Harbor* h = world.getHarbors()[i];
        for (int o = 0; o < h->getGoodsForSale().getSize(); o++) {
            h->getGoodsForSale()[i]->randomizeAmount();
            h->getGoodsForSale()[i]->randomizePrice();
            h->randomizeCannonStock();
        }
    }
};

void HarborController::tradeCannons() {
    Harbor* h = world.getPlayer().getShip()->getCurrentHarbor();
    bool input_failed = false;
    do {
        if (input_failed == true) {
            cliViewController.writeOutput(String("The given input was incorrect!"));
            input_failed = false;
        }
        //cliViewController.writeOutput(String("Light cannons: ") << h->getLightCannonStock() << " in stock, for 50 gold each");
        //cliViewController.writeOutput(String("Medium cannons: ") << h->getMediumCannonStock() << " in stock, for 200 gold each");
        //cliViewController.writeOutput(String("Heavy cannons: ") << h->getHeavyCannonStock() << " in stock, for 1000 gold each");

        try {
            const int input = std::stoi(cliViewController.getInput().c_str());
        }
        catch(std::invalid_argument) {
            input_failed = true;
        };
    } while(input_failed == true);
}

void HarborController::buyShip() {
    Player& player = world.getPlayer();
    Ship* ship = player.getShip();
    Harbor* harbor = ship->getCurrentHarbor();

    cliViewController.writeOutput(String("These ships are for sale:"));
    for(int i = 0; i < world.getHarborDistances().getSize(); i++) {
        cliViewController.writeOutput(String() << i << ": " << harbor->getShipsForSale().get(i)->getName());
    }

    bool input_failed = false;
    do {
        if (input_failed == true) {
            cliViewController.writeOutput(String("The given input was incorrect!"));
            input_failed = false;
        }

        try {
            const int input = std::stoi(cliViewController.getInput().c_str());
            if(input >= 0 && input < harbor->getShipsForSale().getSize()) {
                auto shipToBuy = harbor->getShipsForSale().get(input);
                if (player.getMoney() - shipToBuy->getPrice() + (player.getShip()->getPrice() / 2) < 0) {
                    cliViewController.writeOutput(String("You do not have enough money to buy this ship"));
                    return;
                }
                if (ship->getCargoAmount() > shipToBuy->getCargoSpace()) {
                    cliViewController.writeOutput(String("You cannot buy this ship, because you currently have more cargo than this ship can hold."));
                    return;
                }

                auto boughtShip = harbor->getShipsForSale().remove_index(input);
                Ship* oldShip = player.setShip(boughtShip);
                oldShip->setDestination(nullptr);
                oldShip->setCurrentHarbor(nullptr);
                oldShip->setHealth(oldShip->getMaxHealth());
                for (int i = 0; i < oldShip->getCargo().getSize(); i++) {
                    boughtShip->getCargo().append(oldShip->getCargo().remove_index(i));
                }
                player.payMoney(boughtShip->getPrice());
                player.receiveMoney(oldShip->getPrice() / 2);
                boughtShip->setCurrentHarbor(harbor);
                harbor->getShipsForSale().append(oldShip);
                cliViewController.writeOutput(String("You bought: ") << boughtShip->getName());
            } else {
                input_failed = true;
            }
        }
        catch(std::invalid_argument) {
            input_failed = true;
        };
    } while(input_failed == true);
}

void HarborController::repairShip() {
    if (world.getPlayer().getMoney() - 1 > 0) {
        world.getPlayer().getShip()->repair(10);
        world.getPlayer().payMoney(1);
    } else
    {
        cliViewController.writeOutput(String("You do not have enough money!"));
    }
};

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
        for(int i = 0; i < world.getHarborDistances().getSize(); i++) {
            if (world.getHarborDistances()[i]->from == world.getPlayer().getShip()->getCurrentHarbor())
                cliViewController.writeOutput(String() << i << ": " << world.getHarborDistances()[i]->to->getName());
        }

        try {
            const int input = std::stoi(cliViewController.getInput().c_str());
            if(input >= 0 && input < world.getHarborDistances().getSize() && world.getHarborDistances()[input]->from == ship->getCurrentHarbor()) {
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
};

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
        cliViewController.writeOutput(String("Your currently own: ") << player->getShip()->getName() << " as your ship");
        cliViewController.writeOutput(String("Your ship has: ") << player->getShip()->getHealth() << " health");
        cliViewController.writeOutput(String("Inventory:"));

        for(int i = 0; i < ship->getCargo().getSize(); i++) {
            const auto g = ship->getCargo()[i];
            cliViewController.writeOutput(g->getName() << ": " << g->getAmount() << "x");
        }

        cliViewController.writeOutput(String("Your options are:"));
        cliViewController.writeOutput(String("trade_cannons, sell_cannons, buy_goods, sell_goods, buy_ship, sell_ship, set_sail, repair, quit"));
        const String input = cliViewController.getInput();
        if (input == String("trade_cannons")) {
            tradeCannons();
        } else if (input == String("buy_goods")) {
            //buyGoods();
        } else if (input == String("buy_ship")) {
            buyShip();
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
};
