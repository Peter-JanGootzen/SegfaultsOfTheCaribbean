#include "models/cannon.hpp"
#include "models/enums/cannon_type.hpp"

Cannon::Cannon(CannonType type) noexcept : type(type) {}

CannonType Cannon::getCannonType() const noexcept {
    return type;
}