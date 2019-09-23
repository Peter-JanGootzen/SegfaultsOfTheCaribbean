#ifndef FILE_GAME_CONTROLLER_HPP
#define FILE_GAME_CONTROLLER_HPP
#include "std/random.hpp"
#include "models/world.hpp"
#include "models/player.hpp"
#include "controllers/sea_controller.hpp"
#include "controllers/harbor_controller.hpp"

class GameController {
public:
    GameController(World w);
    void gameLoop();
private:
    World& world;
    Random random;
    SeaController& seaController;
    HarborController& harborController;
};

#endif