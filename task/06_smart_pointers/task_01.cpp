#include <iostream>
#include <cassert>
#include <memory>

// Task 1: Базовое использование std::unique_ptr
//
// Реализуйте функции для работы с unique_ptr:
// 1. Создание unique_ptr через make_unique
// 2. Передача владения
// 3. Доступ к ресурсу
// 4. Автоматическое освобождение памяти

class Resource {
    int value_;
public:
    Resource(int v) : value_(v) {
        std::cout << "Resource created with value: " << value_ << "\n";
    }
    
    ~Resource() {
        std::cout << "Resource destroyed with value: " << value_ << "\n";
    }
    
    int getValue() const { return value_; }
    void setValue(int v) { value_ = v; }
};

// TODO: Создать unique_ptr через make_unique
std::unique_ptr<Resource> createResource(int value) {
    // TODO: используйте std::make_unique для создания
    return nullptr;
}

// TODO: Функция принимающая unique_ptr по значению (передача владения)
void useResource(std::unique_ptr<Resource> res) {
    // TODO: используйте ресурс
    // TODO: при выходе из функции ресурс автоматически освободится
}

// Код для проверки
void testUniquePtr() {
    // Создание unique_ptr
    auto res = createResource(42);
    assert(res != nullptr);
    assert(res->getValue() == 42);
    
    // Доступ к ресурсу
    res->setValue(100);
    assert(res->getValue() == 100);
    
    // Передача владения
    useResource(std::move(res));
    assert(res == nullptr);  // После перемещения должен быть nullptr
    
    // Автоматическое освобождение при выходе из области видимости
    {
        auto local_res = createResource(200);
        assert(local_res->getValue() == 200);
    }
    // Ресурс автоматически освобожден
    
    std::cout << "Unique_ptr basic tests passed!\n";
}

int main() {
    testUniquePtr();
    return 0;
}

