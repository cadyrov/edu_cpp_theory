#include <algorithm>
#include <iostream>
#include <cassert>
#include <string>
#include <memory>

// Task 5: std::move и передача владения
//
// Реализуйте класс Resource, который управляет ресурсом через std::move:
// - Нельзя копировать
// - Можно перемещать
// - После перемещения исходный объект не владеет ресурсом

class Resource {
    int* data_;
    bool owns_;
public:
    Resource(int value) : owns_(true) {
        data_ = new int(value);
    }
    
    // TODO: delete copy constructor и copy assignment
    Resource(const Resource& other) = delete;
    Resource& operator=(const Resource& other) = delete;
    
    // TODO: реализуйте move constructor и move assignment
    Resource(Resource&& other) noexcept {
        data_ = other.data_;
        owns_ = true;
        other.data_ = nullptr;
        other.owns_ = false;
    }

    Resource& operator=(Resource&& other) noexcept {
        Resource temp(std::move(other));
        swap(temp);
        return *this;
    }
    
    void swap(Resource& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(owns_, other.owns_);
    }

    ~Resource() {
        if (owns_) delete data_;
    }
    
    int getValue() const { return *data_; }
};

void testResourceMove() {
    Resource r1(42);
    
    Resource r2(std::move(r1));
    assert(r2.getValue() == 42);
    
    std::cout << "Resource move tests passed!\n";
}

int main() {
    testResourceMove();
    return 0;
}
