#ifndef FILE_WORLD_HPP
#define FILE_WORLD_HPP
#include "models/player.hpp"
#include "models/harbor_distance.hpp"
#include "std/vector.hpp"

class World {
public:
    World(Player* player, Vector<Harbor*>* harbors, Vector<HarborDistance*>* harborDistances);
    ~World();
    World(World&& other);
    World(const World& other) = delete;
    World& operator=(World&& other);
    World& operator=(const World& other) = delete;
    Player& getPlayer() const;
    Vector<HarborDistance*>& getHarborDistances() const;
    Vector<Harbor*>& getHarbors() const;
private:
    Player* player;
    Vector<HarborDistance*>* harborDistances;
    Vector<Harbor*>* harbors;
};

#endif