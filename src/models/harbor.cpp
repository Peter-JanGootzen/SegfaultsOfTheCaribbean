#include "models/harbor.hpp"

Harbor::Harbor() { };
Harbor::Harbor(String name, Ship* shipsForSale, unsigned int shipsForSaleSize,
    Good* goodsForSale, unsigned int goodsForSaleSize) :
    name(name), shipsForSale(shipsForSale), shipsForSaleSize(shipsForSaleSize),
    goodsForSale(goodsForSale), goodsForSaleSize(goodsForSaleSize) {

};