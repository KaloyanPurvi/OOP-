#include<iostream>
#include<fstream>
#include<assert.h>
using namespace std;

enum Errors {
	noFile=-1
};

const char* convertErrorToString(int errorCode) {
	switch (errorCode) {
	case Errors::noFile: return "No File Found";
	}
}

int countCharFromFile(fstream& file, char charToCount) {
	if (!file.is_open()) {
		return -1;
	}
	int result = 0;
	while (!file.eof()) {
		char readed;
		file.get(readed);
		if (readed == charToCount)result++;
	}
	return result;
}
int main() {
	fstream myFile("iCountCharFromFile.cpp");
	cout << countCharFromFile(myFile, '\n');
	myFile.close();
}