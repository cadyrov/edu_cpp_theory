#include <iostream>
#include <cassert>
#include <memory>
#include <algorithm>

// Task 8: Буфер с неинициализированной памятью
//
// Реализуйте класс UninitializedBuffer, который:
// 1. Управляет буфером неинициализированной памяти
// 2. Поддерживает создание объектов через placement new
// 3. Правильно управляет жизненным циклом объектов
// 4. Поддерживает копирование и перемещение

template<typename T>
class UninitializedBuffer {
    unsigned char* buffer_;
    size_t capacity_;
    size_t size_;
    
public:
    explicit UninitializedBuffer(size_t capacity) 
        : buffer_(nullptr), capacity_(0), size_(0) {
        // TODO: выделите память через operator new[] с правильным выравниванием
        // Подсказка: используйте alignas(T) или std::aligned_alloc
        // TODO: инициализируйте capacity_
    }
    
    // TODO: Деструктор
    ~UninitializedBuffer() {
        // TODO: уничтожьте все созданные объекты через std::destroy_n
        // TODO: освободите память через operator delete[]
    }
    
    // TODO: Создать объект в буфере
    template<typename... Args>
    T* construct(Args&&... args) {
        // TODO: проверьте что есть место
        // TODO: используйте placement new для создания объекта
        // TODO: обновите size_
        return nullptr;
    }
    
    // TODO: Уничтожить объект по индексу
    void destroy(size_t index) {
        // TODO: используйте std::destroy_at
        // TODO: обновите size_
    }
    
    // TODO: Уничтожить все объекты
    void destroyAll() {
        // TODO: используйте std::destroy_n
        // TODO: обновите size_
    }
    
    // TODO: Получить указатель на объект
    T* get(size_t index) {
        // TODO: верните указатель на объект по индексу
        return nullptr;
    }
    
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
};

// Код для проверки
void testUninitializedBuffer() {
    UninitializedBuffer<int> buffer(10);
    
    assert(buffer.capacity() == 10);
    assert(buffer.size() == 0);
    
    // Создание объектов
    int* obj1 = buffer.construct(42);
    int* obj2 = buffer.construct(100);
    int* obj3 = buffer.construct(200);
    
    assert(buffer.size() == 3);
    assert(*obj1 == 42);
    assert(*obj2 == 100);
    assert(*obj3 == 200);
    
    // Доступ к объектам
    assert(*buffer.get(0) == 42);
    assert(*buffer.get(1) == 100);
    assert(*buffer.get(2) == 200);
    
    // Уничтожение одного объекта
    buffer.destroy(1);
    assert(buffer.size() == 2);
    
    // Уничтожение всех объектов
    buffer.destroyAll();
    assert(buffer.size() == 0);
    
    std::cout << "UninitializedBuffer tests passed!\n";
}

int main() {
    testUninitializedBuffer();
    return 0;
}

