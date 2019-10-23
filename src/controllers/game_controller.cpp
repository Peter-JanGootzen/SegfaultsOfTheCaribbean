#include <utility>
#include <iostream>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include "controllers/game_controller.hpp"
#include "controllers/harbor_controller.hpp"
#include "controllers/sea_controller.hpp"

GameController::GameController(World* w) : 
    world(w) {
    cliViewController = new CliViewController();
    seaController = new SeaController(*w, *cliViewController);
    harborController = new HarborController(*w, *cliViewController);
}

void GameController::start() {
    cliViewController->writeOutput(String("Welcome to Segfaults of the Caribbean!"));
    cliViewController->writeOutput(String("Good luck in the dangerous waters of the Caribbean."));

    // Choosing a starting harbor
    bool input_failed = false;
    do {
        if (input_failed == true) {
            cliViewController->writeOutput(String("The given input was incorrect!"));
            input_failed = false;
        }

        cliViewController->writeOutput(String("In which harbor would you like to start?"));

        for(size_t i = 0; i < world->getHarbors().getSize(); i++) {
            cliViewController->writeOutput(String() << i << String(": ") << world->getHarbors()[i]->getName());
        }
        try {
            const String input_string = cliViewController->getInput();
            const int input = std::atoi(input_string.c_str());
            if(input >= 0 && input < world->getHarbors().getSize()) {
                world->getPlayer().getShip()->setDestination(world->getHarbors()[input]);
                harborController->dockShip();
            } else
            {
                input_failed = true;
            }
        }
        catch(const std::invalid_argument&) {
            input_failed = true;
        }
    } while(input_failed == true);
}

void GameController::gameLoop() {
    bool quit = false;
    while(((world->getPlayer().getMoney() < 1'000'000 &&
          (world->getPlayer().getShip() != nullptr &&  !world->getPlayer().getShip()->isSunken())) ||
          world->getPlayer().getShip() == nullptr) &&
          !quit) {
        if (world->getPlayer().getShip() != nullptr && world->getPlayer().getShip()->isDocked())
        { // You are docked
            quit = this->harborController->presentOptions();
        } else { // you are at sea
            const bool arrived = this->seaController->sail();
            if (arrived)
                harborController->dockShip();
        }
        cliViewController->writeOutput(String("---------------------------------------------------------------------------------------"));
    }
}

GameController::~GameController() {
    delete this->world;
    delete this->seaController;
    delete this->harborController;
    delete this->cliViewController;
}