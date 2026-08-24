// Напишите visit_tuple, который через std::apply вызывает visitor для каждого элемента tuple.
#include <iostream>
#include <tuple>
#include <variant>

int main() {
    std::variant<int, double, std::string> value = std::string{"hello"};

    auto visitor = Overloaded{[](int x) { std::cout << "int: " << x << '\n'; },
                              [](double x) { std::cout << "double: " << x << '\n'; },
                              [](const std::string& x) { std::cout << "string: " << x << '\n'; }};

    std::visit(visitor, value);
}

// clang++ --std=c++23 -o main