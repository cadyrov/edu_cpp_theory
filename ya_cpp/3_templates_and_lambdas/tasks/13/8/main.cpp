//  Напишите `Overloaded` и примените его к `std::variant<int, double, std::string>`.
#include <iostream>
#include <variant>

template <typename... Ts> struct Overloaded : Ts... {
    using Ts::operator()...;
};
template <typename... Ts> Overloaded(Ts...) -> Overloaded<Ts...>;

int main() {
    std::variant<int, double, std::string> value = std::string{"hello"};

    auto visitor = Overloaded{[](int x) { std::cout << "int: " << x << '\n'; },
                              [](double x) { std::cout << "double: " << x << '\n'; },
                              [](const std::string& x) { std::cout << "string: " << x << '\n'; }};

    std::visit(visitor, value);
}

// clang++ --std=c++23 -o main