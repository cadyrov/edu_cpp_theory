#include <iostream>
#include <cassert>
#include <memory>

// Task 7: enable_shared_from_this
//
// Реализуйте класс SharedObject, который:
// 1. Наследуется от enable_shared_from_this
// 2. Может безопасно возвращать shared_ptr на себя
// 3. Правильно используется с make_shared

class SharedObject : public std::enable_shared_from_this<SharedObject> {
    int value_;
    
public:
    SharedObject(int value) : value_(value) {}
    
    // TODO: Получить shared_ptr на себя
    std::shared_ptr<SharedObject> getSharedPtr() {
        // TODO: используйте shared_from_this()
        return nullptr;
    }
    
    // TODO: Получить weak_ptr на себя
    std::weak_ptr<SharedObject> getWeakPtr() {
        // TODO: используйте weak_from_this()
        return std::weak_ptr<SharedObject>();
    }
    
    int getValue() const { return value_; }
    void setValue(int v) { value_ = v; }
};

// TODO: Фабричная функция для создания shared_ptr
std::shared_ptr<SharedObject> createSharedObject(int value) {
    // TODO: создайте shared_ptr через make_shared
    return nullptr;
}

// Код для проверки
void testEnableSharedFromThis() {
    // Создание через make_shared (обязательно!)
    auto obj = createSharedObject(42);
    assert(obj != nullptr);
    assert(obj->getValue() == 42);
    
    // Получение shared_ptr на себя
    auto self_ptr = obj->getSharedPtr();
    assert(self_ptr != nullptr);
    assert(self_ptr->getValue() == 42);
    assert(self_ptr.use_count() == 2);  // obj и self_ptr
    
    // Получение weak_ptr на себя
    auto weak_ptr = obj->getWeakPtr();
    assert(!weak_ptr.expired());
    
    // Использование weak_ptr
    auto locked = weak_ptr.lock();
    assert(locked != nullptr);
    assert(locked->getValue() == 42);
    
    std::cout << "enable_shared_from_this tests passed!\n";
}

int main() {
    testEnableSharedFromThis();
    return 0;
}

