#include <iostream>
#include <random>
#include <ctime>
#include "RandomNumberGenerator.h"

struct Point {
	int x;
	int y;
};

class Object {

};

class Pacman {
	char** playfield;
	static unsigned With;
	static unsigned Height;
	Object ghost;
	Object player;

	Pacman(unsigned With, unsigned Height);

};

char** createMaze(unsigned Width, unsigned Height) {
	char** result = new char* [Width];
	//lets initialize the whole matrix
	for (int currentColl = 0;currentColl < Width;currentColl++) {
		result[currentColl] = new char[Height];	
	}
	//now lets set the borders
	for (int currentColl = 0, maxHeight= (Height-1);currentColl < Width;currentColl++) {
		result[currentColl][0] = '#';
		result[currentColl][maxHeight] = '#';
	}
	for (int currentRow = 0, maxWidth = (Width - 1);currentRow < Width;currentRow++) {
		result[0][currentRow] = '#';
		result[maxWidth][currentRow] = '#';
	}

	//lets make some random walls
	RandomNumberGenerator rnd(0,)

	return result;
}

int main() {
	
}