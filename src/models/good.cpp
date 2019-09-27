#include "models/good.hpp"
#include "std/random.hpp"

Good::Good() {};
Good::Good(String name, int minPrice, int maxPrice, int minAmount, int maxAmount) :
    name(name), minPrice(minPrice), maxPrice(maxPrice), minAmount(minAmount),
    maxAmount(maxAmount) {

};

String Good::getName() const {
    return this->name;
}
int Good::getAmount() const {
    return this->getAmount();
}
void Good::randomizePrice() {
    this->currentPrice = Random::getInstance().getRandomInt(minPrice, maxPrice);
}
void Good::randomizeAmount() {
    this->currentAmount = Random::getInstance().getRandomInt(minAmount, maxAmount);
}