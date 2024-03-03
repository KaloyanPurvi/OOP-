#include <iostream>
#include <fstream>
#include <assert.h>
using namespace std;

int main() {
	fstream myFile("iPrintMyCode.cpp");
	if (!myFile.is_open()) {
		return -1;
	}
	while (true) {
		char str[1024];
		myFile.getline(str, 1024);
		if (myFile.eof()) return 0;
		cout << str << endl;
	}
}