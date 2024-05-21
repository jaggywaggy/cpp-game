#include <iostream>

#include "raii.cpp"

void printRef(int &i) {
  std::cout << &i << " " << i << " " << sizeof(i) << std::endl;
}

void printCopy(int x) {
  std::cout << &x << " " << x << " " << sizeof(x) << std::endl;
}

int main() {
  int a = 10;
  int b = 12;

  // Assign a pointer to an integer.
  // int pointer to the address of a/b.
  int *pa = &a;
  int *pb = &b;

  // Reference of value. (Passed by reference)
  printRef(a);
  printRef(b);
  std::cout << std::endl;

  // Assign the value 56 to the address of a.
  *pa = 56;
  printRef(a);
  printRef(b);
  std::cout << std::endl;

  // Assign the value 56 to the address of b.
  *pb = 99;
  printRef(a);
  printRef(b);
  std::cout << std::endl;

  // Copy of value. (Passed by value)
  // Same memory address.
  printCopy(a);
  printCopy(b);
  std::cout << std::endl;

  // Create our RAII int array.
  IntArr arr(10);
  arr.setItem(4, 12);
  arr.setItem(8, 89);
  arr.print();

  // Create our RAII dynamic array.
  DynamicArray<float> dynarr1(20);
  for (int i = 0; i < dynarr1.getSize(); i++) {
    dynarr1.setItem(i, 0);
  }
  dynarr1.setItem(18, 51.2);
  dynarr1.setItem(5, 163.1);
  dynarr1.print();

  // Create another RAII dynamic array.
  DynamicArray<std::string> dynarr2(11);
  for (int i = 0; i < dynarr2.getSize(); i++) {
    dynarr2.setItem(i, "");
  }
  dynarr2.setItem(9, "A Value");
  dynarr2.setItem(5, "Another Value");
  dynarr2.print();

  return 0;
}
