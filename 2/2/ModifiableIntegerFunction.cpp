#pragma once
#include "ModifiableIntegerFunction.h"
#include <iostream>


static void setAllToOneCharArray(char character,char* arr, size_t size) {
    for (int i = 0; i < size; i++) {
        
            arr[i] = character;
        
    }
}

static void printMatrix(char* arr, size_t rows, size_t colls) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < colls; j++) {
            std::cout << arr[i*colls + j]<<',';
        }
        std::cout << std::endl;
    }
}

/*
for (int i = 0; i < ARR_SIZE; i++) {
        
    }
*/

static ModifiableIntegerFunction fToThePowerOfTwo(int16_t(*left)(int16_t), int16_t k) {
    if (k == 0) {
        return ModifiableIntegerFunction([](int16_t x) -> int16_t { return 0; }); // x^0 = 1
    }
    static int16_t(*functionLeft)(int16_t) = left; //if its not static it goes boom :)

    ModifiableIntegerFunction result([](int16_t x) -> int16_t { return functionLeft(x) * functionLeft(x); });
    return result;
}
static void IntersectionOfArrays(bool* left, size_t lSize, const bool* right, size_t rSize) {
    for (int i = 0; i < lSize && i < rSize; i++) {
        left[i] &= right[i];
    }
}

static ModifiableIntegerFunction SumFunc(int16_t(*left)(int16_t), int16_t(*right)(int16_t)) {
    static int16_t(*functionLeft)(int16_t) = left; //if its not static it goes boom :)
    static int16_t(*functionRight)(int16_t) = right;
    ModifiableIntegerFunction result([](int16_t x) -> int16_t { return functionLeft(x) + functionRight(x); });
    return result;
}

static ModifiableIntegerFunction MinusFunc(int16_t(*left)(int16_t), int16_t(*right)(int16_t)) {
    static int16_t(*functionLeft)(int16_t) = left; //if its not static it goes boom :)
    static int16_t(*functionRight)(int16_t) = right;
    ModifiableIntegerFunction result([](int16_t x) -> int16_t { return functionLeft(x) - functionRight(x); });
    return result;
}

int16_t(*ModifiableIntegerFunction::getFunctionPointer())(int16_t) { return f; }

ModifiableIntegerFunction::ModifiableIntegerFunction(int16_t(*input)(int16_t)) {
    f = input;
}

void ModifiableIntegerFunction::setOutcome(int16_t x, int16_t y) {
    setOutcomes[x] = y;
    isNotValid[x] = false;
}
void ModifiableIntegerFunction::setNan(int16_t x) {
    isNotValid[x] = 1;
}


int16_t ModifiableIntegerFunction::operator()(int16_t x) { //iska mi se da sa vynshni ama compilatora ne mi dava da predef. operator ()
    if (isNotValid[x]) {
        std::cerr << "Error";
        return 0; //not the best option because there are functions which actually return 0, but thats why we have the cerr
    }
    if (isSetOutcome[x])return setOutcomes[x]; // Return the set outcome if not invalid
    isSetOutcome[x] = true;
    int16_t result = f(x);
    setOutcomes[x] = result; //otherwise calculcate the function and store cache
    return result;
}


ModifiableIntegerFunction operator+(const ModifiableIntegerFunction& left, const ModifiableIntegerFunction& right){
    //nikyde ne pishe che ako v right funciqta ne e definirana, che i tuk ne trqbva da byde
    // napravil sym go na funcionalno nivo i operator + pyrvo vryshta funciq - sled koeto presmqta otgovora podaden mu v rezultata 
    return SumFunc(left.f, right.f);
}

ModifiableIntegerFunction operator-(const ModifiableIntegerFunction& left, const ModifiableIntegerFunction& right) {
    //nikyde ne pishe che ako v right funciqta ne e definirana, che i tuk ne trqbva da byde
    // napravil sym go na funcionalno nivo i operator + pyrvo vryshta funciq - sled koeto presmqta otgovora podaden mu v rezultata 
    return MinusFunc(left.f, right.f);
}

bool operator<(const ModifiableIntegerFunction& left, const ModifiableIntegerFunction& right) {
    for (int i = 0; i <= INT16_MAX; i++) {
        if (left.isNotValid[i] && (!right.isNotValid[i])) continue;
        if (left.isNotValid[i] && right.isNotValid[i]) continue; //i do all the ifs to surpass the 'error message' in the () operator
        if (!left.isNotValid[i] && right.isNotValid[i]) return false;
        if (left.f(i) > right.f(i)) return false;
    }
    return left != right;
}
bool operator<=(const ModifiableIntegerFunction& left, const ModifiableIntegerFunction& right) {
    return (left < right) || (left == right);
}

bool operator>(const ModifiableIntegerFunction& left, const ModifiableIntegerFunction& right) {
    return right < left; //they just switch sides
}
bool operator>=(const ModifiableIntegerFunction& left, const ModifiableIntegerFunction& right) {
    return (right < left) || left == right;
}


