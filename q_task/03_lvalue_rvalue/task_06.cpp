#include <iostream>
#include <cassert>
#include <type_traits>

// Task 6: Правила коллапсирования ссылок (Reference Collapsing)
//
// Напишите шаблоны, которые демонстрируют правила коллапсирования:
// T& & -> T&
// T&& & -> T&
// T& && -> T&
// T&& && -> T&&

template<typename T>
class RefAnalyzer {
public:
    // TODO: реализуйте get_type для разных случаев
    static const char* get_type();
};

// TODO: специализации для разных типов ссылок

void testRefCollapsing() {
    // TODO: Используйте std::is_same для проверки типов
    // TODO: Проверьте правила коллапсирования
    
    std::cout << "Reference collapsing tests passed!\n";
}

int main() {
    testRefCollapsing();
    return 0;
}
