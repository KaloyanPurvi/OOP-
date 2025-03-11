#pragma once
#include <iostream>
#include "PartialFunction.h"


class ComparedFunction :public PartialFunction {
protected:
    PartialFunction** funcArray;
    size_t size;

    void copyFrom(const ComparedFunction& other);
    void moveFrom(ComparedFunction&& other);
    void free();

public:
    //we dont need a def constructor
    ComparedFunction(const PartialFunction* const* arr, size_t size);

    ComparedFunction& operator=(const ComparedFunction& other);
    ComparedFunction& operator=(ComparedFunction&& other); //we will reuse them in the max and min fun

    ComparedFunction(const ComparedFunction& other);
    ComparedFunction(ComparedFunction&& other);

    virtual int32_t operator()(int32_t x) const override = 0;

    virtual bool isDefinedAt(int32_t x) const override;
    virtual ~ComparedFunction() override;

    virtual PartialFunction* clone() const override=0;
};


//.....................................
//..................................... 
//.....................................
//..................................... 

