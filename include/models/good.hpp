#ifndef FILE_GOOD_HPP
#define FILE_GOOD_HPP
#include "std/string.hpp"

// WHooh no rule of five here!
class Good {
public:
    Good();
    Good(String name, int minPrice, int maxPrice, int minAmount, int maxAmount);
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