#include <iostream>
#include <cassert>
#include <memory>

// Task 5: Преобразования между умными указателями
//
// Реализуйте функции для преобразования:
// 1. Преобразование unique_ptr в shared_ptr
// 2. Работа с полиморфизмом (Base/Derived)
// 3. Правильная передача владения

class Base {
public:
    virtual ~Base() = default;
    virtual int getValue() const { return 0; }
};

class Derived : public Base {
    int value_;
public:
    Derived(int v) : value_(v) {}
    int getValue() const override { return value_; }
};

// TODO: Преобразовать unique_ptr в shared_ptr
std::shared_ptr<Base> convertToShared(std::unique_ptr<Base> unique) {
    // TODO: преобразуйте unique_ptr в shared_ptr
    return nullptr;
}

// TODO: Создать shared_ptr из Derived
std::shared_ptr<Base> createDerivedShared(int value) {
    // TODO: создайте shared_ptr<Derived> и преобразуйте в shared_ptr<Base>
    return nullptr;
}

// TODO: Создать unique_ptr из Derived
std::unique_ptr<Base> createDerivedUnique(int value) {
    // TODO: создайте unique_ptr<Derived> и преобразуйте в unique_ptr<Base>
    return nullptr;
}

// Код для проверки
void testConversions() {
    // Преобразование unique_ptr в shared_ptr
    auto unique = std::make_unique<Derived>(42);
    std::shared_ptr<Base> shared = convertToShared(std::move(unique));
    assert(shared != nullptr);
    assert(shared->getValue() == 42);
    assert(unique == nullptr);  // unique_ptr должен быть перемещен
    
    // Создание shared_ptr из Derived
    auto shared_derived = createDerivedShared(100);
    assert(shared_derived != nullptr);
    assert(shared_derived->getValue() == 100);
    
    // Создание unique_ptr из Derived
    auto unique_derived = createDerivedUnique(200);
    assert(unique_derived != nullptr);
    assert(unique_derived->getValue() == 200);
    
    std::cout << "Smart pointer conversions tests passed!\n";
}

int main() {
    testConversions();
    return 0;
}

