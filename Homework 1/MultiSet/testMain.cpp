#pragma once
#include "MultiSet.h"

void testDifference() {
	MultiSet obj1(5, 3);
	obj1.add(2);
	obj1.add(2);
	obj1.add(5);

	MultiSet obj2(6, 2);
	obj2.add(3);
	obj2.add(3);
	obj2.add(3);

	DifferenceOfSets(obj1, obj2).printNumbers(); //Should print all numbers
}


void testIntersections() {
	MultiSet obj1(5, 3);
	obj1.add(2);
	obj1.add(2);
	obj1.add(5);

	MultiSet obj2(6, 2);
	obj2.add(3);
	obj2.add(3);
	obj2.add(3);
	
	IntersectionOfSets(obj1, obj2).printNumbers(); //Should print the empty set because nothing matches
}


void addMoreThanCapacityK() {
	MultiSet obj1(5, 3);
	obj1.add(2);
	obj1.add(2);

	obj1.add(4);

	obj1.add(2);
	obj1.add(2);
	obj1.add(2);
	obj1.add(2);
	obj1.add(2); //so far we have 7 times 2 and 1 time 4
	//and and if we add another one here it should tell you to stop:
	obj1.add(2);
}

void testPrintBinary() {
	MultiSet obj1(5, 3);
	obj1.add(2);
	obj1.add(2);
	obj1.add(3);
	obj1.add(1);
	obj1.printBinary();
	// should print:                                 00000101 00010000 00000000
    //here is the space for each number because:     00011122 23334445 55
	//works fine
}

void testCompliment() {
	MultiSet obj1(5, 3);
	obj1.add(2);
	obj1.add(2);
	obj1.add(3);
	obj1.add(1);
	std::cout << "Original is: "; 
	obj1.printBinary();
	std::cout << "\nFlipped  is: ";
	compliment(obj1).printBinary();
	//the original obj1 should print:                                 00000101 00010000 00000000
	//Our function should print                                       11111010 11101111 11111111
	//works fine
}

void testReadAndWrite() {
	MultiSet obj1(4, 2);
	obj1.add(1);
	obj1.add(1);
	obj1.add(4);
	obj1.writeToFile("test1.txt"); //also i created << operator
	MultiSet obj2;
	obj2.readFromFile("test1.txt"); // >> operator
	std::cout << "Original is: ";
	obj1.printBinary();
	std::cout << "\n Readed  is: ";
	obj2.printBinary();
}


int main()
{


}
