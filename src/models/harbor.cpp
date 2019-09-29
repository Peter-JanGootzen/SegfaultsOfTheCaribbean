#include "models/harbor.hpp"
#include "models/ship.hpp"

Harbor::Harbor() {
    this->goodsForSale = new Vector<Good*>(0, true);
    this->shipsForSale = new Vector<Ship*>(0, true);
};
Harbor::Harbor(String name, Vector<Ship*>* shipsForSale, Vector<Good*>* goodsForSale) :
    name(name), shipsForSale(shipsForSale), goodsForSale(goodsForSale) {

};

String Harbor::getName() const {
    return this->name;
};

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

Harbor::~Harbor() {
    if (shipsForSale != nullptr)
        delete shipsForSale;
    if (goodsForSale != nullptr)
        delete goodsForSale;
}