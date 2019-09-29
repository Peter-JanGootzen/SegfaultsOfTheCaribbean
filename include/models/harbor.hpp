#ifndef FILE_HARBOR_HPP
#define FILE_HARBOR_HPP
#include "std/string.hpp"
#include "std/vector.hpp"
#include "models/ship.hpp"
#include "models/good.hpp"

class Ship;

class Harbor {
public:
    Harbor();
    ~Harbor();
    Harbor(Harbor&& other);
    Harbor(const Harbor& other) = delete;
    Harbor& operator=(Harbor&& other);
    Harbor& operator=(const Harbor& other) = delete;
    Harbor(String name, Vector<Ship*>* shipsForSale, Vector<Good*>* goodsForSale);

    String getName() const;
    Vector<Good*>& getGoodsForSale() const;
    Vector<Ship*>& getShipsForSale() const;
private:
    String name;
    Vector<Ship*>* shipsForSale; 
    Vector<Good*>* goodsForSale;
};

#endif