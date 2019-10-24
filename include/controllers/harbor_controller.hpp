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
    bool presentOptions();
    void dockShip();
private:
    void tradeCannons();
    void tradeGoods();
    void buyShip();
    void repairShip();
    void setSail();
    World& world;
    CliViewController& cliViewController;
};
#endif