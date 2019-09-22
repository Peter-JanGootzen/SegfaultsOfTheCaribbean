#include <iostream>
#include "models/world.hpp"
#include "controllers/game_controller.hpp"
#include "std/string.hpp"

int main(int argc, char const *argv[])
{
    //World w;
    //// Do the world filling like a madlad god
    //auto gameController = GameController(w);
    //gameController.gameLoop();
    auto string = String(5, "test");
    std::cout << string << std::endl;
}
