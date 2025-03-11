#pragma once
#include "ComparedFunction.h"

class MaximumFunction : public ComparedFunction {

public:
    int32_t operator()(int32_t x) const override;
    MaximumFunction(const PartialFunction* const* arr, size_t size);
 

    //operator = is dealt with by the compiler and the comparedFunction`s operator= and so on
    PartialFunction* clone() const override;

};

