#ifndef FILE_GAME_CONTROLLER_HPP
#define FILE_GAME_CONTROLLER_HPP
#include "std/random.hpp"
#include "models/world.hpp"
#include "models/player.hpp"
#include "controllers/sea_controller.hpp"
#include "controllers/harbor_controller.hpp"
#include "view_controllers/cli_view_controller.hpp"

class GameController {
public:
    GameController(World w);
    ~GameController();

    void start();
    void gameLoop();
private:
    World world;
    Random random;
    SeaController* seaController;
    HarborController* harborController;
    CliViewController* cliViewController;
};

#endif