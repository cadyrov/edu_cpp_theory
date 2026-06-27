#include <iostream>
#include <memory>
#include <vector>

#include <iostream>
#include <utility>

struct X {
    X(int in) {
        ref_ = new int(in);
        std::cout << in << " default ctor\n";
    }

    X(const X& other) {
        if (other.ref_ != nullptr) {
            ref_ = new int(*other.ref_);

            std::cout << *other.ref_ << " copy ctor\n";
        }
        
        std::cout << "copy ctor\n";
    }

    X(X&& other) noexcept {
        ref_ = other.ref_;
        other.ref_ = nullptr;

        std::cout << "move ctor\n";
    }

    X& operator=(const X& other) {
        if (this != &other) {
            delete ref_;
            ref_ = new int(*other.ref_);

            std::cout << *other.ref_ << " copy assignment\n";
        }

        return *this;
    }

    X& operator=(X&& other) noexcept {
        if (this != &other) {
            delete ref_;
            ref_ = other.ref_;
            other.ref_ = nullptr;

            std::cout << "move assignment\n";
        }

        return *this;
    }

    ~X() {
        if (ref_ != nullptr) {
            std::cout << *ref_ << " ";
        }

        delete ref_;

        std::cout << "dtor\n";
    }

    int* ref_;
};
    
int main() {
    X a(1);
    X b = a;
    std::move(a);
    std::cout << *a.ref_ << "end of main\n";
    X c(2);
    c = a;
    c = std::move(a);
    
    X d = X(4);

    std::cout << *a.ref_ << "end of main\n";
}


