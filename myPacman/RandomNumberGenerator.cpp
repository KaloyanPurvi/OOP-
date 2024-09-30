#include "RandomNumberGenerator.h"

//it needs to use time to be "random"
std::mt19937 RandomNumberGenerator::rng(std::time(0));


RandomNumberGenerator::RandomNumberGenerator(int minVal, int maxVal)
    : minValue(minVal), maxValue(maxVal) {}

int RandomNumberGenerator::generate() {
    std::uniform_int_distribution<int> dist(minValue, maxValue);
    return dist(rng);
}