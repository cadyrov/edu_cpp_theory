#include <iostream>
#include <memory>
#include <optional>
#include <string>

template<typename T>
class Node {
public:
    Node(T value) : data_(value) {}
    T data_;
    std::unique_ptr<Node> next_;   
};


template<typename T>
class Queue {
public:
    Queue() : l_(nullptr), r_(nullptr) {}
    Queue(const Queue&) = delete;
    Queue(Queue&&) = delete;
    Queue& operator= (const Queue&) = delete;
    Queue& operator =(Queue&&) = delete;

    size_t Size() const{
        return size_;
    }

    void Push(T in) {
        auto new_node = std::make_unique<Node<T>>(in);
        if (l_ == nullptr) {
            l_ = std::move(new_node);
            r_ = l_.get();
        } else {
            r_->next_ = std::move(new_node);
            r_ = r_->next_.get();
        }
        ++size_;
    }

    std::optional<T> Get() {
        if (l_ == nullptr) {
            return std::nullopt;
        }
        T value = l_->data_;
        l_ = std::move(l_->next_);
        --size_;
        
        if (l_ == nullptr) {
            r_ = nullptr;
        }

        return value;
    }
private:
    std::unique_ptr<Node<T>> l_;  // левый (начало очереди)
    Node<T>* r_;                   // правый (конец очереди)
    size_t size_ = 0;
};


int main() {
    std::string command;
    size_t n;

    getline(std::cin, command);
    n = std::stoul(command);

    Queue<int> queue;

    for (size_t i = 0; i < n; ++i) {
        getline(std::cin, command);

        if (command.substr(0, 3) == "put") {
            int value = std::stoi(command.substr(4));
            queue.Push(value);
        } else if (command == "get") {
            auto result = queue.Get();
            if (result.has_value()) {
                std::cout << result.value() << std::endl;
            } else {
                std::cout << "error" << std::endl;
            }
        } else if (command == "size") {
            std::cout << queue.Size() << std::endl;
        }   
    }


    return 0;
}