#ifndef FILE_RANDOM_HPP
#define FILE_RANDOM_HPP
#include <random>

class Random {

public:
    Random();
    ~Random()  { int i = 0; }
    int getRandomInt(int min, int max);
    static Random& getInstance();
private:
    std::random_device device;
    std::default_random_engine dre;
};

#endif