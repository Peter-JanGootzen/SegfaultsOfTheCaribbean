#include "models/good.hpp"

Good::Good() {};
Good::Good(String name, int minPrice, int maxPrice, int minAmount, int maxAmount) :
    name(name), minPrice(minPrice), maxPrice(maxPrice), minAmount(minAmount),
    maxAmount(maxAmount) {

};