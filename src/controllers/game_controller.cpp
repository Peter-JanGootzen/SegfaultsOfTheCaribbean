#include <utility>
#include <iostream>
#include <cstring>
#include "controllers/game_controller.hpp"
#include "controllers/harbor_controller.hpp"
#include "controllers/sea_controller.hpp"

GameController::GameController(World w) : 
    world(std::move(w)),
    seaController(new SeaController()),
    harborController(new HarborController()),
    cliViewController(new CliViewController()) {
};

void GameController::start() {
    cliViewController->writeOutput("Welcome to Segfaults of the Caribbean!");
    cliViewController->writeOutput("You will start with XXXXX money to buy a ship.");
    cliViewController->writeOutput("Good luck in the dangerous waters of the Caribbean.");
}

void GameController::gameLoop() {
    while((world.getPlayer().getMoney() < 1000000 && 
          (world.getPlayer().getShip() != nullptr &&  !world.getPlayer().getShip()->isSunken())) || 
          world.getPlayer().getShip() == nullptr) {
        String input = cliViewController->getInput();
        if(input == "S") {
            cliViewController->writeOutput(String("Raise the sails!")); 
        }
        cliViewController->writeOutput(String("You wrote: ") << input);
        break;
    }
};

GameController::~GameController() {
    delete this->seaController;
    delete this->harborController;
    delete this->cliViewController;
};