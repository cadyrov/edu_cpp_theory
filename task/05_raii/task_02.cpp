#include <iostream>
#include <cassert>
#include <cstdio>
#include <stdexcept>

// Task 2: RAII для файлов
//
// Реализуйте класс File, который:
// 1. Открывает файл в конструкторе
// 2. Закрывает файл в деструкторе
// 3. Предоставляет методы для чтения/записи
// 4. Обрабатывает ошибки открытия файла

class File {
    FILE* handle_;
    
public:
    // TODO: Конструктор (открывает файл)
    File(const char* filename, const char* mode) {
        // TODO: откройте файл через fopen
        // TODO: если не удалось открыть, выбросьте исключение
    }
    
    // TODO: Деструктор (закрывает файл)
    ~File() {
        // TODO: закройте файл через fclose если handle_ не nullptr
    }
    
    // TODO: Запретить копирование
    File(const File&) = delete;
    File& operator=(const File&) = delete;
    
    // TODO: Метод для чтения строки
    bool readLine(char* buffer, size_t size) {
        // TODO: используйте fgets для чтения строки
        return false;
    }
    
    // TODO: Метод для записи строки
    bool writeLine(const char* line) {
        // TODO: используйте fprintf для записи
        return false;
    }
    
    // TODO: Проверка валидности файла
    bool isValid() const {
        // TODO: реализуйте проверку
        return false;
    }
};

// Код для проверки
void testFile() {
    // Создание файла для записи
    {
        File file("test.txt", "w");
        assert(file.isValid());
        file.writeLine("Hello, RAII!");
        file.writeLine("Test line");
        // Файл автоматически закроется при выходе из блока
    }
    
    // Чтение файла
    {
        File file("test.txt", "r");
        assert(file.isValid());
        
        char buffer[100];
        assert(file.readLine(buffer, sizeof(buffer)));
        // Проверка содержимого
    }
    
    // Тест обработки ошибки
    try {
        File file("nonexistent.txt", "r");
        assert(false);  // Не должно дойти сюда
    } catch (const std::exception& e) {
        // Ожидаемое исключение
    }
    
    std::cout << "File RAII tests passed!\n";
}

int main() {
    testFile();
    return 0;
}

