#include <iostream>
#include <cassert>
#include <memory>

// Task 8: Move-only класс (не копируемый)
//
// Реализуйте класс UniqueBuffer, который:
// - Не копируется (delete copy constructor и assignment)
// - Может перемещаться
// - Автоматически освобождает память в деструкторе

class UniqueBuffer {
    char* buffer_;
    size_t size_;
public:
    UniqueBuffer(size_t size) : size_(size) {
        buffer_ = new char[size];
    }
    
    // TODO: delete copy constructor
    // TODO: delete copy assignment
    
    // TODO: реализуйте move constructor
    // TODO: реализуйте move assignment
    
    ~UniqueBuffer() {
        delete[] buffer_;
    }
    
    char* data() { return buffer_; }
    size_t size() const { return size_; }
};

void testUniqueBuffer() {
    UniqueBuffer buf1(100);
    
    // TODO: UniqueBuffer buf2(std::move(buf1));
    // TODO: assert(buf2.size() == 100);
    
    // TODO: Проверьте что копирование запрещено (не компилируется)
    // UniqueBuffer buf3 = buf1;  // Error!
    
    std::cout << "UniqueBuffer tests passed!\n";
}

int main() {
    testUniqueBuffer();
    return 0;
}
