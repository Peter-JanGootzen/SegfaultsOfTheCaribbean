#include "controllers/harbor_controller.hpp"
#include "view_controllers/cli_view_controller.hpp"
#include "std/string.hpp"
#include <sstream>

HarborController::HarborController(World& w, CliViewController& cliViewController) : world(w), cliViewController(cliViewController) {
}

void HarborController::dockShip() {
    world.getPlayer().getShip()->dock();

    for (size_t i = 0; i < world.getHarbors().getSize(); i++) {
        Harbor* h = world.getHarbors()[i];
        for (size_t o = 0; o < h->getGoodsForSale().getSize(); o++) {
            h->getGoodsForSale()[o]->randomizeAmount();
            h->getGoodsForSale()[o]->randomizePrice();
            h->randomizeCannonStock();
        }
    }
}

void HarborController::tradeCannons() {
    Player& p = world.getPlayer();
    Ship* s = p.getShip();
    Harbor* h = s->getCurrentHarbor();

    int shipLightCannons = s->getCannons().count_filter([] (Cannon* c) -> bool {
        return c->getCannonType() == CannonType::Light;
    });
    int shipMediumCannons = s->getCannons().count_filter([] (Cannon* c) -> bool {
        return c->getCannonType() == CannonType::Medium;
    });;
    int shipHeavyCannons = s->getCannons().count_filter([] (Cannon* c) -> bool {
        return c->getCannonType() == CannonType::Heavy;
    });
    cliViewController.writeOutput(String("YOUR SHIPS CANNONS"));
    cliViewController.writeOutput(String("Light cannons: ") << shipLightCannons << " , worth 25 gold each");
    cliViewController.writeOutput(String("Medium cannons: ") << shipMediumCannons << " , worth 100 gold each");
    cliViewController.writeOutput(String("Heavy cannons: ") << shipHeavyCannons << " , worth 500 gold each");
    cliViewController.writeOutput(String("HARBOR STOCK"));
    cliViewController.writeOutput(String("Light cannons: ") << h->getLightCannonStock() << " in stock, for 50 gold each");
    cliViewController.writeOutput(String("Medium cannons: ") << h->getMediumCannonStock() << " in stock, for 200 gold each");
    cliViewController.writeOutput(String("Heavy cannons: ") << h->getHeavyCannonStock() << " in stock, for 1000 gold each");

    bool input_failed = false;
    do {
        if (input_failed == true) {
            cliViewController.writeOutput(String("The given input was incorrect!"));
            input_failed = false;
        }

        try {
            cliViewController.writeOutput(String("Would you like to sell or buy?"));
            const String input = cliViewController.getInput();
            if (input == String("buy")) {
                cliViewController.writeOutput(String("Your options are: light, medium, heavy"));
                const String input = cliViewController.getInput();
                if (input == String("light")) {
                    if (h->getLightCannonStock() > 0 && p.getMoney() > 25) {
                        p.payMoney(50);
                        s->getCannons().append(new Cannon(CannonType::Light));
                        h->setLightCannonStock(h->getLightCannonStock() - 1);
                    } else
                        cliViewController.writeOutput(String("Couldn't buy the cannons"));
                }
                else if (input == String("medium")) {
                    if (h->getMediumCannonStock() > 0 && p.getMoney() > 100) {
                        p.payMoney(200);
                        s->getCannons().append(new Cannon(CannonType::Medium));
                        h->setMediumCannonStock(h->getMediumCannonStock() - 1);
                    } else
                        cliViewController.writeOutput(String("Couldn't buy the cannons"));
                }
                else if (input == String("heavy")) {
                    if (h->getHeavyCannonStock() > 0 && p.getMoney() > 500) {
                        p.payMoney(1000);
                        s->getCannons().append(new Cannon(CannonType::Heavy));
                        h->setHeavyCannonStock(h->getHeavyCannonStock() - 1);
                    } else
                        cliViewController.writeOutput(String("Couldn't buy the cannons"));
                } else {
                    input_failed = true;
                }
            } else if (input == String("sell")) {
                cliViewController.writeOutput(String("Your options are: light, medium, heavy"));
                const String input = cliViewController.getInput();
                if (input == String("light")) {
                    if (shipLightCannons > 0) {
                        p.receiveMoney(25);
                        auto removed = s->getCannons().remove_filter([](Cannon* c) -> bool {
                            return c->getCannonType() == CannonType::Light;
                        });
                        if (removed)
                            delete removed;
                    } else
                        cliViewController.writeOutput(String("Couldn't sell the cannons"));
                }
                else if (input == String("medium")) {
                    if (shipMediumCannons > 0) {
                        p.receiveMoney(100);
                        auto removed = s->getCannons().remove_filter([](Cannon* c) -> bool {
                            return c->getCannonType() == CannonType::Medium;
                        });
                        if (removed)
                            delete removed;
                    } else
                        cliViewController.writeOutput(String("Couldn't sell the cannons"));
                }
                else if (input == String("heavy")) {
                    if (shipHeavyCannons > 0) {
                        p.receiveMoney(500);
                        auto removed = s->getCannons().remove_filter([](Cannon* c) -> bool {
                            return c->getCannonType() == CannonType::Heavy;
                        });
                        if (removed)
                            delete removed;
                    } else
                        cliViewController.writeOutput(String("Couldn't sell the cannons"));
                } else {
                    input_failed = true;
                }
            } else {
                input_failed = true;
            }
        } catch(const std::invalid_argument&) {  
            input_failed = true;
        }
    } while(input_failed == true);
}

