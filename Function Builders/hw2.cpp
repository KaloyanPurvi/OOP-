#pragma once
#include <iostream>
#include <fstream>
#include "MyString.h"
#include "MinimumFunction.h"
#include "MaximumFunction.h"
#include "PartialFunction.h"
#include "PartialFunctionCriteria.hpp"
#include "FunctionReader.h"



//++++++++++++++++++++++++++++++++++++++++++++   TESTS    ++++++++++++++++++++++++++++++++++++++++++++++++++++
static const MyString& readFromBinaryWithZeroes(std::ifstream& ifs) {
    char reader = 'A';
    int keeper = ifs.tellg();
    size_t lenght = 0;
    while (!ifs.eof() && reader != '0') {
        ifs.read(&reader, sizeof(reader));
        lenght++;
    }
    char buff[1024];
    ifs.seekg(keeper);
    ifs.read(buff, sizeof(char) * (lenght)); //we want to skip the  0 at the end
    buff[lenght - 1] = '\0'; //yet we dont want to keep it
    MyString res(lenght);
    res = buff;
    return res;
}
//++++++++++++++++++++++++++++++++++++++++++++   TESTS    ++++++++++++++++++++++++++++++++++++++++++++++++++++

int32_t plusOne(int32_t x) {
    return x + 1;
}

int32_t plusTwo(int32_t x) {
    return x + 2;
}

int32_t plusThree(int32_t x) {
    return x + 3;
}

void firstTest() {

    //here i test for shallow copies and overall functionality

    PartialFunction** ptr = new PartialFunction * [3];
    ptr[0] = new PartialFunctionCriteria<int32_t(*)(int32_t)>(plusOne);
    ptr[1] = new PartialFunctionCriteria<int32_t(*)(int32_t)>(plusTwo);
    ptr[2] = new PartialFunctionCriteria<int32_t(*)(int32_t)>(plusThree);

    MaximumFunction test(ptr, 3);
    MinimumFunction test2(ptr, 3);
    std::cout << test(1) << std::endl;
    std::cout << test2(1) << std::endl;

    ptr[0] = new PartialFunctionCriteria<int32_t(*)(int32_t)>(plusThree);
    MinimumFunction test3(ptr + 1, 2);
   test3 = test2; //without this the test3 object begins from 'plusTwo' therefore it is the lowest one and should print x+2
   std::cout << test3(1) << std::endl;

    delete ptr[0];
    delete ptr[1];
    delete ptr[2];
    delete[] ptr;
}

void ProgramType1() {
    int a, b;
    std::cin >> a;
    std::cin >> b;
    FunctionReader function("func.dat");
    while (a <= b) {
        if (function.isDefinedAt(a)) {
            std::cout << " f("<<a <<")= " << function(a);
        }
        a++;
    }
}
void ProgramType2() {
    FunctionReader function("func.dat");
    int x=0;
    do {
        std::cin >> x;
        if (function.isDefinedAt(x)) {
            std::cout << function(x);
        }
    } while (true);
    //its intended to be infinite, it isnt stated when to end
}

int main() {
    firstTest();

    

    /*
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  
  моят ParticularFunctionCriteria`s constructor does exactly what the homework requests:
  Частична функция по критерий – в конструктора се подава функция (това е функция или обект, който 
  се държи като такава), която по подадено ѝ като аргумент число, връща наредена двойка -
  дали функцията е дефинирана там и ако да, 
  какъв е резултатът.

  Написано е всякаш функцията, която се подавам в конструктора на ParticularFunctionCriteria е 
  функцията, която при подадено число връща pair. 

  Moже и да не е била таква идеята, но това е написано в условието.

  Ако беше написано 

  "Частична функция по критерий – в конструктора се подава функция (това е функция или обект, който
  се държи като такава). Частична функция по критерий по подадено ѝ като аргумент число, връща наредена двойка -
  дали функцията е дефинирана там и ако да,
  какъв е резултатът."

  щеше да е по-ясно, но да

 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   
    
    */

    /*Tested something
    MyString str, str2;
    std::ifstream ifs("Test.dat", std::ios::binary);
    str = readFromBinaryWithZeroes(ifs);
    std::cout << str;
    */

    //PartialFunction* result =readFromFile("func.dat");
  //  delete[] result;
}
