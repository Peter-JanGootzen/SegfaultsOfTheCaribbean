#ifndef FILE_CANNON_HPP
#define FILE_CANNON_HPP
#include "models/enums/cannon_type.hpp"

// WHooh no rule of five here!
class Cannon {

public:
    Cannon(CannonType type);
    CannonType getCannonType();
    ~Cannon() = default;
private:
    CannonType type;
};

#endif