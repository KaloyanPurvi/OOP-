#pragma once
#include "PartialFunction.h"

class FunctionType2 : public PartialFunction {
    int defined[32];
    int size;
public:
    FunctionType2(const int* arguments, int n);
    int32_t operator()(int32_t x) const override;
    bool isDefinedAt(int32_t x) const override;
    PartialFunction* clone() const override;
};
