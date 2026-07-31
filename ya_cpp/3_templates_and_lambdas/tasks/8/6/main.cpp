//6. Напишите шаблонный конструктор `Stack(It first, It last)`.
#include<deque>
#include<iostream>
#include <utility>

template<typename T, typename Container = std::deque<T>>
class Stack {
    public:
        Stack(){};

        template<typename It>
        Stack(It first, It last):storage_(first, last){};

        void Push(const T& in) {
            storage_.push_back(in);
        }

        void Push(T&& in) {
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
    

    std::deque<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    Stack<int> s(a.begin(), a.end());
    
    std::cout << s.Pop() << "\n";
    std::cout << s.Pop() << "\n";
    std::cout << s.Pop() << "\n";


    return 0;
}