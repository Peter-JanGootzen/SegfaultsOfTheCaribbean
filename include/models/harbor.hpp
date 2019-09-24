#ifndef FILE_HARBOR_HPP
#define FILE_HARBOR_HPP
#include "std/string.hpp"
#include "models/ship.hpp"
#include "models/good.hpp"

class Harbor {
public:
    Harbor();
    ~Harbor();
    Harbor(Harbor&& other);
    Harbor(const Harbor& other) = delete;
    Harbor& operator=(Harbor&& other);
    Harbor& operator=(const Harbor& other) = delete;
    Harbor(String name, Ship* shipsForSale, unsigned int shipsForSaleSize, Good* goodsForSale, unsigned int goodsForSaleSize);
private:
    String name;
    // Is not the owner
    Ship* dockedShip;
    Ship* shipsForSale; 
    unsigned int shipsForSaleSize;
    Good* goodsForSale;
    unsigned int goodsForSaleSize;
};

#endif