#include <iostream>

// Class that implements RAII (Resource Acquisition is Initialization)
class IntArr {
  size_t _arrSize;
  int* _arr;

 public:
  IntArr(size_t arrSize) : _arrSize(arrSize), _arr(new int[arrSize]) {
    std::cout << "Constructor triggered - Int Array" << std::endl;
    for (int i = 0; i < arrSize; i++) {
      _arr[i] = 0;
    }
  }

  ~IntArr() {
    std::cout << "Destructor triggered - Int Array" << std::endl;
    delete[] _arr;
  }

  int getItem(size_t index) { return _arr[index]; }

  void setItem(size_t index, int value) { _arr[index] = value; }

  void print() {
    for (int i = 0; i < _arrSize; i++) {
      std::cout << i << " " << _arr[i] << std::endl;
    }
  }
};

// Class that implements the same, but with a generics instead.
template <class T>
class DynamicArray {
  size_t _arrSize;
  T* _arr;

 public:
  DynamicArray(size_t arrSize) : _arrSize(arrSize), _arr(new T[arrSize]) {
    std::cout << "Constructor triggered - Dynamic Array" << std::endl;
  }

  ~DynamicArray() {
    std::cout << "Destructor triggered - Dynamic Array." << std::endl;
    delete[] _arr;
  }

  T getItem(size_t index) { return _arr[index]; }

  size_t getSize() { return _arrSize; }

  void setItem(size_t index, T value) { _arr[index] = value; }

  void print() {
    for (int i = 0; i < _arrSize; i++) {
      std::cout << i << " " << _arr[i] << std::endl;
    }
  }
};
