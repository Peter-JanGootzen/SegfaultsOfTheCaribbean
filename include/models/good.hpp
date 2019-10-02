#ifndef FILE_GOOD_HPP
#define FILE_GOOD_HPP
#include "std/string.hpp"

// WHooh no rule of five here!
class Good {
public:
    Good();
    Good(String name, int minPrice, int maxPrice, int minAmount, int maxAmount);
    Good(String name, int currentAmount);
    String name;
    int getPrice() const;
    String getName() const;
    void randomizePrice();
    int getAmount() const;
    void setAmount(int amount);
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