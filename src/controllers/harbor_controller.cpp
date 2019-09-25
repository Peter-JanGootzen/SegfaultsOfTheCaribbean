#include "controllers/harbor_controller.hpp"
#include "view_controllers/cli_view_controller.hpp"
#include "std/string.hpp"
#include <sstream>

HarborController::HarborController(World& w, CliViewController& cliViewController) : world(w), cliViewController(cliViewController) {
}

void HarborController::quitGame() {
    this->cliViewController.writeOutput(String("Segmentation Fault (core dumped)"));
    this->cliViewController.writeOutput(String("Gnome im kdeing, you quit the game..."));
    exit(0);
}

void HarborController::setSail() {

    bool input_failed = false;
    do {
        if (input_failed == true)
            this->cliViewController.writeOutput(String("The given input was incorrect!"));

        std::ostringstream o;
        o << "You are currently in: " << world.getPlayer().getShip()->getCurrentHarbor()->getName();
        cliViewController.writeOutput(String(o.str().c_str()));

        this->cliViewController.writeOutput(String("These are your sailing options:"));
        for(int i = 0; i < this->world.getHarborDistancesSize(); i++) {
            if (this->world.getHarborDistances()[i].from == this->world.getPlayer().getShip()->getCurrentHarbor() ||
                this->world.getHarborDistances()[i].to == this->world.getPlayer().getShip()->getCurrentHarbor()) {
                std::ostringstream o;
                o << i << ": " << this->world.getHarborDistances()[i].from->getName();
                cliViewController.writeOutput(String(o.str().c_str()));
            }
        }

        int input;
        try {
            input = std::stoi(this->cliViewController.getInput().c_str());
            if(input > 0 && input < this->world.getHarborDistancesSize())
                std::ostringstream o;
                o << "Destination set to: " << this->world.getHarborDistances()[input].distance;
                cliViewController.writeOutput(String(o.str().c_str()));
        }
        catch(std::invalid_argument) {
            input_failed = false;
        };
    } while(input_failed == true);
}

void HarborController::presentOptions() {
    /*
    bool input_failed = false;
    do {
        if (input_failed == true)
            this->cliViewController.writeOutput(String("The given input was incorrect!"));

        this->cliViewController.writeOutput(String("You are currently in a harbor, your options are:"));
        this->cliViewController.writeOutput(String("buy_cannons, buy_goods, buy_ship, set_sail, repair, quit"));
        String input = this->cliViewController.getInput();
        if (input == String("buy_cannons")) {
            buyCannons();
        } else if (input == String("buy_goods")) {
            buyGoods();
        } else if (input == String("buy_ship")) {
            buyShip();
        } else if (input == String("set_sail")) {
            setSail();
        } else if (input == String("repair")) {
            repairShip();
        } else if (input == String("quit")) {
            quitGame();
        } else {
            input_failed = true;
        }
    } while(input_failed == true);
    */
}
