#include <iostream>
#include <cassert>
#include <stdexcept>

// Task 6: Деструктор и управление ресурсами
//
// Реализуйте класс FileHandle, который:
// 1. Правильно освобождает ресурсы в деструкторе
// 2. Использует RAII принцип
// 3. Гарантирует освобождение даже при исключениях

class FileHandle {
    FILE* handle_;
    bool is_open_;
    
public:
    // TODO: Конструктор (открывает файл)
    FileHandle(const char* filename, const char* mode) : handle_(nullptr), is_open_(false) {
        // TODO: откройте файл через fopen
        // TODO: установите is_open_ в true если успешно
    }
    
    // TODO: Деструктор (закрывает файл)
    ~FileHandle() {
        // TODO: если файл открыт, закройте его через fclose
        // TODO: деструктор должен быть noexcept (неявно)
    }
    
    // Запретить копирование и перемещение для простоты
    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;
    FileHandle(FileHandle&&) = delete;
    FileHandle& operator=(FileHandle&&) = delete;
    
    // Методы работы с файлом
    bool write(const char* data) {
        if (is_open_ && handle_) {
            return fprintf(handle_, "%s", data) >= 0;
        }
        return false;
    }
    
    bool isValid() const { return is_open_ && handle_ != nullptr; }
};

// Код для проверки
void testDestructor() {
    // Нормальное использование
    {
        FileHandle file("test_destructor.txt", "w");
        assert(file.isValid());
        file.write("Test data");
        // При выходе из блока деструктор закроет файл
    }
    
    // Проверка что файл закрыт
    {
        FileHandle file("test_destructor.txt", "r");
        assert(file.isValid());
        // Файл можно открыть заново, значит предыдущий закрыт
    }
    
    // Тест что деструктор вызывается даже при исключении
    try {
        FileHandle file("test_exception.txt", "w");
        assert(file.isValid());
        throw std::runtime_error("Test exception");
    } catch (...) {
        // Деструктор должен был закрыть файл
    }
    
    // Проверка что файл закрыт после исключения
    {
        FileHandle file("test_exception.txt", "r");
        assert(file.isValid());
    }
    
    std::cout << "Destructor tests passed!\n";
}

int main() {
    testDestructor();
    return 0;
}

