#include <iostream>
#include <cassert>
#include <memory>
#include <vector>
#include <mutex>
#include <functional>

// Task 10: Продвинутые RAII обертки
//
// Реализуйте класс AdvancedRAII, который:
// 1. Управляет ресурсами с кастомными делитерами
// 2. Поддерживает различные типы ресурсов через шаблоны
// 3. Обеспечивает exception safety
// 4. Поддерживает перемещение ресурсов

template<typename T, typename Deleter = std::default_delete<T>>
class AdvancedRAII {
    T* resource_;
    Deleter deleter_;
    
public:
    // TODO: Конструктор
    explicit AdvancedRAII(T* resource, Deleter deleter = Deleter{}) 
        : resource_(resource), deleter_(deleter) {
        // TODO: инициализируйте члены
    }
    
    // TODO: Деструктор
    ~AdvancedRAII() {
        // TODO: освободите ресурс через deleter_
    }
    
    // TODO: Запретить копирование
    AdvancedRAII(const AdvancedRAII&) = delete;
    AdvancedRAII& operator=(const AdvancedRAII&) = delete;
    
    // TODO: Конструктор перемещения
    AdvancedRAII(AdvancedRAII&& other) noexcept 
        : resource_(other.resource_), deleter_(std::move(other.deleter_)) {
        // TODO: переместите ресурс
        // TODO: обнулите other.resource_
    }
    
    // TODO: Оператор присваивания перемещением
    AdvancedRAII& operator=(AdvancedRAII&& other) noexcept {
        // TODO: освободите текущий ресурс
        // TODO: переместите ресурс из other
        return *this;
    }
    
    // TODO: Получить указатель на ресурс
    T* get() { return resource_; }
    const T* get() const { return resource_; }
    
    // TODO: Освободить ресурс вручную
    void release() {
        // TODO: освободите ресурс и обнулите resource_
    }
    
    // TODO: Проверка валидности
    bool isValid() const {
        // TODO: реализуйте проверку
        return false;
    }
};

// Кастомный делитер для массива
struct ArrayDeleter {
    void operator()(int* ptr) const {
        delete[] ptr;
    }
};

// Код для проверки
void testAdvancedRAII() {
    // Использование с default deleter
    {
        AdvancedRAII<int> ptr(new int(42));
        assert(ptr.isValid());
        assert(*ptr.get() == 42);
    }
    
    // Использование с кастомным deleter для массива
    {
        int* raw_arr = new int[10];
        AdvancedRAII<int, ArrayDeleter> arr(raw_arr, ArrayDeleter{});
        assert(arr.isValid());
        arr.get()[0] = 100;
        assert(arr.get()[0] == 100);
    }
    
    // Перемещение
    {
        AdvancedRAII<int> ptr1(new int(200));
        AdvancedRAII<int> ptr2 = std::move(ptr1);
        assert(!ptr1.isValid());
        assert(ptr2.isValid());
        assert(*ptr2.get() == 200);
    }
    
    // Ручное освобождение
    {
        AdvancedRAII<int> ptr(new int(300));
        assert(ptr.isValid());
        ptr.release();
        assert(!ptr.isValid());
    }
    
    std::cout << "AdvancedRAII tests passed!\n";
}

int main() {
    testAdvancedRAII();
    return 0;
}

