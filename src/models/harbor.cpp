#include "models/harbor.hpp"

Harbor::Harbor() {
    this->dockedShip = nullptr;
    this->goodsForSale = nullptr;
    this->shipsForSale = nullptr;
};
Harbor::Harbor(String name, Ship* shipsForSale, unsigned int shipsForSaleSize,
    Good* goodsForSale, unsigned int goodsForSaleSize) :
    name(name), shipsForSale(shipsForSale), shipsForSaleSize(shipsForSaleSize),
    goodsForSale(goodsForSale), goodsForSaleSize(goodsForSaleSize) {

};

Harbor::Harbor(Harbor&& other) {
    // stack
    this->goodsForSaleSize = other.goodsForSaleSize;
    this->shipsForSaleSize = other.shipsForSaleSize;
    this->name = other.name;

    // heap
    this->dockedShip = other.dockedShip;
    other.dockedShip = nullptr;
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
        this->goodsForSaleSize = other.goodsForSaleSize;
        this->shipsForSaleSize = other.shipsForSaleSize;
        this->name = other.name;

        // heap
        if (this->dockedShip != nullptr)
            delete this->dockedShip;
        this->dockedShip = other.dockedShip;
        other.dockedShip = nullptr;
        if (this->goodsForSale != nullptr)
            delete[] this->goodsForSale;
        this->goodsForSale = other.goodsForSale;
        other.goodsForSale = nullptr;
        if (this->shipsForSale != nullptr)
            delete[] this->shipsForSale;
        this->shipsForSale = other.shipsForSale;
        other.shipsForSale = nullptr;
    }
    return *this;
}
//Harbor& Harbor::operator=(const Harbor& other) {
//
//}

Harbor::~Harbor() {
    delete[] shipsForSale;
    delete[] goodsForSale;
}