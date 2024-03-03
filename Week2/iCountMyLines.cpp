#include <iostream>
#include <fstream>
#include<assert.h>
using namespace std;

int getLinesCount(ifstream& myFile) {
    if (!myFile.is_open()) {
        return -1;
    }
    int result = 0;
    while (true) {
        char str[1000];
        myFile.getline(str,1000);
        result++;
        if (myFile.eof()) return result;
       
    }

}

int main()
{
    ifstream myFile("C:\\Users\\ion computers\\Desktop\\iCountMyLines\\readme.txt");
    ifstream myFile2("iCountMyLines.cpp");
    cout << getLinesCount(myFile);
    myFile.close();
}

