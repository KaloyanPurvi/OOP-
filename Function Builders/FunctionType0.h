#pragma once
#include "PartialFunction.h"
class FunctionType0 : public PartialFunction {
    int32_t args[32];
    int32_t res[32];
    uint16_t size;
public:
    FunctionType0(const int32_t* arguments, const int32_t* results, uint16_t n);
        
    int32_t operator()(int32_t x) const override;
    bool isDefinedAt(int32_t x) const override;
    PartialFunction* clone() const override;
};