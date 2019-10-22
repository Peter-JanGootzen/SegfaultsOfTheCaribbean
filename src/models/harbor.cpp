#include "models/harbor.hpp"
#include "models/ship.hpp"
#include "std/random.hpp"

Harbor::Harbor() {
    this->goodsForSale = new Vector<Good*>(true);
    this->shipsForSale = new Vector<Ship*>(true);
}
Harbor::Harbor(String name) : name(name) {
    this->goodsForSale = new Vector<Good*>(true);
    this->shipsForSale = new Vector<Ship*>(true);
}
Harbor::Harbor(String name, Vector<Ship*>* shipsForSale, Vector<Good*>* goodsForSale) :
    name(name), shipsForSale(shipsForSale), goodsForSale(goodsForSale) {

}

String Harbor::getName() const {
    return this->name;
}

Harbor::Harbor(Harbor&& other) {
    // stack
    this->name = other.name;

    // heap
    this->goodsForSale = other.goodsForSale;
    other.goodsForSale = nullptr;
    this->shipsForSale = other.shipsForSale;
    other.shipsForSale = nullptr;
}
//Harbor::Harbor(const Harbor& other) {
//
//}
Harbor& Harbor::operator=(Harbor&& other) {
    if (this != &other) {
        // stack
        this->name = other.name;

        // heap
        if (this->goodsForSale != nullptr)
            delete this->goodsForSale;
        this->goodsForSale = other.goodsForSale;
        other.goodsForSale = nullptr;
        if (this->shipsForSale != nullptr)
            delete this->shipsForSale;
        this->shipsForSale = other.shipsForSale;
        other.shipsForSale = nullptr;
    }
    return *this;
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

int Harbor::getLightCannonStock() const {
    return this->lightCannonStock;
}
int Harbor::getMediumCannonStock() const {
    return this->mediumCannonStock;
}
int Harbor::getHeavyCannonStock() const {
    return this->heavyCannonStock;
}
void Harbor::setLightCannonStock(int amount) {
    this->lightCannonStock = amount;
}
void Harbor::setMediumCannonStock(int amount) {
    this->mediumCannonStock = amount;
}
void Harbor::setHeavyCannonStock(int amount) {
    this->heavyCannonStock = amount;
}

Harbor::~Harbor() {
    if (shipsForSale != nullptr)
        delete shipsForSale;
    if (goodsForSale != nullptr)
        delete goodsForSale;
}