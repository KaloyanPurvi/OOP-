
#include <iostream>
using namespace std;

struct Point {
    double x;
    double y;
};

struct Line {
    Point firstPoint;
    Point secondPoint;
};

double getDistanceX(const Point& start, const Point& finish) {
    return fabs(start.x - finish.x);
}
double getDistanceY(const Point& start, const Point& finish) {
    return fabs(start.y - finish.y);
}

double getLineLenght(const Line& myLine) {
    double sideA = getDistanceX(myLine.firstPoint, myLine.secondPoint);
    double sideB = getDistanceY(myLine.firstPoint, myLine.secondPoint);

    return sqrt(sideA * sideA + sideB * sideB);
}

void printPoint(const Point& p) {
    cout << "(" << p.x << "," << p.y<<")"; // we should finish
    // try and print the results points
}

void printResult(const Line& myLine) {
    double result = getLineLenght(myLine);
    cout << " P1"; printPoint(myLine.firstPoint);
    cout << " P2"; printPoint(myLine.secondPoint);
    cout << " - "<<result;
}

int main()
{
    Line myLine{ 1,2 , 2, 1 };
    printResult(myLine);
}

