#ifndef FILE_WORLD_HPP
#define FILE_WORLD_HPP
#include "models/player.hpp"
#include "models/harbor_distance.hpp"
#include "std/vector.hpp"
#include "std/unique_ptr.hpp"

class World {
public:
    World(unique_ptr<Player> player, unique_ptr<Vector<Harbor*>> harbors,
          unique_ptr<Vector<HarborDistance*>> harborDistances) noexcept;
    ~World() = default;
    World(World&& other) = delete;
    World(const World& other) = delete;
    World& operator=(World&& other) = delete;
    World& operator=(const World& other) = delete;
    Player& getPlayer() const;
    Vector<HarborDistance*>& getHarborDistances() const;
    Vector<Harbor*>& getHarbors() const;
private:
    unique_ptr<Player> player;
    unique_ptr<Vector<HarborDistance*>> harborDistances;
    unique_ptr<Vector<Harbor*>> harbors;
};

#endif