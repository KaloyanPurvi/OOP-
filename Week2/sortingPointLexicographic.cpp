#include <iostream>
using namespace std;

struct Point {
	int x;
	int y;
};

void swapStruct(Point& A, Point& B) {
	Point temp = A;
	A = B;
	B = temp;
}

void sortPointersLexicographicly(Point* pointsArr, size_t size) {
	//we use selection sort because we want as little swaps as possible
	for (int i = 0; i < size; i++) {
		int minIndex = i;
		for (int j = i + 1; j < size; j++) {
			if (arr[j] < arr[minIndex]) { //here i need to figure this out but i have uni tomorrow so gn
				minIndex = j;
			}
		}
		if (minIndex != i) {
			swapStruct(arr[i], arr[minIndex]);
		}
	}
}

int main() {

}