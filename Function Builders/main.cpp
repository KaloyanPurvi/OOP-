#include <cstdint>
#include <iostream>
#include <fstream>
#include "MyString.h"
#include "MinimumFunction.h"
#include "MaximumFunction.h"
#include "PartialFunction.h"
#include "PartialFunctionCriteria.hpp"
// HEADER PartialFunction.h

class FunctionReader {
    PartialFunction* ptr;
    void read(std::ifstream& ifs);
public:
    FunctionReader(const char* fileName);
    FunctionReader(std::ifstream& ifs);

    int32_t operator()(int32_t x) const;
}; 

int32_t FunctionReader::operator()(int32_t x) const {
    return ptr->operator()(x);
}


void FunctionReader::read(std::ifstream& ifs) {
    uint16_t N, T;
    ifs.read((char*)&N, sizeof(N));
    ifs.read((char*)&T, sizeof(T));
    int32_t* N1 = new int32_t[N];
    int32_t* N2;
    switch (T) {
    case 0:
        N2 = new int32_t[N];
        ifs.read((char*)&N1, sizeof(N1) * N);
        ifs.read((char*)&N2, sizeof(N2) * N);
        ptr = new FunctionType0(N1, N2, N);
    case 1:
        ifs.read((char*)&N1, sizeof(N1) * N);
        ptr = new FunctionType1(N1, N);
    case 2:
        ifs.read((char*)&N1, sizeof(N1) * N);
        ptr = new FunctionType2(N1, N);
    default:
        ptr = nullptr;
    }
}
FunctionReader::FunctionReader(std::ifstream& ifs) {  //we did an overloading function just in case
    read(ifs);
}

FunctionReader::FunctionReader(const char* file) {
    std::ifstream ifs(file, std::ios::binary);
    read(ifs);
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++     functionTYPE 0       +++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class FunctionType0 : public PartialFunction {
    int32_t args[32];
    int32_t res[32];
    uint16_t size;
public:
    FunctionType0(const int32_t* arguments, const int32_t* results, uint16_t n) : size(n) {
        for (int i = 0; i < size; i++) {
            args[i] = arguments[i];
            res[i] = results[i];
        }
    }
    int32_t operator()(int32_t x) const override {
        for (int i = 0; i < size; i++) {
            if (args[i] == x) {
                return res[i];
            }
        }
        throw std::runtime_error("Function not defined at this point");
    }
    bool isDefinedAt(int32_t x) const override {
        for (int i = 0; i < size; i++) {
            if (args[i] == x) {
                return true;
            }
        }
        return false;
    }
    PartialFunction* clone() const override {
        return new FunctionType0(*this);
    }
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++     functionTYPE 1       +++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class FunctionType1 : public PartialFunction {
    int32_t undefined[32];
    uint16_t size;
public:
    //we dont want a def constructor
    FunctionType1(const int32_t* arguments, uint16_t n) : size(n) {
        for (int i = 0; i < size; i++) {
            undefined[i] = arguments[i];
        }
    }
    int32_t operator()(int32_t x) const override {
        for (int i = 0; i < size; i++) {
            if (undefined[i] == x) {
                throw std::runtime_error("Function not defined at point");
            }
        }
        return x;
    }
    bool isDefinedAt(int32_t x) const override {
        for (int i = 0; i < size; i++) {
            if (undefined[i] == x) {
                return false;
            }
        }return true;
    }
    PartialFunction* clone() const override {
        return new FunctionType1(*this);
    }
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++     functionTYPE 3       +++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class FunctionType2 : public PartialFunction {
    int defined[32];
    int size;
public:
    FunctionType2(const int* arguments, int n) : size(n) {
        for (int i = 0; i < size; i++) {
            defined[i] = arguments[i];
        }
    }
    int32_t operator()(int32_t x) const override {
        for (int i = 0; i < size; i++) {
            if (defined[i] == x) {
                return 1;
            }
        }
        return 0;
    }
    bool isDefinedAt(int32_t x) const override {
        return true;
    }
    PartialFunction* clone() const override {
        return new FunctionType2(*this);
    }
};

// (((((((FACTORY)))))))))))))))))))))))))))))))))))))))))))))))))))))

PartialFunction* factory(std::ifstream& ifs){
    uint16_t N, T;
    ifs.read((char*)&N, sizeof(N));
    ifs.read((char*)&T, sizeof(T));
    int32_t* N1 = new int32_t[N];
    int32_t* N2;
    switch (T) {
        case 0:
            N2=new int32_t[N];
            ifs.read((char*)&N1, sizeof(N1)*N);
            ifs.read((char*)&N2, sizeof(N2)*N);
            return new FunctionType0(N1,N2,N);
        case 1:
            ifs.read((char*)&N1, sizeof(N1) * N);
            return new FunctionType1(N1, N);
        case 2:
            ifs.read((char*)&N1, sizeof(N1) * N);
            return new FunctionType2(N1, N);
        default:
            return nullptr;
    }// would return nullptr if T is above 4
};


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

int main() {
    firstTest();
    /*
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  
  MY PARTIALFUNCTIONCRITERIA`s constructor does exactly what the homework requests:
  Частична функция по критерий – в конструктора се подава функция (това е функция или обект, който 
  се държи като такава), която по подадено ѝ като аргумент число, връща наредена двойка -
  дали функцията е дефинирана там и ако да, 
  какъв е резултатът.

  Написано е всякаш функцията, която се подавам в конструктора на partialFunctionCriteria е 
  функцията, която при подадено число връща pair. 

  Moже и да не е била таква идеята, но това е написано в условието.

  Ако беше написано 

  Частична функция по критерий – в конструктора се подава функция (това е функция или обект, който
  се държи като такава). Частична функция по критерий по подадено ѝ като аргумент число, връща наредена двойка -
  дали функцията е дефинирана там и ако да,
  какъв е резултатът.

  Щеше да е по-ясно.

 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   
    
    */

    /*
    MyString str, str2;
    std::ifstream ifs("Test.dat", std::ios::binary);
    str = readFromBinaryWithZeroes(ifs);
    std::cout << str;
    */

    //PartialFunction* result =readFromFile("func.dat");
  //  delete[] result;
}
