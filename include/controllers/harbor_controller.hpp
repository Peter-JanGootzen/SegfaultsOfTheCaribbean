#ifndef FILE_HARBOR_CONTROLLER_HPP
#define FILE_HARBOR_CONTROLLER_HPP
#include "std/string.hpp"
#include "models/player.hpp"

class HarborController {
public:
    void buyGoods(Player p, String[] args);
    void buyCannons(Player p, String[] args);
    void buyShip(Player p, String[] args);
private:
};
#endif