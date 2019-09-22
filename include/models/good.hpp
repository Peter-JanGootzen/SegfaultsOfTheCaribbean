#ifndef FILE_GOOD_HPP
#define FILE_GOOD_HPP
#include "std/string.hpp"

class Good {
public:
    String name;
    int getPrice();
    void randomizePrice();
    int getAmount();
    void randomizeAmount();
private:
    int minPrice;
    int maxPrice;
    int currentPrice;
    int minAmount;
    int maxAmount;
    int currentAmount;
};

#endif