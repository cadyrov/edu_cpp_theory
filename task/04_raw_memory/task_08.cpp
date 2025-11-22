#include <iostream>
#include <cassert>
#include <cstddef>

// Task 8: Пул памяти (Memory Pool)
//
// Реализуйте класс MemoryPool, который:
// 1. Предварительно выделяет большой блок памяти
// 2. Раздает из него маленькие блоки фиксированного размера
// 3. Поддерживает возврат блоков в пул для повторного использования
// 4. Эффективно управляет свободными блоками

class MemoryPool {
    void* pool_;
    size_t pool_size_;
    size_t block_size_;
    size_t block_count_;
    void* free_list_;  // Список свободных блоков
    
public:
    // TODO: Конструктор (выделяет пул памяти)
    MemoryPool(size_t block_size, size_t block_count) {
        // TODO: реализуйте выделение пула и инициализацию free_list
    }
    
    // TODO: Деструктор (освобождает весь пул)
    ~MemoryPool() {
        // TODO: реализуйте освобождение пула
    }
    
    // TODO: Выделить блок из пула
    void* allocate() {
        // TODO: реализуйте выделение блока из free_list
        return nullptr;
    }
    
    // TODO: Вернуть блок в пул
    void deallocate(void* ptr) {
        // TODO: реализуйте возврат блока в free_list
    }
    
    size_t getBlockSize() const { return block_size_; }
    size_t getBlockCount() const { return block_count_; }
};

// Код для проверки
void testMemoryPool() {
    const size_t block_size = 64;
    const size_t block_count = 10;
    
    MemoryPool pool(block_size, block_count);
    
    // Выделение нескольких блоков
    void* block1 = pool.allocate();
    void* block2 = pool.allocate();
    void* block3 = pool.allocate();
    
    assert(block1 != nullptr);
    assert(block2 != nullptr);
    assert(block3 != nullptr);
    assert(block1 != block2);
    assert(block2 != block3);
    
    // Использование блоков
    int* int_ptr = static_cast<int*>(block1);
    int_ptr[0] = 42;
    assert(int_ptr[0] == 42);
    
    // Возврат блоков в пул
    pool.deallocate(block1);
    pool.deallocate(block2);
    
    // Повторное использование
    void* block4 = pool.allocate();
    assert(block4 != nullptr);
    
    pool.deallocate(block3);
    pool.deallocate(block4);
    
    std::cout << "MemoryPool tests passed!\n";
}

int main() {
    testMemoryPool();
    return 0;
}

