#ifndef FILE_WORLD_CREATOR_HPP
#define FILE_WORLD_CREATOR_HPP

#include "std/unique_ptr.hpp"
#include "models/world.hpp"

class WorldCreator {
public:
    unique_ptr<World> createWorld() const;
};

#endif // FILE_WORLD_CREATOR_HPP