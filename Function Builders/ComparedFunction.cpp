#pragma once
#include "ComparedFunction.h"

void ComparedFunction::free()
{
    for (int i = 0; i < size; i++) {
        delete[] funcArray[i];
    }
    delete[] funcArray;
}


ComparedFunction::ComparedFunction(const PartialFunction* const* arr, size_t size) {
    funcArray = new PartialFunction * [size];
    this->size = size;
    for (int i = 0; i < size; i++) {
        funcArray[i] = arr[i]->clone();
    }
}

ComparedFunction& ComparedFunction::operator=(const ComparedFunction& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}
ComparedFunction& ComparedFunction::operator=(ComparedFunction&& other)
{
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

void ComparedFunction::copyFrom(const ComparedFunction& other) {
    funcArray = new PartialFunction * [other.size];
    size = other.size;
    for (size_t i = 0; i < size; i++) {
        funcArray[i] = other.funcArray[i]->clone();
    }
}

void ComparedFunction::moveFrom(ComparedFunction&& other)
{
    funcArray = other.funcArray;
    other.funcArray = nullptr;
    size = other.size;
    other.size = 0;
}

ComparedFunction::ComparedFunction(const ComparedFunction& other) {
    copyFrom(other);
}

ComparedFunction::ComparedFunction(ComparedFunction&& other)
{
    moveFrom(std::move(other));
}



bool ComparedFunction::isDefinedAt(int32_t x) const
{
    for (int i = 0; i < size; i++) {
        if (!(*funcArray[i]).isDefinedAt(x))
            return false;
    }
    return true; //rwar ;)
}

ComparedFunction::~ComparedFunction()
{
    free();
}