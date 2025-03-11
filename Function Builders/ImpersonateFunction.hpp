#pragma once
#include <iostream>
struct ResultCriteria {
    bool isDefined;
    int32_t result;
    ResultCriteria(bool defined, int32_t res) : isDefined(defined), result(res) {}
};

//+++++++++++++++++++++++++++++++++++   ImpersonateFunction    +++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++   ImpersonateFunction    +++++++++++++++++++++++++++++++++++++++++++++++

template <class T>
class ImpersonateFunction {
    T func;
public:
    ImpersonateFunction(const T& func);
    ImpersonateFunction() = delete; //we dont need a def constructor
    ResultCriteria operator()(int32_t x) const;
};

template <class T>
ImpersonateFunction<T>::ImpersonateFunction(const T& func) : func(func) {}

template <class T>
ResultCriteria ImpersonateFunction<T>::operator()(int32_t x) const {
    return ResultCriteria(true, func(x));
}
