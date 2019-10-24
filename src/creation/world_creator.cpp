#include "creation/world_creator.hpp"
#include "std/csv_reader.hpp"
#include "std/random.hpp"

unique_ptr<World> WorldCreator::createWorld() const {
    CSVReader r;
    auto distances { r.readFile(String("../data/distances.csv")) };
    auto harbors { new Vector<Harbor*>(true) };
    auto harbor_distances { new Vector<HarborDistance*>(true) };
    Harbor* current_harbor { nullptr };
    for (size_t i = 0; i < distances->getSize(); i++) {
        if (i == 0) { // maak de harbors aan
            for (size_t k = 0; k < (*distances)[i]->getSize(); k++) {
                if (k == 0) // ignore the first, it's empty
                    continue;
                harbors->append(new Harbor(*(*(*distances)[i])[k]));
            }
        } else {
            for (size_t k = 0; k < (*distances)[i]->getSize(); k++) {
                auto value { *(*(*distances)[i])[k] };
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

    auto goods_prices { r.readFile(String("../data/goods_prices.csv")) };
    auto goods_amounts { r.readFile(String("../data/goods_amounts.csv")) };

    Vector<String*>* goods_header = nullptr;
    for (size_t i = 0; i < goods_prices->getSize(); i++) {
        if (i == 0) { // header
            goods_header = (*goods_prices)[i];
        } else {
            Harbor* current_harbor { nullptr };
            for (size_t k = 0; k < (*goods_prices)[i]->getSize(); k++) {
                if (k == 0) {
                    String current_harbor_name { *(*(*goods_prices)[i])[k] };
                    current_harbor = harbors->get_filter([name = current_harbor_name](Harbor* h) -> bool {
                        return h->getName() == name;
                    });
                } else {
                    String name { *(*goods_header)[k] };
                    String price { *(*(*goods_prices)[i])[k] };
                    int minPrice { std::atoi(price.substr(0, price.find('-')).c_str()) };
                    int maxPrice { std::atoi(price.substr(price.find('-') + 1, price.size() - 1).c_str()) };
                    String amount { *(*(*goods_amounts)[i])[k] };
                    int minAmount { std::atoi(amount.substr(0, amount.find('-')).c_str()) };
                    int maxAmount { std::atoi(amount.substr(amount.find('-') + 1, amount.size() - 1).c_str()) };
                    current_harbor->getGoodsForSale().append(new Good(name, minPrice, maxPrice, minAmount, maxAmount));
                }
            }
        }
    }

    auto ships { r.readFile(String("../data/ships.csv")) };
    auto ship_array { Vector<Ship*>(true) };
    for (size_t i = 0; i < ships->getSize(); i++) {
        if (i == 0) {
            // Ignore the header
            continue;
        }
        else {
            String name { *(*(*ships)[i])[0] };
            int price { std::atoi((*(*(*ships)[i])[1]).c_str()) };
            int cargo { std::atoi((*(*(*ships)[i])[2]).c_str()) };
            int cannons { std::atoi((*(*(*ships)[i])[3]).c_str()) };
            int health { std::atoi((*(*(*ships)[i])[4]).c_str()) };
            String* spec { (*(*ships)[i])[5] };
            String* spec_first { nullptr };
            String* spec_second { nullptr };
            try {
                spec_first = new String(spec->substr(0, spec->find(',')));
                spec_second = new String(spec->substr(spec->find(',') + 1, spec->size() - 1));
            } catch (const std::out_of_range& ex) {
                spec_first = new String(*spec);
            }
            auto specialties { Vector<String*>(true) };
            specialties.append(spec_first);
            if(spec_second != nullptr)
                specialties.append(spec_second);
            ShipWeight weight { ShipWeight::Normal };
            ShipSize size { ShipSize::Normal };
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

    auto player { new Player() };
    player->setShip(ship_array.remove_index(0));
    // Divide ships over harbors
    Random& random { Random::getInstance() };
    while(true) {
        for(size_t i = 0; i < harbors->getSize(); i++) {
            if(random.getRandomInt(1, 100) > 50) {
                (*harbors)[i]->getShipsForSale().append(ship_array.remove_index(0));
                if(ship_array.getSize() == 0) goto exit_looping;
            }
        }
    }
    exit_looping:

    unique_ptr<World> world { new World(player, harbors, harbor_distances) };
    return world;
}