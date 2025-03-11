#pragma once
#include "PartialFunction.h"
#include "ImpersonateFunction.hpp"
template <class T>
class PartialFunctionCriteria : public PartialFunction {
    ImpersonateFunction<T> criteria;
public:
    //we dont need a def constructor
    PartialFunctionCriteria(const ImpersonateFunction<T>& rhs);
    PartialFunctionCriteria(ImpersonateFunction<T>&& rhs);

    int32_t operator()(int32_t x) const override;
    bool isDefinedAt(int32_t x) const override;
    PartialFunction* clone() const override;
};
/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

 MY PARTIALFUNCTIONCRITERIA`s constructor does exactly what the homework requests:
 Частична функция по критерий – в конструктора се подава функция (това е функция или обект, който
 се държи като такава), която по подадено ѝ като аргумент число, връща наредена двойка -
 дали функцията е дефинирана там и ако да,
 какъв е резултатът.

 Написано е всякаш функцията, която се подавам в конструктора на partialFunctionCriteria е
 функцията, която при подадено число връща pair.

 Toва и направих, сега каквото и да се подадено в конструктора на partialFunctionCriteria, то се конвъртва към
 функция/обект, който връща pair :)

 Moже и да не е била таква идеята, но това е написано в условието.

 Ако беше написано

 Частична функция по критерий – в конструктора се подава функция (това е функция или обект, който
 се държи като такава). Частична функция по критерий по подадено ѝ като аргумент число, връща наредена двойка -
 дали функцията е дефинирана там и ако да,
 какъв е резултатът.

 Щеше да е по-ясно.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   */
template <class T>
PartialFunctionCriteria<T>::PartialFunctionCriteria(const ImpersonateFunction<T>& rhs) : criteria(rhs) {}

template <class T>
PartialFunctionCriteria<T>::PartialFunctionCriteria(ImpersonateFunction<T>&& rhs) : criteria(std::move(rhs)) {}



template <class T>
int32_t PartialFunctionCriteria<T>::operator()(int32_t x) const {
    return criteria(x).result;
}

template <class T>
bool PartialFunctionCriteria<T>::isDefinedAt(int32_t x) const {
    try {
        criteria(x);
        return true;
    }
    catch (...) {
        return false;
    }
}

template <class T>
PartialFunction* PartialFunctionCriteria<T>::clone() const {
    return new PartialFunctionCriteria(*this);
}
