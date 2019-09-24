#ifndef FILE_HARBOR_DISTANCE_HPP
#define FILE_HARBOR_DISTANCE_HPP
#include "models/harbor.hpp"

// WHooh no rule of five here!
// This class is not the owner of it's heap data, so no destructor needed
class HarborDistance {
public:
    HarborDistance();
    HarborDistance(Harbor* from, Harbor* to, int distance);
    Harbor* from;
    Harbor* to;
    int distance;
};

#endif