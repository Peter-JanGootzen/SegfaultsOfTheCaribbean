#ifndef FILE_SEA_CONTROLLER_HPP
#define FILE_SEA_CONTROLLER_HPP
#include "models/ship.hpp"
#include "std/random.hpp"

class SeaController {
public:
    SeaController();
    void sail(Ship& s);
    void moveShip(Ship& s, int distance);
private:
};

#endif