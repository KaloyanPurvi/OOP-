#include <iostream>

void copyDynCharArr(char* destination, const char* origin) {
	if (!origin || destination == origin) {
		return;
	}
	destination = new char[strlen(origin) + 1];
	strcpy(destination, origin);
}

class Student {
	char* _name = nullptr;
public:
	void setName(const char* name) {
		copyDynCharArr(_name, name);
	}
	const char* getName() const {
		return _name;
	}
	~Student(){
		delete[] _name;
	}
};

int main() {
	Student st1;
	st1.setName("pyrvi");
	char* setter = st1.getName(); //here we see that this will only work if 'setter' is const

	Student st2;
	st2.setName(setter);
	std::cout << st2.getName(); 
}