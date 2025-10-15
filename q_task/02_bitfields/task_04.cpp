#include <iostream>

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
    static const unsigned int max_write=0777;
    // TODO: реализуйте структуру для хранения прав rwx для owner, group и others
    unsigned int owner:3;
    unsigned int group:3;
    unsigned int others:3;
    
    // Устанавливает права в восьмеричном формате (0-777)
    bool setOctal(unsigned int value) {
        if (value > max_write) {
            return false;
        }

        owner = (value >> 6) & 7; 
        group = (value >> 3) & 7; 
        others = value & 7; 

        return true;
    }
    
    // Методы проверки прав для владельца
    bool canOwnerRead() const {
        // TODO: реализуйте метод
        return owner&4;
    }
    
    bool canOwnerWrite() const {
        // TODO: реализуйте метод
        return owner&2;
    }
    
    bool canOwnerExecute() const {
        // TODO: реализуйте метод
        return owner&1;;
    }
    
    // Методы проверки прав для группы
    bool canGroupRead() const {
        // TODO: реализуйте метод
        return group&4;
    }
    
    bool canGroupWrite() const {
        // TODO: реализуйте метод
        return group&2;
    }
    
    bool canGroupExecute() const {
        // TODO: реализуйте метод
        return group&1;
    }
    
    // Методы проверки прав для остальных
    bool canOthersRead() const {
        // TODO: реализуйте метод
        return others&4;
    }
    
    bool canOthersWrite() const {
        // TODO: реализуйте метод
        return others&2;
    }
    
    bool canOthersExecute() const {
        // TODO: реализуйте метод
        return others&1;
    }
    
    // Выводит права в формате rwxrwxrwx
    friend std::ostream& operator<< (std::ostream& out, FilePermissions fp) {
        out << (fp.canOwnerRead()?"r":"-") <<(fp.canOwnerWrite()?"w":"-")<<(fp.canOwnerExecute()?"x":"-")<<
        (fp.canGroupRead()?"r":"-") <<(fp.canGroupWrite()?"w":"-")<<(fp.canGroupExecute()?"x":"-")<<
        (fp.canOthersRead()?"r":"-") <<(fp.canOthersWrite()?"w":"-")<<(fp.canOthersExecute()?"x":"-");

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
