#include "models/harbor.hpp"
#include "models/ship.hpp"
#include "std/random.hpp"

Harbor::Harbor(String name) : name(name) {
    this->goodsForSale = unique_ptr<Vector<Good*>>(new Vector<Good*>(true));
    this->shipsForSale = unique_ptr<Vector<Ship*>>(new Vector<Ship*>(true));
}
Harbor::Harbor(String name, unique_ptr<Vector<Ship*>> shipsForSale,
               unique_ptr<Vector<Good*>>  goodsForSale) noexcept :
    name(name), shipsForSale(std::move(shipsForSale)), goodsForSale(std::move(goodsForSale)) {}

String Harbor::getName() const noexcept {
    return this->name;
}

Vector<Good*>& Harbor::getGoodsForSale() const {
    return *this->goodsForSale;
}
Vector<Ship*>& Harbor::getShipsForSale() const {
    return *this->shipsForSale;
}

void Harbor::randomizeCannonStock() {
    this->lightCannonStock = Random::getInstance().getRandomInt(0, 5);
    this->mediumCannonStock = Random::getInstance().getRandomInt(0, 3);
    this->heavyCannonStock = Random::getInstance().getRandomInt(0, 2);
}

int Harbor::getLightCannonStock() const noexcept {
    return this->lightCannonStock;
}
int Harbor::getMediumCannonStock() const noexcept {
    return this->mediumCannonStock;
}
int Harbor::getHeavyCannonStock() const noexcept {
    return this->heavyCannonStock;
}
void Harbor::setLightCannonStock(int amount) noexcept {
    this->lightCannonStock = amount;
}
void Harbor::setMediumCannonStock(int amount) noexcept {
    this->mediumCannonStock = amount;
}
void Harbor::setHeavyCannonStock(int amount) noexcept {
    this->heavyCannonStock = amount;
}