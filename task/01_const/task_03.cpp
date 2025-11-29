#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

// Task 3: Const-correct реализация итераторов
//
// Реализуй класс Container, который предоставляет const и non-const итераторы
// с правильной const-correctness. Класс должен поддерживать range-based for циклы
// для const и non-const объектов.
//
// Требования:
// 1. Non-const begin()/end() возвращают non-const итераторы
// 2. Const begin()/end() возвращают const итераторы
// 3. cbegin()/cend() возвращают const итераторы (даже для non-const объектов)
// 4. Range-based for должен корректно работать для const и non-const объектов

template<typename T>
class Container {
    std::vector<T> data_;

public:
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    
    Container(std::initializer_list<T> init) : data_(init) {}
    
    // TODO: Implement non-const begin() and end()
    iterator begin() {
        // TODO: implement
    }
    
    iterator end() {
        // TODO: implement
    }
    
    // TODO: Implement const begin() and end()
    const_iterator begin() const {
        // TODO: implement
    }
    
    const_iterator end() const {
        // TODO: implement
    }
    
    // TODO: Implement cbegin() and cend() (always const)
    const_iterator cbegin() const {
        // TODO: implement
    }
    
    const_iterator cend() const {
        // TODO: implement
    }
    
    size_t size() const { return data_.size(); }
};

void testContainer() {
    Container<int> container{1, 2, 3, 4, 5};
    const Container<int>& const_container = container;
    
    // These should compile:
    for (auto& item : container) {
        item *= 2;  // Modify through non-const iterator
    }
    
    for (const auto& item : const_container) {
        std::cout << item << " ";  // Read through const iterator
    }
    std::cout << "\n";
    
    // These should NOT compile:
    // for (auto& item : const_container) {
    //     item *= 2;  // Error: cannot modify through const iterator
    // }
    
    // These should work (cbegin/cend always return const iterators):
    for (auto it = container.cbegin(); it != container.cend(); ++it) {
        std::cout << *it << " ";  // OK: reading
        // *it = 10;               // Error: cannot modify through const iterator
    }
}

int main() {
    testContainer();
    return 0;
}

