
#include <iostream>
#include "String.h"

void copyDynArr(char* destination, const char* origin) {
	destination = new char[strlen(origin) + 1];
	strcpy(destination, origin);
}

MyString& MyString::operator=(const MyString& other) {
	if (&other != this) {
		free();
		copyFrom(other);
	}
	return *this;
}

MyString::MyString(const MyString& other) {
	copyFrom(other);
}

MyString::MyString() {
	_arr = new char[1];
}

void MyString::free() {
	delete[] _arr;
	_capacity = 0;
	_size = 0;
}
MyString::~MyString() {
	free();
}
MyString::MyString(const char* other): _arr(setDefaultStr()) {
	if (other!=nullptr) {
	copyDynArr(_arr, other);
	_capacity = strlen(other);
	_size = _capacity;
	}
	
}

void MyString::copyFrom(const MyString& other) {
	copyDynArr(_arr, other._arr);
	_capacity = other._capacity;
	_size = other._size;
};


unsigned MyString::capacity() const
{
	return 0;
}

char* MyString::setDefaultStr()
{
	char* _arrDefault = new char[1];
	return _arrDefault;
}



char MyString::at(unsigned index) const {
	if (index >= _capacity) {
		return '\0';
	}
	return _arr[index];
}

char MyString::front() const {
	return _arr[0];
}
char MyString::back() const {
	return _arr[_size];
}
const char* MyString::str() const{
	return _arr;
}

unsigned MyString::lenght() const {
	return _size;
}
unsigned MyString::capacity() const {
	return _capacity;
}

bool MyString::empty() const {

	return (strcmp(_arr,"")==0);
}
void MyString::resize(size_t newSize) { //we only add size whist we keep the string so far
	char* keep = _arr;
	_arr = new char[newSize + 1];
	strcpy(_arr, keep);
	_capacity = newSize;
	delete[] keep;

}
void MyString::append(char ch) {
	if (_size == _capacity) {
		resize(_capacity << 2);
	}
	_size++;
	_arr[_size] = ch;
}

void MyString::append(const char* ch) {
	if (_size == _capacity) {
		resize(_capacity+strlen(ch)+1);
	}
	_size+= strlen(ch);
	strcat(_arr, ch);
}
void MyString::clear() {
	for (int i = 0; i < _size; i++) {
		_arr[i] = '\0';
	}
	_size = 0;
}
bool MyString::equals(const char* ch) const {
	return strcmp(_arr, ch) == 0;
}

int MyString::find(char ch) const{
	for (int i = 0; i < _size; i++) {
		if (_arr[i] == ch)
			return i;
	}
	return -1;
}
