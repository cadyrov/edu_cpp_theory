#include <iostream>
#include <cassert>
#include <memory>

// Task 4: Кастомные делитеры для умных указателей
//
// Реализуйте класс FilePtr, который:
// 1. Использует unique_ptr с кастомным делитером для FILE*
// 2. Автоматически закрывает файл при уничтожении
// 3. Демонстрирует использование кастомных делитеров

#include <cstdio>

// TODO: Кастомный делитер для FILE*
struct FileDeleter {
    void operator()(FILE* file) const {
        // TODO: закройте файл через fclose
    }
};

// TODO: Алиас для удобства
using FilePtr = std::unique_ptr<FILE, FileDeleter>;

// TODO: Функция для открытия файла
FilePtr openFile(const char* filename, const char* mode) {
    // TODO: откройте файл через fopen
    // TODO: создайте FilePtr с кастомным делитером
    return FilePtr(nullptr);
}

// Код для проверки
void testCustomDeleter() {
    // Создание файла для записи
    {
        FilePtr file = openFile("test_custom.txt", "w");
        assert(file != nullptr);
        
        fprintf(file.get(), "Hello from custom deleter!\n");
        // Файл автоматически закроется при выходе из блока
    }
    
    // Чтение файла
    {
        FilePtr file = openFile("test_custom.txt", "r");
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

