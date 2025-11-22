#include <iostream>
#include <cassert>

// Task 4: Права доступа к файлу
// 
// Реализуйте структуру FilePermissions, которая:
// 1. Хранит права доступа в стиле Unix (rwx) для owner, group и others
// 2. Позволяет устанавливать права в восьмеричном формате (chmod)
// 3. Имеет методы для проверки прав
// 4. Занимает минимально возможный размер
//
// Пример использования:
// FilePermissions fp;
// fp.setOctal(0644);  // rw-r--r--
// bool canWrite = fp.canGroupWrite();  // false

struct FilePermissions {
    // TODO: реализуйте структуру для хранения прав rwx для owner, group и others
    
    // Устанавливает права в восьмеричном формате (0-777)
    bool setOctal(unsigned int value) {
        // TODO: реализуйте метод
        return false;
    }
    
    // Методы проверки прав для владельца
    bool canOwnerRead() const {
        // TODO: реализуйте метод
        return false;
    }
    
    bool canOwnerWrite() const {
        // TODO: реализуйте метод
        return false;
    }
    
    bool canOwnerExecute() const {
        // TODO: реализуйте метод
        return false;
    }
    
    // Методы проверки прав для группы
    bool canGroupRead() const {
        // TODO: реализуйте метод
        return false;
    }
    
    bool canGroupWrite() const {
        // TODO: реализуйте метод
        return false;
    }
    
    bool canGroupExecute() const {
        // TODO: реализуйте метод
        return false;
    }
    
    // Методы проверки прав для остальных
    bool canOthersRead() const {
        // TODO: реализуйте метод
        return false;
    }
    
    bool canOthersWrite() const {
        // TODO: реализуйте метод
        return false;
    }
    
    bool canOthersExecute() const {
        // TODO: реализуйте метод
        return false;
    }
    
    // Выводит права в формате rwxrwxrwx
    friend std::ostream& operator<< (std::ostream& out, FilePermissions fp) {
        // TODO: реализуйте вывод
        return out;
    }
};

// Код для проверки
void testFilePermissions() {
    FilePermissions fp;
    
    // Тест установки прав в восьмеричном формате
    assert(fp.setOctal(0644));  // rw-r--r--
    
    // Проверка прав владельца
    assert(fp.canOwnerRead());
    assert(fp.canOwnerWrite());
    assert(!fp.canOwnerExecute());
    
    // Проверка прав группы
    assert(fp.canGroupRead());
    assert(!fp.canGroupWrite());
    assert(!fp.canGroupExecute());
    
    // Проверка прав остальных
    assert(fp.canOthersRead());
    assert(!fp.canOthersWrite());
    assert(!fp.canOthersExecute());
    
    // Тест некорректных значений
    assert(!fp.setOctal(01000));  // Некорректное восьмеричное число
    
    // Вывод текущих прав
    std::cout << fp;  // Должно вывести: rw-r--r--
}

int main() {
    testFilePermissions();
    return 0;
}
