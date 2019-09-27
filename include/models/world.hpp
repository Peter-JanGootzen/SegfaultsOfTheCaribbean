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
    HarborDistance* const getHarborDistances() const;
    unsigned int getHarborDistancesSize() const;
    Harbor* const getHarbors() const;
    unsigned int getHarborsSize() const;
private:
    Player* player;
    HarborDistance* harborDistances;
    unsigned int harborDistancesSize;
    Harbor* harbors;
    unsigned int harborsSize;
};

#endif