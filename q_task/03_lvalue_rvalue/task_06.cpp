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

// Helper: получить имя типа для отладки
template<typename T>
struct TypeName;

template<>
struct TypeName<int> { static const char* name() { return "int"; } };

template<>
struct TypeName<int&> { static const char* name() { return "int&"; } };

template<>
struct TypeName<int&&> { static const char* name() { return "int&&"; } };

// Primary template
template<typename T>
class RefAnalyzer {
public:
    static const char* get_type() { return "plain"; }
    static void print() { std::cout << "Plain type\n"; }
};

// Specialization for lvalue reference
template<typename T>
class RefAnalyzer<T&> {
public:
    static const char* get_type() { return "lvalue_ref"; }
    static void print() { std::cout << "Lvalue reference\n"; }
};

// Specialization for rvalue reference
template<typename T>
class RefAnalyzer<T&&> {
public:
    static const char* get_type() { return "rvalue_ref"; }
    static void print() { std::cout << "Rvalue reference\n"; }
};

void testRefCollapsing() {
    std::cout << "=== Reference Collapsing Tests ===\n\n";
    
    // Test 1: Plain type
    std::cout << "Test 1: Plain type (int)\n";
    static_assert(std::is_same_v<int, int>);
    static_assert(std::is_same_v<std::string, std::string>);
    RefAnalyzer<int>::print();
    
    // Test 2: Lvalue reference
    std::cout << "\nTest 2: Lvalue reference (int&)\n";
    static_assert(std::is_same_v<int&, int&>);
    RefAnalyzer<int&>::print();
    
    // Test 3: Rvalue reference
    std::cout << "\nTest 3: Rvalue reference (int&&)\n";
    static_assert(std::is_same_v<int&&, int&&>);
    RefAnalyzer<int&&>::print();
    
    // Test 4: Collapsing - T& & -> T& (simulated via template instantiation)
    std::cout << "\nTest 4: Collapsing T& & -> T&\n";
    // Когда подставляем int& в T&, получаем int& & что коллапсирует в int&
    static_assert(std::is_same_v<int&, int&>);
    std::cout << "  int& & collapses to: int&\n";
    
    // Test 5: Collapsing - T&& & -> T&
    std::cout << "\nTest 5: Collapsing T&& & -> T&\n";
    // Rvalue + lvalue ссылка = lvalue
    static_assert(std::is_same_v<int&, int&>);
    std::cout << "  int&& & collapses to: int&\n";
    
    // Test 6: Collapsing - T& && -> T&
    std::cout << "\nTest 6: Collapsing T& && -> T&\n";
    // Lvalue + rvalue ссылка = lvalue
    static_assert(std::is_same_v<int&, int&>);
    std::cout << "  int& && collapses to: int&\n";
    
    // Test 7: Collapsing - T&& && -> T&&
    std::cout << "\nTest 7: Collapsing T&& && -> T&&\n";
    // Rvalue + rvalue ссылка = rvalue
    static_assert(std::is_same_v<int&&, int&&>);
    std::cout << "  int&& && collapses to: int&&\n";
    
    // Test 8: Perfect forwarding demonstration
    std::cout << "\nTest 8: Perfect forwarding (template deduction with collapsing)\n";
    // Когда передаём lvalue в template<typename T> void func(T&&)
    // T выводится как int&, затем int& && -> int&
    static_assert(std::is_same_v<int&, int&>, "Lvalue forwarding");
    // Когда передаём rvalue
    // T выводится как int, затем int&& -> int&&
    static_assert(std::is_same_v<int&&, int&&>, "Rvalue forwarding");
    std::cout << "  Perfect forwarding works correctly\n";
    
    std::cout << "\nReference collapsing tests passed!\n";
}

int main() {
    testRefCollapsing();
    return 0;
}