bool operator==(const ModifiableIntegerFunction& left, const ModifiableIntegerFunction& right) {
    
    for (int i = 0; i <= INT16_MAX; i++) {
        if (left.isNotValid[i] && right.isNotValid[i]) continue;
        if (left.isNotValid[i] && (!right.isNotValid[i])) return false;
        if (!left.isNotValid[i] && right.isNotValid[i]) return false;
        if (left.f(i) != right.f(i)) return false;
    }
    return true;
}
bool operator!=(const ModifiableIntegerFunction& left, const ModifiableIntegerFunction& right) {
    return !(left == right);
}



bool operator||(const ModifiableIntegerFunction& left, const ModifiableIntegerFunction& right) {
    int i = 0;
    while (left.isNotValid[i] || right.isNotValid[i]) {
        i++;
    }
    uint16_t diff = left.f(i) - right.f(i);

    if (right.f(i) > left.f(i)) return right || (left);

    unsigned finish = INT16_MAX - diff - 1;
    for (; i < finish; i++) {
        if (left.isNotValid[i] || right.isNotValid[i]) continue;
        if (diff != (left.f(i) - right.f(i))) return false;
    }
    return true;
}



ModifiableIntegerFunction operator^(const ModifiableIntegerFunction& left, int16_t k) {
    if (k == 0) {
        return ModifiableIntegerFunction([](int16_t x) -> int16_t { return 0; }); // x^0 = 1
    }
    if (k == 1) {
        return left; // x^0 = 1
    }

    static int16_t(*pred)(int16_t) = left.f;

    while (k >= 1) {

        pred = fToThePowerOfTwo(pred, k).f;
        k--;
    }
    ModifiableIntegerFunction result(pred);
    return result;

}

ModifiableIntegerFunction operator~(const ModifiableIntegerFunction& left) {
    static int16_t(*keeper)(int16_t) = left.f;
    int16_t(*flipper)(int16_t) = [](int16_t x) -> int16_t { return 1 / keeper(x); };
    ModifiableIntegerFunction result(left); //this way we will keep the setNan parameters
    result.f = flipper;
    return result;
}

bool ModifiableIntegerFunction::containsInArray(int num) const {
    for (int i = 0; i < INT16_MAX; i++) {
        if (setOutcomes[i] == num) return true;
    }
    return false;
}

bool ModifiableIntegerFunction::isSurection() const{
    ModifiableIntegerFunction copy(*this); //i dont want to touch ours
    //lets calculate all the possible outcomes
    for (int i = 0; i < INT16_MAX; i++) {
        if (copy.isNotValid[i])return false;
        copy(i);
    }
    for (int i = 0; i < INT16_MAX; i++) {
        if (!copy.containsInArray(i)) return false;
    }
    return true;
}
bool ModifiableIntegerFunction::isInection() const {
    ModifiableIntegerFunction copy(*this); //i dont want to touch ours
    //lets calculate all the possible outcomes
    for (int i = 0; i < INT16_MAX; i++) {
        if (copy.isNotValid[i])return false;
        copy(i);
    }
    for (int i = 0; i < INT16_MAX; i++) {
        if (!copy.isSetOutcome[i]) return false;
    }
    return true;
}

bool ModifiableIntegerFunction::isBijection() const {
    return isInection() && isSurection();
}

bool ModifiableIntegerFunction::writeToFile(std::ofstream& ofs) const {
    ofs.write((const char*)this, sizeof(ModifiableIntegerFunction));
    
    return true;
}
bool ModifiableIntegerFunction::readFromFile(std::ifstream& ifs){
    int keeper = ifs.tellg();
    ifs.read((char*)this, sizeof(ModifiableIntegerFunction));
    ifs.seekg(keeper);
    ifs.clear();
    return true;
}

bool ModifiableIntegerFunction::writeToFile(const char* fileName) const {
    std::ofstream ofs(fileName, std::ios::binary);
    if (!ofs.is_open()) {
        return false;
    }
    writeToFile(ofs);
    ofs.close();
    return true;
}
bool ModifiableIntegerFunction::readFromFile(const char* fileName) {
    std::ifstream ifs(fileName, std::ios::binary);
    if (!ifs.is_open()) {
        return false;
    }
    readFromFile(ifs);
    return true;
}

void ModifiableIntegerFunction::printGraph(int x, int y) const {
    const unsigned ARR_SIZE = 20;
    char graph[ARR_SIZE][ARR_SIZE];
    char* graphP = *graph;
    //initialize the graph 
    setAllToOneCharArray(' ', graphP, ARR_SIZE*ARR_SIZE);

    for (int i = 0; i < ARR_SIZE; i++) {
        if (isNotValid[i+x])continue;
        uint16_t currentY = f(i+x);
        if (currentY < y || currentY >=(ARR_SIZE + y)) continue;
        //we have to keep in mind that the 'y' is responsible for the rows and that we need to reverse them 
        graph[ARR_SIZE - (currentY - y)-1][i] = currentY+'0';
    }

    printMatrix(graphP, ARR_SIZE, ARR_SIZE);
    
}

