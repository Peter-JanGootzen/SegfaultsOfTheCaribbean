#include <utility>
#include "controllers/game_controller.hpp"
#include "controllers/harbor_controller.hpp"
#include "controllers/sea_controller.hpp"

GameController::GameController(World w) : 
    world(w),
    seaController(*new SeaController()),
    harborController(*new HarborController()) {
};

void GameController::gameLoop() {
    while(world.getPlayer().getMoney() < 1000000 && !world.getPlayer().getShip().isSunken()) {
       
    }
};