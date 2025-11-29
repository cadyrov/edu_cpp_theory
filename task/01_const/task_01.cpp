#include <vector>
#include <stdexcept>
#include <iostream>

// Task 1: Const-correct operator[] с проверкой границ
//
// Реализуй класс SafeArray, который предоставляет const и non-const версии
// operator[] с правильной const-correctness. Const версия должна возвращать
// const ссылку и бросать исключение при выходе за границы, а non-const версия
// должна позволять модификацию, но также бросать исключение при выходе за границы.
//
// Требования:
// 1. Non-const operator[] возвращает non-const ссылку
// 2. Const operator[] возвращает const ссылку
// 3. Обе версии выполняют проверку границ
// 4. Const версия может быть вызвана на const объектах
// 5. Non-const версия не может быть вызвана на const объектах

class SafeArray {
    std::vector<int> data_;

public:
    SafeArray(std::initializer_list<int> init) : data_(init) {}
    
    // TODO: Implement non-const operator[]
    // Should return non-const reference, allow modification
    int& operator[](size_t index) {
        // TODO: implement bounds checking and return reference
    }
    
    // TODO: Implement const operator[]
    // Should return const reference, prevent modification
    const int& operator[](size_t index) const {
        // TODO: implement bounds checking and return const reference
    }
    
    size_t size() const { return data_.size(); }
};

void testSafeArray() {
    SafeArray arr{1, 2, 3, 4, 5};
    const SafeArray& const_arr = arr;
    
    // These should compile and work:
    arr[0] = 10;                    // Modify through non-const version
    int val = const_arr[0];         // Read through const version
    std::cout << "Value: " << val << "\n";
    
    // These should NOT compile:
    // const_arr[0] = 20;            // Error: cannot modify through const reference
    // int& ref = const_arr[0];      // Error: cannot bind const reference to non-const reference
    
    // These should throw std::out_of_range:
    // arr[100];                     // Out of bounds
    // const_arr[100];               // Out of bounds
}

int main() {
    testSafeArray();
    return 0;
}

