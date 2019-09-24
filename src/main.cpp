#include <iostream>
#include <utility>
#include "models/world.hpp"
#include "models/enums/ship_weight.hpp"
#include "controllers/game_controller.hpp"
#include "std/string.hpp"
#include "std/random.hpp"

int main(int argc, char const *argv[])
{
    Player* player = new Player();
    auto harbors = new Harbor[2];
    auto rotoanShipsForSale = new Ship[2];
    rotoanShipsForSale[0] = Ship(String("Pinnace"), 10000, 100, 200, 8, ShipWeight::Light, ShipSize::Small);
    rotoanShipsForSale[1] = Ship(String("Sloep"), 19000, 110, 200, 14, ShipWeight::Light, ShipSize::Small);
    auto roatanGoods = new Good[2];
    roatanGoods[0] = Good(String("bakstenen"), 57, 114, 0, 42);
    roatanGoods[0] = Good(String("cacao"), 125, 375, 11, 107);
    harbors[0] = Harbor(String("Roatan"), rotoanShipsForSale, 2, roatanGoods, 2);
    auto belizeGoods = new Good[2];
    belizeGoods[0] = Good(String("bakstenen"), 23, 57, 27, 534);
    belizeGoods[0] = Good(String("cacao"), 100, 250, 25, 502);
    auto belizeShipsForSale = new Ship[2];
    belizeShipsForSale[0] = Ship(String("Pinnace"), 10000, 100, 200, 8, ShipWeight::Light, ShipSize::Small);
    belizeShipsForSale[1] = Ship(String("Sloep"), 19000, 110, 200, 14, ShipWeight::Light, ShipSize::Small);
    harbors[1] = Harbor(String("Belize"), belizeShipsForSale, 2, belizeGoods, 2);
    auto harborDistances = new HarborDistance[1];
    harborDistances[0] = HarborDistance(&harbors[0], &harbors[1], 2);
    World world = World(player, harbors, 2, harborDistances, 1);

    GameController gc { std::move(world) };
    
    gc.start();
    gc.gameLoop();

    return 0;
}
