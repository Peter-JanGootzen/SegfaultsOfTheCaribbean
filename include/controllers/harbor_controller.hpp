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
    void buyCannons();
    void buyShip();
    void repairShip();
    void dockShip();
    void setSail();
    void quitGame();
    void presentOptions();
private:
    World& world;
    CliViewController& cliViewController;
};
#endif