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
    UniqueBuffer(const UniqueBuffer& other) = delete;
    // TODO: delete copy assignment
    UniqueBuffer& operator=(const UniqueBuffer& other) = delete;
    // TODO: реализуйте move constructor
    UniqueBuffer(UniqueBuffer&& other) {
        // TODO: реализуйте
    }
    // TODO: реализуйте move assignment
    UniqueBuffer& operator=(UniqueBuffer&& other) {
        // TODO: реализуйте
        return *this;
    }

    void swap(UniqueBuffer& other) {
        std::swap(buffer_, other.buffer_);
        std::swap(size_, other.size_);
    }

    ~UniqueBuffer() {
        delete[] buffer_;
    }
    
    char* data() { return buffer_; }
    size_t size() const { return size_; }
};

void testUniqueBuffer() {
    UniqueBuffer buf1(100);
    
    UniqueBuffer buf2(std::move(buf1));
    assert(buf2.size() == 100);
    
   // UniqueBuffer buf3 = buf1;  // Error!
    
    std::cout << "UniqueBuffer tests passed!\n";
}

int main() {
    testUniqueBuffer();
    return 0;
}
