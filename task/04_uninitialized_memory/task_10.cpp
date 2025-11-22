#include <iostream>
#include <cassert>
#include <memory>
#include <vector>
#include <new>

// Task 10: Продвинутый аллокатор с неинициализированной памятью
//
// Реализуйте класс AdvancedAllocator, который:
// 1. Выделяет память без инициализации
// 2. Поддерживает создание объектов через placement new
// 3. Отслеживает созданные объекты
// 4. Правильно освобождает память при исключениях
// 5. Поддерживает выравнивание

template<typename T>
class AdvancedAllocator {
    unsigned char* buffer_;
    size_t capacity_;
    size_t size_;
    std::vector<bool> constructed_;  // Отслеживание созданных объектов
    
public:
    explicit AdvancedAllocator(size_t capacity) 
        : buffer_(nullptr), capacity_(0), size_(0) {
        // TODO: выделите память через operator new[] с правильным выравниванием
        // Подсказка: используйте alignas(T) или std::aligned_alloc
        // TODO: инициализируйте constructed_
    }
    
    // TODO: Деструктор
    ~AdvancedAllocator() {
        // TODO: уничтожьте все созданные объекты
        // TODO: освободите память через operator delete[]
    }
    
    // TODO: Создать объект по индексу
    template<typename... Args>
    T* constructAt(size_t index, Args&&... args) {
        // TODO: проверьте что индекс валиден и объект еще не создан
        // TODO: используйте placement new для создания объекта
        // TODO: обновите constructed_ и size_
        return nullptr;
    }
    
    // TODO: Уничтожить объект по индексу
    void destroyAt(size_t index) {
        // TODO: проверьте что объект создан
        // TODO: используйте std::destroy_at
        // TODO: обновите constructed_ и size_
    }
    
    // TODO: Уничтожить все объекты
    void destroyAll() {
        // TODO: уничтожьте все созданные объекты
        // TODO: обновите constructed_ и size_
    }
    
    // TODO: Получить указатель на объект
    T* get(size_t index) {
        // TODO: верните указатель на объект или nullptr если не создан
        return nullptr;
    }
    
    // TODO: Проверить создан ли объект
    bool isConstructed(size_t index) const {
        // TODO: реализуйте проверку
        return false;
    }
    
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    
    // TODO: Запретить копирование
    AdvancedAllocator(const AdvancedAllocator&) = delete;
    AdvancedAllocator& operator=(const AdvancedAllocator&) = delete;
};

// Код для проверки
void testAdvancedAllocator() {
    AdvancedAllocator<int> allocator(10);
    
    assert(allocator.capacity() == 10);
    assert(allocator.size() == 0);
    
    // Создание объектов в разных позициях
    int* obj1 = allocator.constructAt(2, 42);
    int* obj2 = allocator.constructAt(5, 100);
    int* obj3 = allocator.constructAt(8, 200);
    
    assert(obj1 != nullptr);
    assert(obj2 != nullptr);
    assert(obj3 != nullptr);
    assert(*obj1 == 42);
    assert(*obj2 == 100);
    assert(*obj3 == 200);
    assert(allocator.size() == 3);
    
    // Проверка состояния
    assert(allocator.isConstructed(2));
    assert(allocator.isConstructed(5));
    assert(allocator.isConstructed(8));
    assert(!allocator.isConstructed(0));
    assert(!allocator.isConstructed(9));
    
    // Доступ к объектам
    assert(*allocator.get(2) == 42);
    assert(*allocator.get(5) == 100);
    assert(allocator.get(0) == nullptr);
    
    // Уничтожение одного объекта
    allocator.destroyAt(5);
    assert(allocator.size() == 2);
    assert(!allocator.isConstructed(5));
    assert(allocator.isConstructed(2));
    
    // Уничтожение всех объектов
    allocator.destroyAll();
    assert(allocator.size() == 0);
    assert(!allocator.isConstructed(2));
    assert(!allocator.isConstructed(8));
    
    std::cout << "AdvancedAllocator tests passed!\n";
}

int main() {
    testAdvancedAllocator();
    return 0;
}

