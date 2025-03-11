#pragma once
#include "FunctionType0.h"

FunctionType0::FunctionType0(const int32_t* arguments, const int32_t* results, uint16_t n) : size(n) {
    for (int i = 0; i < size; i++) {
        args[i] = arguments[i];
        res[i] = results[i];
    }
}
int32_t FunctionType0::operator()(int32_t x) const  {
    for (int i = 0; i < size; i++) {
        if (args[i] == x) {
            return res[i];
        }
    }
    throw std::runtime_error("Function not defined at this point");
}
bool FunctionType0::isDefinedAt(int32_t x) const  {
    for (int i = 0; i < size; i++) {
        if (args[i] == x) {
            return true;
        }
    }
    return false;
}
PartialFunction* FunctionType0::clone() const {
    return new FunctionType0(*this);
}