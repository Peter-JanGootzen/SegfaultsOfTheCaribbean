#ifndef FILE_CANNON_HPP
#define FILE_CANNON_HPP
#include "models/enums/cannon_type.hpp"

// WHooh no rule of five here!
class Cannon {

public:
    Cannon(CannonType type);
    ~Cannon();
private:
    CannonType type;
};

#endif