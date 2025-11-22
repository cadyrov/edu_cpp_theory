#include <iostream>
#include <cassert>
#include <string>
#include <utility>

// Task 8: Copy-and-swap идиома
//
// Реализуйте класс StringContainer используя copy-and-swap:
// 1. Реализуйте конструктор копирования
// 2. Реализуйте оператор присваивания через swap
// 3. Обеспечьте строгую гарантию exception safety

class StringContainer {
    std::string* data_;
    size_t size_;
    
public:
    // TODO: Конструктор
    StringContainer(const std::string& str) : size_(1) {
        // TODO: выделите память и скопируйте строку
    }
    
    // TODO: Конструктор копирования
    StringContainer(const StringContainer& other) : size_(other.size_) {
        // TODO: скопируйте данные из other
    }
    
    // TODO: Деструктор
    ~StringContainer() {
        // TODO: освободите память
    }
    
    // TODO: Метод swap (noexcept)
    void swap(StringContainer& other) noexcept {
        // TODO: обменяйте содержимое используя std::swap
    }
    
    // TODO: Оператор присваивания через copy-and-swap
    StringContainer& operator=(const StringContainer& other) {
        // TODO: создайте временную копию other
        // TODO: используйте swap для атомарной замены
        // TODO: это обеспечивает строгую гарантию
        return *this;
    }
    
    // TODO: Оператор перемещения
    StringContainer(StringContainer&& other) noexcept 
        : data_(other.data_), size_(other.size_) {
        // TODO: переместите данные
        // TODO: обнулите other
    }
    
    // TODO: Оператор перемещающего присваивания
    StringContainer& operator=(StringContainer&& other) noexcept {
        // TODO: используйте swap для перемещения
        return *this;
    }
    
    const std::string& getString() const {
        return data_ ? *data_ : throw std::runtime_error("Empty container");
    }
    
    size_t getSize() const { return size_; }
};

// Код для проверки
void testCopyAndSwap() {
    // Создание объектов
    StringContainer c1("Hello");
    StringContainer c2("World");
    
    assert(c1.getString() == "Hello");
    assert(c2.getString() == "World");
    
    // Тест копирования
    StringContainer c3 = c1;
    assert(c3.getString() == "Hello");
    assert(c1.getString() == "Hello");  // Оригинал не изменился
    
    // Тест присваивания через copy-and-swap
    c2 = c1;
    assert(c2.getString() == "Hello");
    
    // Тест swap
    StringContainer c4("Test");
    c4.swap(c1);
    assert(c4.getString() == "Hello");
    assert(c1.getString() == "Test");
    
    // Тест перемещения
    StringContainer c5 = std::move(c2);
    assert(c5.getString() == "Hello");
    
    // Проверка что swap noexcept
    static_assert(noexcept(std::declval<StringContainer>().swap(std::declval<StringContainer&>())),
                  "swap should be noexcept");
    
    std::cout << "Copy-and-swap tests passed!\n";
}

int main() {
    testCopyAndSwap();
    return 0;
}

