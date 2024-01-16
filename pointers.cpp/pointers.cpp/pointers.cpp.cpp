#include <iostream>

void printRef(int& i) {
	std::cout << &i << " " << i << " " << sizeof(i) << std::endl;
}

void printCopy(int x) {
	std::cout << &x << " " << x << " " << sizeof(x) << std::endl;
}

int main() {
	int a = 10;
	int b = 12;
	int* pa = &a;
	int* pb = &b;

	// Reference of value. (Passed by reference)
	printRef(a);
	printRef(b);
	std::cout << std::endl;

	*pa = 56;
	printRef(a);
	printRef(b);
	std::cout << std::endl;
	
	*pb = 99;
	printRef(a);
	printRef(b);
	std::cout << std::endl;

	// Copy of value. (Passed by value)
	// Same memory address.
	printCopy(a);
	printCopy(b);
	std::cout << std::endl;

	return 0;
}