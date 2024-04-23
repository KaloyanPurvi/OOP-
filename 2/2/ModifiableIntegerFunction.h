#pragma once
#include <iostream>
#include <fstream>

class ModifiableIntegerFunction {
    bool isNotValid[INT16_MAX + 1]{ 0 }; //we make them all valid
    bool isSetOutcome[INT16_MAX + 1]{ 0 };
    int16_t setOutcomes[INT16_MAX + 1];
    int16_t(*f)(int16_t) = [](int16_t x) -> int16_t { return x; };


    bool containsInArray(int num) const;
public:
    int16_t(*getFunctionPointer())(int16_t); // it cant be const 
    ModifiableIntegerFunction() = default;
    ModifiableIntegerFunction(int16_t(*input)(int16_t));
    void setOutcome(int16_t x, int16_t y);
    void setNan(int16_t x);
    int16_t operator()(int16_t x); // ne iskam da e vynshna zashtoto iskam  da dobavqm cache stoinosti v setOutcomes

    friend ModifiableIntegerFunction operator+(const ModifiableIntegerFunction& left, const ModifiableIntegerFunction& right);
    friend ModifiableIntegerFunction operator-(const ModifiableIntegerFunction& left, const ModifiableIntegerFunction& right);
    ModifiableIntegerFunction operator()(const ModifiableIntegerFunction& g) const;
    friend bool operator<(const ModifiableIntegerFunction& left, const ModifiableIntegerFunction& right);
    friend bool operator<=(const ModifiableIntegerFunction& left, const ModifiableIntegerFunction& right);
    friend bool operator>(const ModifiableIntegerFunction& left, const ModifiableIntegerFunction& right);
    friend bool operator>=(const ModifiableIntegerFunction& left, const ModifiableIntegerFunction& right);
    friend bool operator==(const ModifiableIntegerFunction& left, const ModifiableIntegerFunction& right);
    friend bool operator!=(const ModifiableIntegerFunction& left, const ModifiableIntegerFunction& right);
    friend ModifiableIntegerFunction operator^(const ModifiableIntegerFunction& left, int16_t k);
    friend ModifiableIntegerFunction operator~(const ModifiableIntegerFunction& left);
    bool isSurection() const;
    bool isInection() const;
    bool isBijection() const;
    friend bool operator||(const ModifiableIntegerFunction& left, const ModifiableIntegerFunction& right);
    bool writeToFile(std::ofstream& ofs) const;
    bool writeToFile(const char* fileName) const;
    bool readFromFile(std::ifstream& ifs);
    bool readFromFile(const char* fileName);

    void printGraph(int x, int y) const;
};
