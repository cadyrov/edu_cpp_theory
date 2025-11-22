#include <iostream>
#include <cassert>
#include <memory>
#include <vector>
#include <mutex>

// Task 9: Комбинирование RAII паттернов
//
// Реализуйте класс SafeContainer, который:
// 1. Использует RAII для управления памятью
// 2. Использует RAII для синхронизации доступа
// 3. Комбинирует несколько RAII паттернов
// 4. Гарантирует безопасность при исключениях

template<typename T>
class SafeContainer {
    std::vector<T> data_;
    mutable std::mutex mutex_;
    
public:
    // TODO: Добавить элемент (с автоматической блокировкой)
    void push(const T& value) {
        // TODO: используйте std::lock_guard для блокировки
        // TODO: добавьте элемент в data_
    }
    
    // TODO: Получить размер (с автоматической блокировкой)
    size_t size() const {
        // TODO: используйте std::lock_guard для блокировки
        return 0;
    }
    
    // TODO: Получить элемент по индексу (с автоматической блокировкой)
    T get(size_t index) const {
        // TODO: используйте std::lock_guard для блокировки
        // TODO: верните элемент по индексу
        return T{};
    }
    
    // TODO: Очистить контейнер (с автоматической блокировкой)
    void clear() {
        // TODO: используйте std::lock_guard для блокировки
        // TODO: очистите data_
    }
    
    // TODO: Оператор присваивания с блокировкой
    SafeContainer& operator=(const SafeContainer& other) {
        // TODO: используйте std::lock_guard для обоих контейнеров
        // TODO: скопируйте данные
        return *this;
    }
};

// Код для проверки
void testSafeContainer() {
    SafeContainer<int> container;
    
    // Добавление элементов
    container.push(1);
    container.push(2);
    container.push(3);
    
    assert(container.size() == 3);
    assert(container.get(0) == 1);
    assert(container.get(1) == 2);
    assert(container.get(2) == 3);
    
    // Копирование
    SafeContainer<int> container2;
    container2 = container;
    assert(container2.size() == 3);
    
    // Очистка
    container.clear();
    assert(container.size() == 0);
    
    // Тест с исключениями
    try {
        container.push(42);
        // Симуляция исключения
        throw std::runtime_error("test");
    } catch (...) {
        // Контейнер должен остаться в валидном состоянии
        assert(container.size() == 1);
    }
    
    std::cout << "SafeContainer (combined RAII) tests passed!\n";
}

int main() {
    testSafeContainer();
    return 0;
}

