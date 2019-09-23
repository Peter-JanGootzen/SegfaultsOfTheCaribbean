#ifndef FILE_HARBOR_HPP
#define FILE_HARBOR_HPP
#include "std/string.hpp"
#include "models/ship.hpp"
#include "models/good.hpp"

class Harbor {
public:
    Harbor();
    Harbor(String name, Ship* shipsForSale, unsigned int shipsForSaleSize, Good* goodsForSale, unsigned int goodsForSaleSize);
private:
    String name;
    Ship* dockedShip;
    Ship* shipsForSale; 
    unsigned int shipsForSaleSize;
    Good* goodsForSale;
    unsigned int goodsForSaleSize;
};

#endif