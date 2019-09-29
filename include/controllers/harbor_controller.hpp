#ifndef FILE_HARBOR_CONTROLLER_HPP
#define FILE_HARBOR_CONTROLLER_HPP
#include "std/string.hpp"
#include "models/player.hpp"
#include "models/ship.hpp"
#include "view_controllers/cli_view_controller.hpp"
#include "models/world.hpp"

class HarborController {
public:
    HarborController(World& w, CliViewController& cliViewController);
    void buyGoods();
    void tradeCannons();
    void buyShip();
    void repairShip();
    void dockShip();
    void setSail();
    bool presentOptions();
private:
    World& world;
    CliViewController& cliViewController;
};
#endif