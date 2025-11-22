#include <iostream>
#include <cassert>
#include <vector>
#include <utility>

// Task 9: Forwarding функций с универсальными ссылками
//
// Реализуйте шаблонный контейнер Holder, который:
// - Принимает функцию и параметры через универсальные ссылки
// - Вызывает функцию с сохранением категории значения параметров
// - Использует std::forward для perfect forwarding

template<typename Func, typename... Args>
class Holder {
    // TODO: сохраняйте функцию и аргументы
    
public:
    Holder(Func&& f, Args&&... args) {
        // TODO: сохраните функцию и аргументы используя std::forward
    }
    
    // TODO: метод execute, который вызывает функцию с сохраненными аргументами
};

void testFunctionForwarding() {
    int counter = 0;
    
    auto increment_by_ref = [&counter](int& x) {
        counter++;
        x++;
    };
    
    auto increment_by_rvalue = [&counter](int&& x) {
        counter += 10;
    };
    
    // TODO: Используйте Holder для сохранения и вызова функций
    // TODO: Проверьте что категория значения сохраняется
    
    std::cout << "Function forwarding tests passed!\n";
}

int main() {
    testFunctionForwarding();
    return 0;
}
