#include "models/harbor_distance.hpp"

HarborDistance::HarborDistance() {
    this->from = nullptr;
    this->to = nullptr;
};
HarborDistance::HarborDistance(Harbor* from, Harbor* to, int distance) :
    from(from), to(to), distance(distance) {

};