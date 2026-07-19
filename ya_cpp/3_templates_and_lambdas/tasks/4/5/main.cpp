//4. Напишите шаблон класса `Printer<T>`.
#include <iostream>

template <typename T>
class Printer{
    public:
        void print(const T& value){
            std::cout << value << "\n";
        }
};

template <>
class Printer<bool>{
    public:
        void print(bool value){
            value ? std::cout << "true" << "\n" : std::cout << "false" << "\n";
        }
};

int main() {
    Printer<int> p;

    p.print(42);

    Printer<bool> b;
    b.print(true);
    b.print(false);

    return 0;
}