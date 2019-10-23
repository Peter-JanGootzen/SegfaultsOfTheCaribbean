#include "models/harbor_distance.hpp"

HarborDistance::HarborDistance() {
    this->from = nullptr;
    this->to = nullptr;
}
HarborDistance::HarborDistance(Harbor* from, Harbor* to, int distance) :
    from(from), to(to), distance(distance) {}

Harbor* HarborDistance::getFrom() const {
    return this->from;
}
Harbor* HarborDistance::getTo() const {
    return this->to;
}
int HarborDistance::getDistance() const {
    return distance;
}
