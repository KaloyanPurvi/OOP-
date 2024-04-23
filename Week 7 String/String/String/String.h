#pragma once
class MyString
{
	char* _arr;
	size_t _size = 0;
	size_t _capacity = 0; //"хубаво е да се увеличава с Pow 2, кoгато е нужно"
public:
	MyString();
	char at(unsigned index) const;
	char front() const;
	char back() const;
	const char* str() const;
	unsigned lenght() const;
	unsigned capacity() const;
	char* setDefaultStr();	
	bool empty() const;
	void append(char ch);
	void append(const char* ch);
	void clear(); //ne promenq capacity-to
	bool equals(const char* ch) const;
	int find(char ch) const;
	
	~MyString();
	MyString& operator=(const MyString& other);
	MyString(const MyString& other);
	MyString(const char* other);

private:
	void resize(size_t newSize);
	void copyFrom(const MyString& other);
	void free();
};

