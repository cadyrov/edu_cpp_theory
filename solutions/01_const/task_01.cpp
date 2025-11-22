#include <string>
#include <vector>
#include <iostream>

// Task 1: Константность и геттеры
// Реализуйте геттеры для класса Configuration, обеспечив:
// 1. Защиту от модификации возвращаемых данных
// 2. Максимальную производительность
// 3. Следование best practices для const-correctness

class Configuration {
    std::string name_;
    int value_;
    std::vector<std::string> options_;
public:
    Configuration(std::string name, int value) 
        : name_(name), value_(value) {}
    
    // TODO: Реализуйте геттеры с правильной константностью
    int GetValue() const {
        // TODO: реализуйте
        return 0;
    }

    const std::string& GetName() const {
        // TODO: реализуйте
        return name_;
    }

    const std::vector<std::string>& GetOptions() const {
        // TODO: реализуйте
        return options_;
    }
    
};

// Код для проверки решения
void testConfiguration() {
    const Configuration cfg("test", 42);
    
    // Эти строки должны компилироваться:
    auto name = cfg.GetName();        // Получение имени
    auto value = cfg.GetValue();      // Получение значения
    auto& options = cfg.GetOptions(); // Получение опций
    
    std::cout << "Name: " << name << "\n";
    std::cout << "Value: " << value << "\n";
    std::cout << "Options size: " << options.size() << "\n";
    
    // Эти строки НЕ должны компилироваться:
    // cfg.GetOptions().push_back("new"); // Ошибка: нельзя модифицировать вектор
    // cfg.GetName().clear();             // Ошибка: нельзя модифицировать строку
}

int main() {
    testConfiguration();
    return 0;
}
