#ifndef FILE_BATTLE_CONTROLLER_HPP
#define FILE_BATTLE_CONTROLLER_HPP

#include "models/ship.hpp"
#include "view_controllers/cli_view_controller.hpp"
#include "models/world.hpp"

class BattleController {
public:
    BattleController(World& w, CliViewController& cliViewController);
    void battle(Ship* s);
private:
    World& world;
    CliViewController& cliViewController;
};

#endif