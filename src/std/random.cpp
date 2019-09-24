#include "std/random.hpp"
#include <random>


Random* Random::instance = 0;

Random& Random::getInstance(){
    if(instance == 0)
        instance = new Random();
    return *instance;
}

Random::Random() {
    std::random_device device;
    std::default_random_engine dre(device());
};

int Random::getRandomInt(int min, int max) {
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(device);
};
