#pragma once

#include <random>
#include <ctime>

class RandomNumberGenerator {
private:
    int minValue;
    int maxValue;
    static std::mt19937 rng; //we make it static so that next time it keeps on going and doesnt start over again

public:
   
    RandomNumberGenerator(int minVal, int maxVal);

    //here we will generate the number
    int generate();
};
