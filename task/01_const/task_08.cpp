#include <string>
#include <vector>
#include <memory>
#include <iostream>

// Task 8: Const указатели и ссылки в сложных сценариях + West const vs East const
//
// Реализуй функции, которые демонстрируют правильное использование const с указателями
// и ссылками в различных сценариях. Пойми разницу между:
// - const T* vs T* const vs const T* const
// - const T& vs T&
// - West const (int const*) vs East const (const int*)
// - Когда использовать каждый вариант
//
// Требования:
// 1. Функция, принимающая указатель на const данные (используй East const)
// 2. Функция, принимающая const указатель (редко, но пойми это)
// 3. Функция, принимающая const указатель на const данные
// 4. Функция, принимающая const ссылку
// 5. Функция, возвращающая const ссылку vs non-const ссылку
// 6. Продемонстрируй эквивалентность West const и East const

class Data {
    int value_;
    std::string name_;

public:
    Data(int v, std::string n) : value_(v), name_(std::move(n)) {}
    
    int getValue() const { return value_; }
    void setValue(int v) { value_ = v; }
    const std::string& getName() const { return name_; }
};

// TODO: Implement function taking pointer to const data (East const style)
// Can't modify *ptr, but can change ptr itself
void processConstData(const Data* ptr) {
    // TODO: implement - can read but not modify
    // Can we do: ptr = nullptr? Yes, ptr itself is not const
}

// TODO: Implement equivalent function using West const style
// Data const* is equivalent to const Data* (East const)
void processConstDataWest(Data const* ptr) {
    // TODO: implement - same as above, just different style
    // Demonstrate that West const and East const are equivalent
}

// TODO: Implement function taking const pointer
// Can't change ptr itself, but can modify *ptr (if data is not const)
void processConstPointer(Data* const ptr) {
    // TODO: implement - can modify *ptr but not ptr
    // Can we do: ptr = nullptr? No, ptr is const
}

// TODO: Implement function taking const pointer to const data
// Can't change ptr or *ptr
void processConstPointerToConst(const Data* const ptr) {
    // TODO: implement - can only read
}

// TODO: Implement function taking const reference
// Most common pattern for read-only access
void processConstReference(const Data& ref) {
    // TODO: implement - can read but not modify
}

// TODO: Implement function returning const reference to internal data
// Protects internal data from modification
class Container {
    std::vector<Data> data_;

public:
    void add(const Data& d) { data_.push_back(d); }
    
    // Return const reference - protects internal data
    const Data& get(size_t index) const {
        // TODO: implement
        static const Data dummy(0, "");
        return dummy;
    }
    
    // Return non-const reference - allows modification
    Data& getMutable(size_t index) {
        // TODO: implement
        static Data dummy(0, "");
        return dummy;
    }
};

void testConstPointersAndRefs() {
    Data d1(10, "one");
    Data d2(20, "two");
    const Data d3(30, "three");
    
    Data* ptr1 = &d1;
    const Data* ptr2 = &d2;           // East const
    Data const* ptr2_west = &d2;      // West const - equivalent to East const
    Data* const ptr3 = &d1;
    const Data* const ptr4 = &d3;
    Data const* const ptr4_west = &d3;  // West const style
    
    // These should compile:
    processConstData(ptr1);              // Non-const pointer to non-const data
    processConstData(ptr2);              // Pointer to const data (East const)
    processConstDataWest(ptr2_west);     // Pointer to const data (West const) - equivalent
    processConstPointer(ptr1);           // Const pointer to non-const data
    processConstPointerToConst(ptr2);    // Const pointer to const data
    processConstReference(d1);           // Non-const object
    processConstReference(d3);           // Const object
    
    // Demonstrate equivalence of West and East const
    // Both styles compile and work the same way
    const Data* east_ptr = &d2;
    Data const* west_ptr = &d2;
    // east_ptr and west_ptr are equivalent
    
    Container container;
    container.add(d1);
    container.add(d2);
    
    const Container& const_container = container;
    const Data& ref1 = const_container.get(0);  // Const reference
    Data& ref2 = container.getMutable(0);       // Non-const reference
    
    // These should NOT compile:
    // processConstPointer(ptr2);                 // Error: can't pass const Data* to Data* const
    // processConstReference(d3).setValue(100);   // Error: can't modify through const reference
    // const_container.getMutable(0);              // Error: can't call non-const method on const object
}

int main() {
    testConstPointersAndRefs();
    return 0;
}

