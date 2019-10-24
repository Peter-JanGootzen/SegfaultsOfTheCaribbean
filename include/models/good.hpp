#ifndef FILE_GOOD_HPP
#define FILE_GOOD_HPP
#include "std/string.hpp"

// WHooh no rule of five here!
class Good {
public:
    Good(String name, int minPrice, int maxPrice, int minAmount, int maxAmount);
    Good(String name, int currentAmount);
    int getPrice() const noexcept;
    String getName() const noexcept;
    void randomizePrice();
    int getAmount() const noexcept;
    void setAmount(int amount) noexcept;
    void randomizeAmount();
private:
    String name;
    int minPrice;
    int maxPrice;
    int currentPrice;
    int minAmount;
    int maxAmount;
    int currentAmount;
};

#endif