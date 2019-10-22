#include <iostream>
#include <utility>
#include "models/world.hpp"
#include "models/enums/ship_weight.hpp"
#include "controllers/game_controller.hpp"
#include "std/string.hpp"
#include "std/random.hpp"
#include "std/csv_reader.hpp"

World* createWorld() {
    CSVReader r;
    auto distances = r.readFile(String("../data/distances.csv"));
    auto harbors = new Vector<Harbor*>(true);
    auto harbor_distances = new Vector<HarborDistance*>(true);
    Harbor* current_harbor = nullptr;
    for (size_t i = 0; i < distances->getSize(); i++) {
        if (i == 0) { // maak de harbors aan
            for (size_t k = 0; k < (*distances)[i]->getSize(); k++) {
                if (k == 0) // ignore the first, it's empty
                    continue;
                harbors->append(new Harbor(*(*(*distances)[i])[k]));
            }
        } else {
            for (size_t k = 0; k < (*distances)[i]->getSize(); k++) {
                auto value = *(*(*distances)[i])[k];
                if (k == 0)
                    current_harbor = harbors->get_filter([name = value](Harbor* h) -> bool {
                        return h->getName() == name;
                    });
                else {
                    auto to_harbor = harbors->get_filter([to = (*harbors)[k - 1]](Harbor* h) -> bool {
                        return h == to;
                    });
                    auto distance = std::atoi(value.c_str());
                    harbor_distances->append(new HarborDistance(current_harbor, to_harbor, distance));
                }
            }
        }
    }
    distances->~Vector();

    auto goods_prices = r.readFile(String("../data/goods_prices.csv"));
    auto goods_amounts = r.readFile(String("../data/goods_amounts.csv"));

    auto goods = new Vector<Good*>(true);
    Vector<String*>* goods_header = nullptr;
    for (size_t i = 0; i < goods_prices->getSize(); i++) {
        if (i == 0) { // header
            goods_header = (*goods_prices)[i];
        } else {
            Harbor* current_harbor = nullptr;
            for (size_t k = 0; k < (*goods_prices)[i]->getSize(); k++) {
                if (k == 0) {
                    String current_harbor_name = *(*(*goods_prices)[i])[k];
                    current_harbor = harbors->get_filter([name = current_harbor_name](Harbor* h) -> bool {
                        return h->getName() == name;
                    });
                } else {
                    String name = *(*goods_header)[k];
                    String price = *(*(*goods_prices)[i])[k];
                    int minPrice = std::atoi(price.substr(0, price.find('-')).c_str());
                    int maxPrice = std::atoi(price.substr(price.find('-') + 1, price.size() - 1).c_str());
                    String amount = *(*(*goods_amounts)[i])[k];
                    int minAmount = std::atoi(amount.substr(0, amount.find('-')).c_str());
                    int maxAmount = std::atoi(amount.substr(amount.find('-') + 1, amount.size() - 1).c_str());
                    current_harbor->getGoodsForSale().append(new Good(name, minPrice, maxPrice, minAmount, maxAmount));
                }
            }
        }
    }
    goods_prices->~Vector();
    goods_amounts->~Vector();


    auto ships = r.readFile(String("../data/ships.csv"));
    auto ship_array = Vector<Ship*>(true);
    Vector<String*>* ships_header = nullptr;
    for (size_t i = 0; i < ships->getSize(); i++) {
        if (i == 0) {
            ships_header = (*ships)[i];
        }
        else {
            String name = *(*(*ships)[i])[0];
            int price = std::atoi((*(*(*ships)[i])[1]).c_str());
            int cargo = std::atoi((*(*(*ships)[i])[2]).c_str());
            int cannons = std::atoi((*(*(*ships)[i])[3]).c_str());
            int health = std::atoi((*(*(*ships)[i])[4]).c_str());
            String* spec = (*(*ships)[i])[5];
            String* spec_first = nullptr;
            String* spec_second = nullptr;
            if(spec->find(',') != -1) {
                spec_first = new String(spec->substr(0, spec->find(',')));
                spec_second = new String(spec->substr(spec->find(',') + 1, spec->size() - 1));
            } else {
                spec_first = spec;
            }
            auto specialties = Vector<String*>(true);
            specialties.append(spec_first);
            specialties.append(spec_second);
            ShipWeight weight = ShipWeight::Normal;
            ShipSize size = ShipSize::Normal;
            for(size_t i = 0; i < specialties.getSize(); i++) {
                if(*spec == String("klein")) {
                    size = ShipSize::Small;
                } else if(*spec == String("log")) {
                    weight = ShipWeight::Heavy;
                } else if (*spec == String("licht")) {
                    weight = ShipWeight::Light; 
                }
            }

            ship_array.append(new Ship(name, price, health, cargo, cannons, weight, size));
        }
    }

    // WORLD
    auto player = new Player();
    auto world = new World(player, harbors, harbor_distances);
    return world;
}

int main()
{
    auto world = createWorld();
    auto gc = GameController(world);
    gc.start();
    gc.gameLoop();
}