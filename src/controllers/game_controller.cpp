#include <utility>
#include <iostream>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include "controllers/game_controller.hpp"
#include "controllers/harbor_controller.hpp"
#include "controllers/sea_controller.hpp"

GameController::GameController(unique_ptr<World> w)
    : world(std::move(w)) {
    cliViewController = unique_ptr<CliViewController>(new CliViewController());
    seaController = unique_ptr<SeaController>(new SeaController(*world, *cliViewController));
    harborController = unique_ptr<HarborController>(new HarborController(*world, *cliViewController));
}

void GameController::start() {
    cliViewController->writeOutput(String("Welcome to Segfaults of the Caribbean!"));
    cliViewController->writeOutput(String("Good luck in the dangerous waters of the Caribbean."));

    // Choosing a starting harbor
    bool input_failed { false };
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
            const size_t input { static_cast<size_t>(std::stol(input_string.c_str())) };
            if(input < world->getHarbors().getSize()) {
                world->getPlayer().getShip()->setDestination(world->getHarbors()[input]);
                harborController->dockShip();
            } else
            {
                input_failed = true;
            }
        }
        catch(...) {
            input_failed = true;
        }
    } while(input_failed == true);
}

void GameController::gameLoop() {
    bool quit { false };
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
    if(world->getPlayer().getMoney() >= 1'000'000)
        cliViewController->writeOutput(String("You won!"));
    else
        cliViewController->writeOutput(String("You lost!"));
}