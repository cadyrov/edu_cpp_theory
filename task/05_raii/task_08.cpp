#include <iostream>
#include <cassert>
#include <memory>
#include <vector>
#include <cstring>
#include <mutex>
#include <cstdio>

// Task 8: RAII для различных ресурсов
//
// Реализуйте класс MultiResource, который:
// 1. Управляет несколькими типами ресурсов (память, файлы, мьютексы)
// 2. Использует RAII для каждого типа ресурса
// 3. Правильно освобождает все ресурсы

class MultiResource {
    // TODO: Ресурсы разных типов
    std::unique_ptr<int[]> memory_;
    std::vector<std::unique_ptr<FILE, decltype(&fclose)>> files_;
    std::vector<std::unique_ptr<std::mutex>> mutexes_;
    
public:
    // TODO: Конструктор
    MultiResource(size_t memory_size, size_t file_count, size_t mutex_count) {
        // TODO: выделите память
        // TODO: откройте файлы
        // TODO: создайте мьютексы
    }
    
    // TODO: Деструктор не нужен (правило нуля)
    // Все ресурсы освободятся автоматически
    
    // Методы доступа
    int* getMemory() { return memory_.get(); }
    
    FILE* getFile(size_t index) {
        // TODO: верните указатель на файл по индексу
        return nullptr;
    }
    
    std::mutex* getMutex(size_t index) {
        // TODO: верните указатель на мьютекс по индексу
        return nullptr;
    }
    
    size_t getFileCount() const { return files_.size(); }
    size_t getMutexCount() const { return mutexes_.size(); }
};

// Код для проверки
void testMultiResource() {
    MultiResource res(100, 2, 3);
    
    assert(res.getMemory() != nullptr);
    assert(res.getFileCount() == 2);
    assert(res.getMutexCount() == 3);
    
    // Использование памяти
    res.getMemory()[0] = 42;
    assert(res.getMemory()[0] == 42);
    
    // Использование файлов
    FILE* file1 = res.getFile(0);
    assert(file1 != nullptr);
    
    // Использование мьютексов
    std::mutex* mutex1 = res.getMutex(0);
    assert(mutex1 != nullptr);
    
    // При выходе из функции все ресурсы освободятся автоматически
    std::cout << "MultiResource tests passed!\n";
}

int main() {
    testMultiResource();
    return 0;
}

