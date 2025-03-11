#pragma once
#include <iostream>
#include "ModifiableIntegerFunction.h"

//Sys sydeistvieto na: ivailo asparuhov

int main()
{

    ModifiableIntegerFunction myTest([](int16_t x) -> int16_t { return x*10; });
    ModifiableIntegerFunction myTest2(myTest);
    myTest2.setNan(10);
    std::cout << (myTest2(10)) << std::endl; //should print Error
    std::cout << (myTest2 + myTest)(10) << std:: endl; // + and - WORKS ON A FUNCTION LEVEL, OTHERWISE it would have returned an error as if most people would just calculate f(x) and g(x) and then just return it
    std::cout << (myTest2 - myTest)(10)<<std::endl; // - should return 0 because they are copies of one another
    myTest2.setNan(myTest(10));
    std::cout << (myTest2(myTest(10)))<<std::endl; //composition - should print error
    std::cout << (myTest < myTest2); // is false

    ModifiableIntegerFunction Test3([](int16_t x)->int16_t { return x+2; });
    ModifiableIntegerFunction Test4([](int16_t x)->int16_t { return x+3; });
    std::cout << "\nUSPOREDNI: " << (Test3||Test4); //should print true

    ModifiableIntegerFunction Test5([](int16_t x)->int16_t { return x; });
    //std::cout <<'\n'<< (Test5^2)(3); //16

    //std::cout<<'\n' << (~Test5)(5); //1 because = 1/(x+1) and x=0

    //std::cout << '\n' << (Test5.isInection());
   // std::cout << '\n' << (Test5.isSurection());
   // std::cout << '\n' << (Test5.isBijection());

    
    std::cout << '\n';
    Test5.printGraph(0, 0);
    std::cout << '\n';
    Test5.printGraph(2, 2); //doesnt work quite well
    

}

