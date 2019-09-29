#include <iostream>
#include <utility>
#include "models/world.hpp"
#include "models/enums/ship_weight.hpp"
#include "controllers/game_controller.hpp"
#include "std/string.hpp"
#include "std/random.hpp"

int main(int argc, char const *argv[])
{
    String input = String("Halooo") << 5123213 << String("test");
    std::cout << input << std::endl;
    Ship* ship = new Ship(String("Pinnace"), 10000, 100, 200, 8, ShipWeight::Light, ShipSize::Small);
    Player* player = new Player();
    player->setShip(ship);
    auto harbors = new Vector<Harbor*>(2, true);
    auto rotoanShipsForSale = new Vector<Ship*>(2, true);
    rotoanShipsForSale->append(new Ship(String("Pinnace"), 10000, 100, 200, 8, ShipWeight::Light, ShipSize::Small));
    rotoanShipsForSale->append(new Ship(String("Sloep"), 19000, 110, 200, 14, ShipWeight::Light, ShipSize::Small));
    auto roatanGoods = new Vector<Good*>(2, true);
    roatanGoods->append(new Good(String("bakstenen"), 57, 114, 0, 42));
    roatanGoods->append(new Good(String("cacao"), 125, 375, 11, 107));
    harbors->append(new Harbor(String("Roatan"), rotoanShipsForSale, roatanGoods));
    auto belizeGoods = new Vector<Good*>(2, true);
    belizeGoods->append(new Good(String("bakstenen"), 23, 57, 27, 534));
    belizeGoods->append(new Good(String("cacao"), 100, 250, 25, 502));
    auto belizeShipsForSale = new Vector<Ship*>(2, true);
    belizeShipsForSale->append(new Ship(String("Pinnace"), 10000, 100, 200, 8, ShipWeight::Light, ShipSize::Small));
    belizeShipsForSale->append(new Ship(String("Sloep"), 19000, 110, 200, 14, ShipWeight::Light, ShipSize::Small));
    harbors->append(new Harbor(String("Belize"), belizeShipsForSale, belizeGoods));
    Vector<HarborDistance*>* harborDistances = new Vector<HarborDistance*>(2, true);
    harborDistances->append(new HarborDistance(harbors->get(0), harbors->get(1), 2));
    harborDistances->append(new HarborDistance(harbors->get(1), harbors->get(0), 2));
    World* world = new World(player, harbors, harborDistances);

    GameController gc { world };
    
    gc.start();
    gc.gameLoop();

    std::cout << String("Segmentation Fault (core dumped)") << std::endl;
    std::cout << String("Gnome im kdeing, you quit the game...") << std::endl;
    return 0;
}
