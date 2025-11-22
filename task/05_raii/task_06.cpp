#include <iostream>
#include <cassert>
#include <memory>
#include <cstdio>

// Task 6: Кастомные делитеры
//
// Реализуйте класс FilePtr, который:
// 1. Использует std::unique_ptr с кастомным делитером для файлов
// 2. Автоматически закрывает файл при уничтожении
// 3. Демонстрирует использование кастомных делитеров

// TODO: Кастомный делитер для FILE*
struct FileDeleter {
    void operator()(FILE* file) const {
        // TODO: реализуйте закрытие файла
    }
};

// TODO: Алиас для удобства
using FilePtr = std::unique_ptr<FILE, FileDeleter>;

// TODO: Функция для создания FilePtr
FilePtr openFile(const char* filename, const char* mode) {
    // TODO: откройте файл и создайте FilePtr
    return FilePtr(nullptr);
}

// Код для проверки
void testCustomDeleter() {
    // Создание файла для записи
    {
        FilePtr file = openFile("custom_test.txt", "w");
        assert(file != nullptr);
        
        fprintf(file.get(), "Hello from custom deleter!\n");
        // Файл автоматически закроется при выходе из блока
    }
    
    // Чтение файла
    {
        FilePtr file = openFile("custom_test.txt", "r");
        assert(file != nullptr);
        
        char buffer[100];
        fgets(buffer, sizeof(buffer), file.get());
        // Проверка содержимого
    }
    
    // Тест с nullptr
    {
        FilePtr file(nullptr);
        // Не должно быть ошибки при уничтожении
    }
    
    std::cout << "Custom deleter tests passed!\n";
}

int main() {
    testCustomDeleter();
    return 0;
}

