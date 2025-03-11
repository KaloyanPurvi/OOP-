#pragma once
#include "PartialFunction.h"
#include "FunctionType0.h"
#include "FunctionType1.h"
#include "FunctionType2.h"
#include <fstream>

class FunctionReader {
    PartialFunction* ptr;
    void read(std::ifstream& ifs);
public:
    FunctionReader(const char* fileName);
    FunctionReader(std::ifstream& ifs);

    bool isDefinedAt(int32_t x) const;

    int32_t operator()(int32_t x) const;
};