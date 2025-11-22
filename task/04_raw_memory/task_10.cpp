#include <iostream>
#include <cassert>
#include <cstddef>
#include <map>
#include <cstring>

// Task 10: Продвинутый аллокатор с отслеживанием
//
// Реализуйте класс TrackingAllocator, который:
// 1. Отслеживает все выделения и освобождения памяти
// 2. Обнаруживает утечки памяти
// 3. Предоставляет статистику использования памяти
// 4. Проверяет двойное освобождение и использование после освобождения

struct AllocationInfo {
    void* ptr;
    size_t size;
    const char* file;
    int line;
};

class TrackingAllocator {
    std::map<void*, AllocationInfo> allocations_;
    size_t total_allocated_;
    size_t peak_allocated_;
    size_t allocation_count_;
    
public:
    TrackingAllocator() 
        : total_allocated_(0), peak_allocated_(0), allocation_count_(0) {}
    
    // TODO: Выделить память с отслеживанием
    void* allocate(size_t size, const char* file = __FILE__, int line = __LINE__) {
        // TODO: реализуйте выделение с записью информации
        return nullptr;
    }
    
    // TODO: Освободить память с проверками
    void deallocate(void* ptr) {
        // TODO: реализуйте освобождение с проверкой:
        // - что указатель был выделен через этот аллокатор
        // - что он не был освобожден ранее
    }
    
    // TODO: Получить статистику
    size_t getTotalAllocated() const { return total_allocated_; }
    size_t getPeakAllocated() const { return peak_allocated_; }
    size_t getAllocationCount() const { return allocation_count_; }
    size_t getCurrentAllocated() const {
        // TODO: реализуйте подсчет текущей выделенной памяти
        return 0;
    }
    
    // TODO: Проверить на утечки
    bool hasLeaks() const {
        // TODO: реализуйте проверку наличия утечек
        return false;
    }
    
    // TODO: Вывести информацию об утечках
    void printLeaks() const {
        // TODO: реализуйте вывод информации об утечках
    }
    
    ~TrackingAllocator() {
        // TODO: в деструкторе проверьте на утечки
    }
};

// Код для проверки
void testTrackingAllocator() {
    TrackingAllocator allocator;
    
    // Выделение памяти
    void* ptr1 = allocator.allocate(100);
    void* ptr2 = allocator.allocate(200);
    
    assert(ptr1 != nullptr);
    assert(ptr2 != nullptr);
    assert(allocator.getAllocationCount() == 2);
    assert(allocator.getCurrentAllocated() == 300);
    
    // Освобождение
    allocator.deallocate(ptr1);
    assert(allocator.getCurrentAllocated() == 200);
    
    // Проверка на утечки (ptr2 еще не освобожден)
    assert(allocator.hasLeaks() == true);
    
    allocator.deallocate(ptr2);
    assert(allocator.getCurrentAllocated() == 0);
    assert(allocator.hasLeaks() == false);
    
    // Тест двойного освобождения (должен быть защищен)
    // allocator.deallocate(ptr2);  // Должно быть защищено
    
    std::cout << "Total allocated: " << allocator.getTotalAllocated() << "\n";
    std::cout << "Peak allocated: " << allocator.getPeakAllocated() << "\n";
    std::cout << "TrackingAllocator tests passed!\n";
}

int main() {
    testTrackingAllocator();
    return 0;
}

