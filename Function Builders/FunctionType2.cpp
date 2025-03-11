#include "FunctionType2.h"

FunctionType2::FunctionType2(const int* arguments, int n) : size(n) {
        for (int i = 0; i < size; i++) {
            defined[i] = arguments[i];
        }
    }
int32_t FunctionType2::operator()(int32_t x) const  {
        for (int i = 0; i < size; i++) {
            if (defined[i] == x) {
                return 1;
            }
        }
        return 0;
    }
bool FunctionType2::isDefinedAt(int32_t x) const  {
        return true;
    }
PartialFunction* FunctionType2::clone() const  {
        return new FunctionType2(*this);
    }

