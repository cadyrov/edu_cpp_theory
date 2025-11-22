#include <iostream>
#include <cassert>

// Task 3: No-throw гарантия
//
// Реализуйте класс NoThrowContainer, который:
// 1. Предоставляет методы с noexcept гарантией
// 2. Использует операции которые не бросают исключения
// 3. Правильно помечает методы как noexcept

class NoThrowContainer {
    int* data_;
    size_t size_;
    size_t capacity_;
    
public:
    // TODO: Конструктор по умолчанию (noexcept)
    NoThrowContainer() noexcept {
        // TODO: инициализируйте поля
    }
    
    // TODO: Деструктор (должен быть noexcept)
    ~NoThrowContainer() noexcept {
        // TODO: освободите память
    }
    
    // TODO: Метод swap (noexcept)
    void swap(NoThrowContainer& other) noexcept {
        // TODO: обменяйте содержимое используя std::swap
        // TODO: swap для встроенных типов не бросает исключений
    }
    
    // TODO: Метод получения размера (noexcept)
    size_t getSize() const noexcept {
        // TODO: верните размер
        return 0;
    }
    
    // TODO: Метод проверки пустоты (noexcept)
    bool isEmpty() const noexcept {
        // TODO: верните true если контейнер пуст
        return true;
    }
    
    // TODO: Оператор присваивания через swap (noexcept)
    NoThrowContainer& operator=(const NoThrowContainer& other) {
        // TODO: создайте копию
        // TODO: используйте swap для атомарной замены
        return *this;
    }
    
    // Запретить копирование для простоты
    NoThrowContainer(const NoThrowContainer&) = delete;
};

// Код для проверки
void testNoThrowGuarantee() {
    // Создание контейнеров
    NoThrowContainer c1;
    NoThrowContainer c2;
    
    assert(c1.isEmpty());
    assert(c1.getSize() == 0);
    
    // Тест swap (должен быть noexcept)
    c1.swap(c2);
    
    // Проверка что swap не бросает исключений
    static_assert(noexcept(c1.swap(c2)), "swap should be noexcept");
    static_assert(noexcept(c1.getSize()), "getSize should be noexcept");
    static_assert(noexcept(c1.isEmpty()), "isEmpty should be noexcept");
    
    std::cout << "No-throw guarantee tests passed!\n";
}

int main() {
    testNoThrowGuarantee();
    return 0;
}

