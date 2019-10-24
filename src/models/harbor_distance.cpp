#include "models/harbor_distance.hpp"

HarborDistance::HarborDistance(Harbor* from, Harbor* to, int distance) noexcept :
    from(from), to(to), distance(distance) {}

Harbor* HarborDistance::getFrom() const noexcept {
    return this->from;
}
Harbor* HarborDistance::getTo() const noexcept {
    return this->to;
}
int HarborDistance::getDistance() const noexcept {
    return distance;
}
