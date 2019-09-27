#ifndef FILE_SEA_CONTROLLER_HPP
#define FILE_SEA_CONTROLLER_HPP
#include "models/ship.hpp"
#include "std/random.hpp"
#include "controllers/battle_controller.hpp"
#include "view_controllers/cli_view_controller.hpp"
#include "models/world.hpp"

class SeaController {
public:
    SeaController(World& w, CliViewController& cliViewController);
    bool sail();
    void move();
private:
    World& world;
    CliViewController& cliViewController;
    BattleController battleController;
};

#endif