#ifndef FILE_WORLD_HPP
#define FILE_WORLD_HPP
#include "models/player.hpp"
#include "models/harbor_distance.hpp"

class World {
public:
    World(Player& player, HarborDistance* harborDistances, unsigned int harborDistancesSize);
    Player& getPlayer() const;
private:
    Player& player;
    HarborDistance* harborDistances;
    unsigned int harborDistancesSize;
};

#endif