#include "models/harbor_distance.hpp"

HarborDistance::HarborDistance() {};
HarborDistance::HarborDistance(Harbor* from, Harbor* to, int distance) :
    from(from), to(to), distance(distance) {

};