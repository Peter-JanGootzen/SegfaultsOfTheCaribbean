#include <iostream>
#include <fstream>
#include <utility>
#include "creation/world_creator.hpp"
#include "controllers/game_controller.hpp"

int main(int, const char* argv[])
{
    int exit_code = EXIT_SUCCESS;

    try {
        WorldCreator wc;
        unique_ptr<World> world = wc.createWorld();
        GameController gc { std::move(world) };
        // Increased performance, two functions at once, probably parallel ;)
        gc.start(); gc.gameLoop();
    } catch(const std::ifstream::failure& e) {
        std::cerr << e.what() << std::endl;
    } catch( const std::exception& ex) {
        std::cerr << argv[0] << ": " << ex.what() << std::endl;
        exit_code = EXIT_FAILURE;
    } catch (...) {
        std::cerr << "An exception has occured" << std::endl;
    }

    return exit_code;
}