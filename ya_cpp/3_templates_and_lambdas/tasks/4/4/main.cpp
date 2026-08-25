//4. Напишите шаблон класса `Printer<T>`.
#include <iostream>

template <typename T>
class Printer{
    public:
        void print(const T& value){
            std::cout << value << "\n";
        }
};

int main() {
    Printer<int> p;

    p.print(42);


    return 0;
}