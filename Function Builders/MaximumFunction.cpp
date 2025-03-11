#pragma once
#include "MaximumFunction.h"

MaximumFunction::MaximumFunction(const PartialFunction* const* arr, size_t size) :ComparedFunction(arr, size) {}
int32_t MaximumFunction::operator()(int32_t x) const
{
    int32_t result = INT32_MIN;
    for (int i = 0; i < size; i++) {
        if (funcArray[i]->isDefinedAt(x)) { //operator&& would work fine here because only if the 1st arg is correct will the second be calculated but i will not use it instead:
            int32_t currentResult = (*funcArray[i])(x); //so that we dont calculate it twice, it could be a really complicated function
            if (currentResult > result)
                result = currentResult;
        }
    }
    return result;
}

PartialFunction* MaximumFunction::clone() const{
    return new MaximumFunction(*this);
}