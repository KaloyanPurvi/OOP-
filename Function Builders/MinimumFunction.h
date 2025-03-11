#pragma once
#include "ComparedFunction.h"

class MinimumFunction : public ComparedFunction {

public:
    int32_t operator()(int32_t x) const override;
    MinimumFunction(const PartialFunction* const* arr, size_t size);
    PartialFunction* clone() const override;
};

