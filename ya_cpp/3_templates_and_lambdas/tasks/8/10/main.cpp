//10. Добавьте в `Stack` методы `empty` и `size`, используя `size_type`.
#include<deque>
#include<iostream>
#include <utility>

template<typename T, typename Container = std::deque<T>>
class Stack {
    public:
        using value_type = typename Container::value_type;
        using reference = typename Container::reference;
        using const_reference = typename Container::const_reference;
        using size_type = typename Container::size_type;

        Stack(){};

        template<typename It>
        Stack(It first, It last):storage_(first, last){};

        void Push(const value_type& in) {
            storage_.push_back(in);
        }

        void Push(value_type&& in) {
            storage_.push_back(std::forward<value_type>(in));
        }

        value_type Pop() {
            value_type a = storage_.back();
            storage_.pop_back();

            return a;
        }

        reference Top() {
            return storage_.back();
        }

        const_reference Top() const {
            return storage_.back();
        }

        bool empty() const{
            return storage_.empty();
        }

        size_type size() const {
            return storage_.size();
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
    
    std::cout << s.empty() << "\n";
    std::cout << s.size() << "\n";

    std::cout << s.Pop() << "\n";
    std::cout << s.Pop() << "\n";
    std::cout << s.Pop() << "\n";


    return 0;
}