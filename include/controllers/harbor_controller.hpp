#ifndef FILE_HARBOR_CONTROLLER_HPP
#define FILE_HARBOR_CONTROLLER_HPP
#include "std/string.hpp"
#include "models/player.hpp"
#include "models/ship.hpp"

class HarborController {
public:
    HarborController();
    void buyGoods(Player p);
    void buyCannons(Player p);
    void buyShip(Player p);
private:
};
#endif