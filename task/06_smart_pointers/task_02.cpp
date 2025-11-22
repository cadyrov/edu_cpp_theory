#include <iostream>
#include <cassert>
#include <memory>

// Task 2: std::shared_ptr и разделяемое владение
//
// Реализуйте класс SharedResource, который:
// 1. Использует shared_ptr для разделяемого владения
// 2. Позволяет нескольким объектам использовать один ресурс
// 3. Автоматически освобождает ресурс когда последний владелец уничтожен

class SharedResource {
    std::shared_ptr<int> data_;
    
public:
    // TODO: Конструктор (создает shared_ptr)
    SharedResource(int value) {
        // TODO: создайте shared_ptr через make_shared
    }
    
    // TODO: Конструктор копирования (разделяет владение)
    SharedResource(const SharedResource& other) {
        // TODO: скопируйте shared_ptr (разделение владения)
    }
    
    // TODO: Оператор присваивания (разделяет владение)
    SharedResource& operator=(const SharedResource& other) {
        // TODO: скопируйте shared_ptr
        return *this;
    }
    
    // TODO: Получить значение
    int getValue() const {
        // TODO: реализуйте доступ к значению
        return 0;
    }
    
    // TODO: Установить значение
    void setValue(int value) {
        // TODO: реализуйте установку значения
    }
    
    // TODO: Получить количество владельцев
    size_t useCount() const {
        // TODO: верните количество владельцев shared_ptr
        return 0;
    }
};

// Код для проверки
void testSharedPtr() {
    // Создание первого объекта
    SharedResource res1(42);
    assert(res1.getValue() == 42);
    assert(res1.useCount() == 1);
    
    // Копирование (разделение владения)
    SharedResource res2 = res1;
    assert(res1.useCount() == 2);
    assert(res2.useCount() == 2);
    assert(res1.getValue() == 42);
    assert(res2.getValue() == 42);
    
    // Изменение через один объект влияет на другой
    res1.setValue(100);
    assert(res2.getValue() == 100);
    
    // Создание третьего объекта
    {
        SharedResource res3 = res1;
        assert(res1.useCount() == 3);
    }
    // res3 уничтожен, но ресурс еще существует
    assert(res1.useCount() == 2);
    
    // Уничтожение res2
    res2 = SharedResource(200);  // Присваивание нового значения
    assert(res1.useCount() == 1);
    assert(res1.getValue() == 100);
    
    std::cout << "Shared_ptr tests passed!\n";
}

int main() {
    testSharedPtr();
    return 0;
}

