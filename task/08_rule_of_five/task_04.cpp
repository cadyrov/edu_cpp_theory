#include <iostream>
#include <cassert>
#include <cstring>

// Task 4: Конструктор перемещения
//
// Реализуйте класс ResourceHolder с конструктором перемещения:
// 1. Перемещение ресурса без копирования
// 2. Обнуление исходного объекта
// 3. noexcept спецификация

class ResourceHolder {
    int* resource_;
    size_t count_;
    
public:
    // Конструктор
    ResourceHolder(size_t count) : count_(count) {
        resource_ = new int[count_];
        for (size_t i = 0; i < count_; ++i) {
            resource_[i] = static_cast<int>(i);
        }
    }
    
    // TODO: Конструктор перемещения (noexcept)
    ResourceHolder(ResourceHolder&& other) noexcept {
        // TODO: переместите resource_ из other
        // TODO: переместите count_
        // TODO: обнулите other (resource_ = nullptr, count_ = 0)
    }
    
    // Деструктор
    ~ResourceHolder() {
        delete[] resource_;
    }
    
    // Запретить копирование для этого задания
    ResourceHolder(const ResourceHolder&) = delete;
    ResourceHolder& operator=(const ResourceHolder&) = delete;
    ResourceHolder& operator=(ResourceHolder&&) = delete;
    
    int* getResource() const { return resource_; }
    size_t getCount() const { return count_; }
    bool isEmpty() const { return resource_ == nullptr; }
};

// Код для проверки
void testMoveConstructor() {
    // Создание объекта
    ResourceHolder holder1(10);
    assert(holder1.getCount() == 10);
    assert(!holder1.isEmpty());
    
    int* original_ptr = holder1.getResource();
    
    // Перемещение
    ResourceHolder holder2 = std::move(holder1);
    
    // Проверка что данные перемещены
    assert(holder2.getCount() == 10);
    assert(holder2.getResource() == original_ptr);  // Тот же указатель
    assert(holder2.getResource()[0] == 0);
    assert(holder2.getResource()[9] == 9);
    
    // Проверка что исходный объект обнулен
    assert(holder1.isEmpty());
    assert(holder1.getCount() == 0);
    
    // Проверка что перемещение noexcept
    static_assert(noexcept(ResourceHolder(std::declval<ResourceHolder&&>())),
                  "Move constructor should be noexcept");
    
    // Перемещение из временного объекта
    ResourceHolder holder3 = ResourceHolder(5);
    assert(holder3.getCount() == 5);
    assert(!holder3.isEmpty());
    
    std::cout << "Move constructor tests passed!\n";
}

int main() {
    testMoveConstructor();
    return 0;
}

