// OOP week 2 perry.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;


enum Month:char {
    defaultM=0,
    January=1,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December

};

struct Date {
    Month dateMonth;
    int year;
};

void getMonthToString(Month myMonth) {

    switch (myMonth) {
    case 1: cout << "January";
        break;
    case 2: cout << "February";
        break;
    case 3: cout << "March";
        break;
    case 4: cout << "April";
        break;
    case 5: cout << "May";
        break;
    case 6: cout << "June";
        break;
    case 7: cout << "July";
        break;
    case 8: cout << "August";
        break;
    case 9: cout << "September";
        break;
    case 10: cout << "October";
        break;
    case 11: cout << "November";
        break;
    case 12: cout << "December";
        break;
    default:
        cout << "Problem";
        break;
    }

}

Month getNextMonth(const Month& myMonth) {
    Month newMonth;
    if (myMonth == 12) return January;
    return (Month)(myMonth + 1);
}

Date getNextDate(const Date& currentDate) {

    Date nextDate;
    nextDate.dateMonth = getNextMonth(currentDate.dateMonth);
    
    nextDate.dateMonth = getNextMonth(currentDate.dateMonth);

}

struct Product {
    bool sold;
    int ID;
    double price;
    Date loadDate = {(Month)0,0};
    Date soldDate = { (Month)0,0 };
};

bool areMonthsOkay(const Month& soldMonth, const Month& myMonth) {
    return (soldMonth >= myMonth);
  
}
bool areYearsOkay( int soldYear, int myYear) {
    return (soldYear >= myYear);
}

bool datesOkay(const Date& myDate, const Date& soldDate) {
    if (areYearsOkay(myDate.year,soldDate.year)) {
        if ((myDate.year == soldDate.year) && areMonthsOkay(myDate.dateMonth, soldDate.dateMonth)) {
            return true;
        }
       
        return true;
    }
    return false;
}

void sell(Product& myProduct, const Date& soldDate) {
    if (datesOkay(myProduct.loadDate, soldDate)) {
        myProduct.sold=true;
        return;
    }
    cout << "Error";
    return;
    
}

int main()
{
    
}

