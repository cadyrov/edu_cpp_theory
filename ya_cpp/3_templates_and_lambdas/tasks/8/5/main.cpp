//5. Добавьте `push`, `pop`, `top` в `Stack`.
#include<deque>
#include<iostream>
#include <utility>

template<typename T, typename Container = std::deque<T>>
class Stack {
    public:
        Stack(){};

        void Push(T in) {
            storage_.push_back(std::forward<T>(in));
        }

        T Pop() {
            T a = storage_.back();
            storage_.pop_back();

            return a;
        }

        typename Container::reference Top() {
            return storage_.back();
        }

        typename Container::const_reference Top() const {
            return storage_.back();
        }

    private:
        Container storage_;
};


int main() {
    Stack<int> a;

    a.Push(1);
    a.Push(2);
    a.Push(3);
    
    std::cout << a.Pop() << "\n";
    std::cout << a.Pop() << "\n";
    std::cout << a.Pop() << "\n";


    return 0;
}