#pragma once
#include "PartialFunction.h"

class FunctionType1 : public PartialFunction {
    int32_t undefined[32];
    uint16_t size;
public:
    //we dont want a def constructor
    FunctionType1(const int32_t* arguments, uint16_t n);
    int32_t operator()(int32_t x) const override;
    bool isDefinedAt(int32_t x) const override;
    PartialFunction* clone() const override;
};
