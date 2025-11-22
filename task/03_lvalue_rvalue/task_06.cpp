#include <iostream>
#include <cassert>
#include <string>
#include <type_traits>

// Task 6: Правила коллапсирования ссылок (Reference Collapsing)
//
// Напишите шаблоны, которые демонстрируют правила коллапсирования:
// T& & -> T&
// T&& & -> T&
// T& && -> T&
// T&& && -> T&&

// TODO: Helper: получить имя типа для отладки
template<typename T>
struct TypeName;

// TODO: Специализации для int, int&, int&&

// TODO: Primary template
template<typename T>
class RefAnalyzer {
public:
    // TODO: реализуйте методы для определения типа
};

// TODO: Specialization for lvalue reference
template<typename T>
class RefAnalyzer<T&> {
public:
    // TODO: реализуйте
};

// TODO: Specialization for rvalue reference
template<typename T>
class RefAnalyzer<T&&> {
public:
    // TODO: реализуйте
};

void testRefCollapsing() {
    std::cout << "=== Reference Collapsing Tests ===\n\n";
    
    // TODO: Реализуйте тесты для всех правил коллапсирования
    
    std::cout << "\nReference collapsing tests passed!\n";
}

int main() {
    testRefCollapsing();
    return 0;
}
