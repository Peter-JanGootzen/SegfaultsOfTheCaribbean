#ifndef FILE_GAME_CONTROLLER_HPP
#define FILE_GAME_CONTROLLER_HPP
#include "models/world.hpp"

class GameController {
public:
    GameController(World w);
    void gameLoop();
};

#endif