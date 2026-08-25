#include <iostream>

template<typename Printer>
class Base{
public:
    template<typename T>
    std::ostream&  print(std::ostream& os, T in){
        return static_cast<Printer*>(this)->print_impl(os, in);
    }
};

class Printer: public Base<Printer>{
public:
    template<typename T>
    std::ostream& print_impl(std::ostream& os, T in){
        os << in;

        return os;
    }
};

int main() {
    Printer x;

    x.print(std::cout, 1);

    return 0;
}
