#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <cassert>


template <typename T>
class Deque{
public:
    Deque() = delete;
    Deque(const Deque&) = delete;
    Deque(Deque&&) = delete;
    
    Deque(size_t size){
        data_.resize(size);
        right_ = prev(right_);
    }

    bool PushFront(T value){
        if (size_ == data_.size()) {
            return false;
        }

        data_[left_] = value;
        left_ = next(left_);

        ++size_;

        return true;    
    }

    bool PushBack(T value){
        if (size_ == data_.size()) {
            return false;
        }

        data_[right_] = value;
        right_ = prev(right_);

        ++size_;

        return true;
    }

    

    std::optional<T> PopFront(){
        if (size_ == 0) {
            return std::nullopt;
        }

        left_ = prev(left_);

        --size_;
        
        return data_[left_];
    }

    std::optional<T> PopBack(){
        if (size_ == 0) {
            return std::nullopt;
        }

        right_ = next(right_);

        --size_;
        
        return data_[right_];
    }
private:
    size_t left_ = 0;
    size_t right_=0;
    size_t size_ =0;
    std::vector<T> data_{};

    size_t prev(size_t i){
        return (data_.size() + --i) % data_.size();
    }

    size_t next(size_t i){
        return (data_.size() + ++i) % data_.size();
    }
};

int main() {
    Deque<int> dqt(5);

    assert(dqt.PopFront() == std::nullopt);
    assert(dqt.PopBack() == std::nullopt);
    assert(dqt.PushFront(1) == true);
    assert(dqt.PushFront(2) == true);
    assert(dqt.PopBack() == 1);
    assert(dqt.PopBack() == 2);
    
    int cmds;
    std::cin >> cmds;

    int dsize;
    std::cin >> dsize;
    
    Deque<int> dq(dsize);

    for (int i = 0; i < cmds; ++i) {
        std::string cmd;
        std::cin >> cmd;

        int value;

        if (cmd == "push_back") {
            std::cin >> value;
            if(!dq.PushBack(value)) {
                std::cout << "error\n";
            }
        } else if (cmd == "push_front") {
            std::cin >> value;
            if(!dq.PushFront(value)) {
                std::cout << "error\n";
            }
        } else if (cmd == "pop_back") {
            auto value = dq.PopBack();
            if (value.has_value()) {
                std::cout << value.value() << "\n";
            } else {
                std::cout << "error\n";
            }
        } else if (cmd == "pop_front") {
            auto value = dq.PopFront();
            if (value.has_value()) {
                std::cout << value.value() << "\n";
            } else {
                std::cout << "error\n";
            }
        }
    }

    return 0;
}