#include "models/world.hpp"

World::World(Player* player, Harbor* harbors, unsigned int harborsSize, HarborDistance* harborDistances, unsigned int harborDistancesSize) : 
            player(player), harbors(harbors), harborsSize(harborsSize), harborDistances(harborDistances), harborDistancesSize(harborDistancesSize) {

}

Player& World::getPlayer() const {
    return *this->player;
}

World::~World() {
    delete player;
    delete[] harborDistances;
    delete[] harbors;
}

World::World(World&& other) {
    // stack
    this->harborDistancesSize = other.harborDistancesSize;
    this->harborsSize = other.harborsSize;

    // heap
    this->player = other.player;
    other.player = nullptr;
    this->harborDistances = other.harborDistances;
    other.harborDistances = nullptr;
    this->harbors = other.harbors;
    other.harbors = nullptr;
}
//World::World(const World& other) {
//    if (this != &other) {
//        // stack
//        this->harborDistances = other.harborDistances;
//
//        // heap
//        delete this->player;
//        this->player = &(*other.player);
//
//        delete[] this->harborDistances;
//        this->harborDistances = &(*other.harborDistances);
//        this->harborDistances = other.harborDistances;
//    }
//}
World& World::operator=(World&& other) {
    if (this != &other) {
        // stack
        this->harborDistancesSize = other.harborDistancesSize;
        this->harborsSize = other.harborsSize;

        // heap
        if (this->player != nullptr)
            delete this->player;
        this->player = other.player;
        other.player = nullptr;
        if (this->harborDistances != nullptr)
            delete[] this->harborDistances;
        this->harborDistances = other.harborDistances;
        other.harborDistances = nullptr;
        if (this->harbors != nullptr)
            delete[] this->harbors;
        this->harbors = other.harbors;
        other.harbors = nullptr;
    }
    return *this;
}
//World& World::operator=(const World& other) {
//    if (this != &other) {
//        // stack
//        this->harborDistances = other.harborDistances;
//
//        // heap
//        delete this->player;
//        this->player = &(*other.player);
//
//        delete[] this->harborDistances;
//        this->harborDistances = &(*other.harborDistances);
//        this->harborDistances = other.harborDistances;
//    }
//    return *this;
//}