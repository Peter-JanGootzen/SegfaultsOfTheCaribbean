#include <utility>
#include <iostream>
#include <cstring>
#include "controllers/game_controller.hpp"
#include "controllers/harbor_controller.hpp"
#include "controllers/sea_controller.hpp"

GameController::GameController(World* w) : 
    world(w) {
    cliViewController = new CliViewController();
    seaController = new SeaController(*w, *cliViewController);
    harborController = new HarborController(*w, *cliViewController);
};

void GameController::start() {
    cliViewController->writeOutput("Welcome to Segfaults of the Caribbean!");
    cliViewController->writeOutput("You will start with XXXXX money to buy a ship.");
    cliViewController->writeOutput("Good luck in the dangerous waters of the Caribbean.");
}

void GameController::gameLoop() {
    while((world->getPlayer().getMoney() < 1000000 && 
          (world->getPlayer().getShip() != nullptr &&  !world->getPlayer().getShip()->isSunken())) || 
          world->getPlayer().getShip() == nullptr) {
        cliViewController->writeOutput("---------------------------------------------------------------------------------------");
        if (world->getPlayer().getShip() != nullptr && world->getPlayer().getShip()->isDocked())
        { // You are docked
            this->harborController->presentOptions();
        } else { // you are at sea
            this->seaController->sail(world->getPlayer().getShip());
        }
        String input = cliViewController->getInput();
        if(input == "S") {
            cliViewController->writeOutput(String("Raise the sails!")); 
        }
        cliViewController->writeOutput(String("You wrote: ") << input);
        break;
    }
};

GameController::~GameController() {
    delete this->world;
    delete this->seaController;
    delete this->harborController;
    delete this->cliViewController;
};