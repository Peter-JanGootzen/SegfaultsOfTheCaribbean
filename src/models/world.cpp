#include "models/world.hpp"

World::World(unique_ptr<Player> player, unique_ptr<Vector<Harbor*>> harbors,
             unique_ptr<Vector<HarborDistance*>> harborDistances) noexcept
    : player(std::move(player)), harborDistances(std::move(harborDistances)),
      harbors(std::move(harbors)) {}

Player& World::getPlayer() const {
    return *this->player;
}

Vector<HarborDistance*>& World::getHarborDistances() const {
    return *this->harborDistances;
}
Vector<Harbor*>& World::getHarbors() const {
    return *this->harbors;
}