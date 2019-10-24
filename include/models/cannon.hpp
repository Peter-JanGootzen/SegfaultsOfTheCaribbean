#ifndef FILE_CANNON_HPP
#define FILE_CANNON_HPP
#include "models/enums/cannon_type.hpp"

// WHooh no rule of five here!
class Cannon {
public:
    Cannon(CannonType type) noexcept;
    CannonType getCannonType() const noexcept;
private:
    CannonType type;
};

#endif