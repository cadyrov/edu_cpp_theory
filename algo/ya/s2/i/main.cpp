#include <iostream>
#include <vector>
#include <optional>
#include <string>

template<typename T>
class Queue {
public:
    Queue() = delete;
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
    Queue(Queue&&) = delete;
    Queue& operator=(Queue&&) = delete;

    Queue(size_t size){
        data_.resize(size);
    }

    [[nodiscard]] bool Push(T&& in) {
        if (size_ == data_.size()) [[unlikely]] {
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

        --size_;

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
    int command_count;
    size_t size;
    std::string command;

    getline(std::cin, command);
    command_count = std::stoi(command); 

    getline(std::cin, command);
    size = std::stoul(command);

   

    Queue<int> q(size);

    for(int i = 0; i < command_count; ++i) {
        getline(std::cin, command);
        
        if (command == "peek") {
            auto v = q.Peek();
            if (v == std::nullopt) {
                std::cout << "None\n";
            } else {
                std::cout << v.value() << "\n";
            }
        } else if (command == "size") {
            std::cout << q.Size() <<"\n";
        }else if (command == "pop") {
            auto v = q.Pop();
            if (v == std::nullopt) {
                std::cout << "None\n";
            } else {
                std::cout << v.value() << "\n";
            }
        } else {
            if (!q.Push(std::stoi(command.substr(5)))) {
                std::cout << "error\n";
            }
        }
    }    

    return 0;
}