void HarborController::tradeGoods() {
    Player& p = world.getPlayer();
    Ship* s = p.getShip();
    Harbor* h = s->getCurrentHarbor();

    for (size_t i = 0; i < h->getGoodsForSale().getSize(); i++) {
        const Good* g = h->getGoodsForSale().get(i);
        cliViewController.writeOutput(g->getName() << ": " << g->getAmount() << "x, for: " << g->getPrice() << " each");
    }

    bool input_failed = false;
    do {
        if (input_failed == true) {
            cliViewController.writeOutput(String("The given input was incorrect!"));
            input_failed = false;
        }

        try {
            cliViewController.writeOutput(String("Would you like to sell or buy?"));
            const String input = cliViewController.getInput();
            if (input == String("buy")) {
                cliViewController.writeOutput(String("Enter the name of the good you want to purchase"));
                const String input = cliViewController.getInput();
                Good* toBuyGood = h->getGoodsForSale().get_filter([input](Good* g) -> bool {
                    return g->getName() == input;
                });
                if (toBuyGood == nullptr) {
                    input_failed = true;
                } else {
                    cliViewController.writeOutput(String("Enter the amount you would like to purchase"));
                    try {
                        const int amountToBuy = std::stoi(cliViewController.getInput().c_str());
                        int moneyToSpend = amountToBuy * toBuyGood->getPrice();
                        if(amountToBuy > 0 && amountToBuy <= toBuyGood->getAmount()) {
                            if (p.getMoney() - moneyToSpend > 0) {
                                Good* cargoGood = s->getCargo().get_filter([toBuyGood](Good* g) -> bool {
                                    return g->getName() == toBuyGood->getName();
                                });
                                if (cargoGood == nullptr) {
                                    s->getCargo().append(new Good(toBuyGood->getName(), amountToBuy));
                                } else {
                                    cargoGood->setAmount(cargoGood->getAmount() + amountToBuy);
                                }
                                p.payMoney(moneyToSpend);
                                toBuyGood->setAmount(toBuyGood->getAmount() - amountToBuy);
                            } else {
                                cliViewController.writeOutput(String("Couldn't buy the goods"));
                            }
                        } else {
                            input_failed = true;
                        }
                    }
                    catch(const std::invalid_argument&) {
                        input_failed = true;
                    }
                }
            } else if (input == String("sell")) {
                cliViewController.writeOutput(String("Enter the name of the good you want to sell"));
                const String input = cliViewController.getInput();
                Good* toSellGood = s->getCargo().get_filter([input](Good* g) -> bool {
                    return g->getName() == input;
                });
                Good* toSellGoodHarbor = h->getGoodsForSale().get_filter([input](Good* g) -> bool {
                    return g->getName() == input;
                });
                if (toSellGood == nullptr) {
                    cliViewController.writeOutput(String("You do not own this good"));
                    input_failed = true;
                } else {
                    if (toSellGoodHarbor == nullptr) {
                        cliViewController.writeOutput(String("The harbor does not sell this good"));
                        input_failed = true;
                    }
                    cliViewController.writeOutput(String("Enter the amount you would like to sell"));
                    try {
                        const int amountToSell = std::stoi(cliViewController.getInput().c_str());
                        int moneyToReceive = amountToSell * (toSellGoodHarbor->getPrice() / 2);
                        if(amountToSell > 0 && amountToSell <= toSellGood->getAmount()) {
                            p.receiveMoney(moneyToReceive);
                            toSellGoodHarbor->setAmount(toSellGoodHarbor->getAmount() + amountToSell);
                            toSellGood->setAmount(toSellGood->getAmount() - amountToSell);
                            if (toSellGood->getAmount() <= 0)
                                s->getCargo().remove(toSellGood);
                        } else {
                            input_failed = true;
                        }
                    }
                    catch(const std::invalid_argument&) {
                        input_failed = true;
                    }
                }
            } else {
                input_failed = true;
            }
        } catch(const std::invalid_argument&) {  
            input_failed = true;
        }
    } while(input_failed == true);
}

