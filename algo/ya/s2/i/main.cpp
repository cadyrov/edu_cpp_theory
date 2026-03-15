#include <iostream>
#include <vector>
#include <optional>

template<typename T>
class Queue {
public:
    Queue() = delete;
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
    Queue(Queue&&) = delete;
    Queue& operator=(Queue&&) = delete;

    Queue(size_t size){
        data_.reserve(size);
    }

    bool Push(T&& in) {
        if (size_ == data_.size()) {
            return false;
        }
    
        data_[r_] = std::forward<T>(in);
        r_ = next_r();

        size_++;

        return true;
    }

    size_t Size() const{
        return size_;
    }

    std::optional<T> Peek() const {
        if  (Size() == 0) {
            return std::nullopt;
        }

        return data_[l_];
    }

    std::optional<T> Pop() {
        if  (Size() == 0) {
            return std::nullopt;
        }

        T res = data_[l_];

        l_ = next_l();

        return res;
    }

private:
    size_t next_r() {
        if (data_.size() == 0) {
            return r_;
        }
        return (r_ + 1) % data_.size();
    }

    size_t next_l() {
        if (data_.size() == 0) {
            return l_;
        }

        return (l_ + 1) % data_.size();
    }

    size_t l_ = 0;
    size_t r_ = 0;

    size_t size_ = 0;

    std::vector<T> data_;
};




int main() {




    return 0;
}