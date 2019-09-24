#ifndef FILE_SEA_CONTROLLER_HPP
#define FILE_SEA_CONTROLLER_HPP
#include "models/ship.hpp"
#include "std/random.hpp"
#include "controllers/battle_controller.hpp"

class SeaController {
public:
    SeaController();
    void sail(Ship& s);
    void move(Ship& s);
private:
    BattleController battle_controller;
};

#endif