void HarborController::buyShip() {
    Player& player = world.getPlayer();
    Ship* ship = player.getShip();
    Harbor* harbor = ship->getCurrentHarbor();

    cliViewController.writeOutput(String("These ships are for sale:"));
    for(size_t i = 0; i < harbor->getShipsForSale().getSize(); i++) {
        cliViewController.writeOutput(String() << i << ": " << harbor->getShipsForSale().get(i)->getName());
    }

    try {
        const size_t input = std::stoi(cliViewController.getInput().c_str());
        if(0 && input < harbor->getShipsForSale().getSize()) {
            auto shipToBuy = harbor->getShipsForSale().get(input);
            if (player.getMoney() - shipToBuy->getPrice() + (player.getShip()->getPrice() / 2) < 0) {
                cliViewController.writeOutput(String("You do not have enough money to buy this ship"));
                return;
            }
            if (ship->getCargoAmount() > shipToBuy->getCargoSpace()) {
                cliViewController.writeOutput(String("You cannot buy this ship, because you currently have more cargo than this ship can hold."));
                return;
            }
            if (ship->getCannons().getSize() > shipToBuy->getCannonCapacity()) {
                cliViewController.writeOutput(String("You cannot buy this ship, because you currently have more cannons than this ship can hold."));
                return;
            }

            auto boughtShip = harbor->getShipsForSale().remove_index(input);
            Ship* oldShip = player.setShip(boughtShip);
            oldShip->setDestination(nullptr);
            oldShip->setCurrentHarbor(nullptr);
            oldShip->setHealth(oldShip->getMaxHealth());
            for (size_t i = 0; i < oldShip->getCargo().getSize(); i++) {
                boughtShip->getCargo().append(oldShip->getCargo().remove_index(i));
            }
            for (size_t i = 0; i < oldShip->getCannons().getSize(); i++) {
                boughtShip->getCannons().append(oldShip->getCannons().remove_index(i));
            }
            player.payMoney(boughtShip->getPrice());
            player.receiveMoney(oldShip->getPrice() / 2);
            boughtShip->setCurrentHarbor(harbor);
            harbor->getShipsForSale().append(oldShip);
            cliViewController.writeOutput(String("You bought: ") << boughtShip->getName());
        } else {
            return;
        }
    }
    catch(const std::invalid_argument&) {
        cliViewController.writeOutput(String("The given input was incorrect!"));
        return;
    }
}

void HarborController::repairShip() {
    if (world.getPlayer().getShip()->getHealth() == world.getPlayer().getShip()->getMaxHealth()) {
        cliViewController.writeOutput(String("No need in repairing, your ship has full health"));
        return;
    }
    if (world.getPlayer().getMoney() - 1 < 0) {
        cliViewController.writeOutput(String("You do not have enough money!"));
        return;
    }

    world.getPlayer().getShip()->repair(10);
    world.getPlayer().payMoney(1);
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
        for(size_t i = 0; i < world.getHarborDistances().getSize(); i++) {
            if (world.getHarborDistances()[i]->getFrom() == world.getPlayer().getShip()->getCurrentHarbor())
                cliViewController.writeOutput(String() << i << ": " << world.getHarborDistances()[i]->getTo()->getName());
        }

        try {
            const size_t input = std::stoi(cliViewController.getInput().c_str());
            if(input < world.getHarborDistances().getSize() && world.getHarborDistances()[input]->getFrom() == ship->getCurrentHarbor()) {
                ship->setDestinationDistance(world.getHarborDistances()[input]->getDistance());
                ship->setDestination(world.getHarborDistances()[input]->getTo());
                ship->setCurrentHarbor(nullptr);
                cliViewController.writeOutput(String("Destination set to: ") << world.getHarborDistances()[input]->getTo()->getName());
            }
        }
        catch(const std::invalid_argument&) {
            input_failed = true;
        }
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
        cliViewController.writeOutput(String("Your currently own: ") << player->getShip()->getName() << " as your ship");
        cliViewController.writeOutput(String("Your ship has: ") << player->getShip()->getHealth() << " health");
        cliViewController.writeOutput(String("Inventory:"));

        for(size_t i = 0; i < ship->getCargo().getSize(); i++) {
            const auto g = ship->getCargo()[i];
            cliViewController.writeOutput(g->getName() << ": " << g->getAmount() << "x");
        }

        cliViewController.writeOutput(String("Your options are:"));
        cliViewController.writeOutput(String("trade_cannons, trade_goods, buy_ship, set_sail, repair, quit"));
        const String input = cliViewController.getInput();
        if (input == String("trade_cannons")) {
            tradeCannons();
        } else if (input == String("trade_goods")) {
            tradeGoods();
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
}
