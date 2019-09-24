#ifndef FILE_WORLD_HPP
#define FILE_WORLD_HPP
#include "models/player.hpp"
#include "models/harbor_distance.hpp"

class World {
public:
    World(Player* player, Harbor* harbors, unsigned int harborSize, HarborDistance* harborDistances, unsigned int harborDistancesSize);
    ~World();
    World(World&& other);
    World(const World& other) = delete;
    World& operator=(World&& other);
    World& operator=(const World& other) = delete;
    Player& getPlayer() const;
private:
    Player* player;
    HarborDistance* harborDistances;
    Harbor* harbors;
    unsigned int harborsSize;
    unsigned int harborDistancesSize;
};

#endif