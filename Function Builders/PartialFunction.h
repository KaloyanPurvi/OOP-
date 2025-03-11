#pragma once
#include <iostream>

class PartialFunction {
public:
    //we dont need a def constructor since its abstract class andd its delited
    virtual int32_t operator()(int32_t x) const = 0;
    virtual bool isDefinedAt(int32_t x) const = 0;
    virtual ~PartialFunction() = default;
    virtual PartialFunction* clone() const = 0;
};


