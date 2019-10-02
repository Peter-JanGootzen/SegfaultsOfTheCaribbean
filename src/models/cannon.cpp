#include "models/cannon.hpp"
#include "models/enums/cannon_type.hpp"

Cannon::Cannon(CannonType type) : type(type) {

}

CannonType Cannon::getCannonType() {
    return type;
}