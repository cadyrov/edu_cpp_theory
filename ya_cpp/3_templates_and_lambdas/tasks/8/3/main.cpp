//3. Напишите `Stack<T, Container>` поверх контейнера.
#include<deque>
#include<iostream>

template<typename T, typename Container = std::deque<T>>
class Stack {
    public:
        Stack(){};

        void Put(T in) {
            storage_.push_back(in);
        }

        T Pop() {
            T a = storage_.back();
            storage_.pop_back();

            return a;
        }

    private:
        Container storage_;
};


int main() {
    Stack<int> a;

    a.Put(1);
    a.Put(2);
    a.Put(3);
    
    std::cout << a.Pop() << "\n";
    std::cout << a.Pop() << "\n";
    std::cout << a.Pop() << "\n";


    return 0;
}