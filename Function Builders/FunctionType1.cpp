#pragma once
#include "FunctionType1.h"

FunctionType1::FunctionType1(const int32_t* arguments, uint16_t n) : size(n) {
        for (int i = 0; i < size; i++) {
            undefined[i] = arguments[i];
        }
    }
int32_t FunctionType1::operator()(int32_t x) const  {
        for (int i = 0; i < size; i++) {
            if (undefined[i] == x) {
                throw std::runtime_error("Function not defined at point");
            }
        }
        return x;
    }
    bool FunctionType1::isDefinedAt(int32_t x) const  {
        for (int i = 0; i < size; i++) {
            if (undefined[i] == x) {
                return false;
            }
        }return true;
    }
    PartialFunction* FunctionType1::clone() const  {
        return new FunctionType1(*this);
    }
