// Напишите visit_tuple, который через std::apply вызывает visitor для каждого элемента tuple.
#include <iostream>
#include <string>
#include <tuple>
#include <utility>

template <typename Visitor, typename Tuple> void visit_tuple(Visitor&& visitor, Tuple&& tuple) {
    std::apply([&visitor](auto&&... args) { (visitor(std::forward<decltype(args)>(args)), ...); },
               std::forward<Tuple>(tuple));
}

int main() {
    auto data = std::tuple{42, std::string{"hello"}, 3.5};

    visit_tuple([](const auto& value) { std::cout << value << '\n'; }, data);
}

// clang++ --std=c++23 -o main