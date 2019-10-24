#ifndef FILE_GAME_CONTROLLER_HPP
#define FILE_GAME_CONTROLLER_HPP
#include "std/random.hpp"
#include "std/unique_ptr.hpp"
#include "models/world.hpp"
#include "models/player.hpp"
#include "controllers/sea_controller.hpp"
#include "controllers/harbor_controller.hpp"
#include "view_controllers/cli_view_controller.hpp"

class GameController {
public:
    GameController(unique_ptr<World> w);
    ~GameController() = default;

    void start();
    void gameLoop();
private:
    unique_ptr<World> world;
    unique_ptr<SeaController> seaController;
    unique_ptr<HarborController> harborController;
    unique_ptr<CliViewController> cliViewController;
};

#endif