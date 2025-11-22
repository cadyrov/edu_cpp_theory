#include <string>
#include <vector>
#include <utility>
#include <iostream>

// Task 3: Константные итераторы
// 
// Реализуйте класс ReadOnlyVector, который:
// 1. Хранит вектор строк
// 2. Предоставляет только read-only доступ к элементам
// 3. Позволяет итерироваться по элементам, но не изменять их
// 4. Имеет методы size() и empty()

class ReadOnlyVector {
    std::vector<std::string> data_;

public:
    using const_iterator = std::vector<std::string>::const_iterator;
    // TODO: Реализуйте:
    // 1. Конструктор из vector<string>
    ReadOnlyVector(std::vector<std::string> data) {
        // TODO: реализуйте
    }

    // 2. begin() и end(), возвращающие константные итераторы
    const_iterator begin() const {
        // TODO: реализуйте
        return data_.begin();
    }

    const_iterator end() const {
        // TODO: реализуйте
        return data_.end();
    }
    // 3. size() и empty()
    size_t size() const {
        // TODO: реализуйте
        return 0;
    }

    bool empty() const {
        // TODO: реализуйте
        return true;
    }

    // 4. operator[] для константного доступа к элементам
    const std::string& operator[](size_t idx) const {
        // TODO: реализуйте
        static std::string empty;
        return empty;
    }
    
};

// Код для проверки
void testReadOnlyVector() {
    std::vector<std::string> data = {"one", "two", "three"};
    const ReadOnlyVector ro(data);
    
    // Проверка размера
    std::cout << "Size: " << ro.size() << "\n";
    std::cout << "Empty: " << ro.empty() << "\n";
    
    // Проверка доступа к элементам
    std::cout << "First element: " << ro[0] << "\n";
    
    // Проверка итерации
    for (const auto& item : ro) {
        std::cout << item << " ";
    }
    std::cout << "\n";
    
    // Эти строки НЕ должны компилироваться:
    // ro[0] = "new";                    // Нельзя изменять элементы
    // auto it = ro.begin(); *it = "new"; // Нельзя изменять через итератор
}

int main() {
    testReadOnlyVector();
    return 0;
}
