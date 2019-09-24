#include "models/world.hpp"

World::World(Player& player, HarborDistance* harborDistances, unsigned int harborDistancesSize) : 
            player(player), harborDistances(harborDistances), harborDistancesSize(harborDistancesSize) {

}

Player& World::getPlayer() const {
    return this->player;
}