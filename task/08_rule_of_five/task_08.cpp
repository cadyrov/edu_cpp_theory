#include <iostream>
#include <cassert>
#include <string>
#include <vector>

// Task 8: Rule of Zero
//
// Реализуйте класс ModernContainer, который:
// 1. Использует только RAII-типы (string, vector, unique_ptr)
// 2. Не требует определения специальных функций
// 3. Демонстрирует что компилятор сгенерирует их автоматически

class ModernContainer {
    std::string name_;                    // RAII-тип
    std::vector<int> data_;               // RAII-тип
    std::string info_;                    // RAII-тип (заменен на string для копируемости)
    
public:
    // TODO: Конструктор
    ModernContainer(const std::string& name) : name_(name) {
        // TODO: инициализируйте name_
        // TODO: info_ уже инициализирован по умолчанию
    }
    
    // TODO: НЕ определяйте деструктор, конструктор копирования и т.д.
    // Компилятор сгенерирует их автоматически и правильно!
    
    // Методы для работы с данными
    void addData(int value) {
        data_.push_back(value);
    }
    
    void setInfo(const std::string& info) {
        info_ = info;
    }
    
    const std::string& getName() const { return name_; }
    const std::vector<int>& getData() const { return data_; }
    const std::string& getInfo() const { return info_; }
};

// Код для проверки
void testRuleOfZero() {
    // Создание
    ModernContainer c1("Container1");
    c1.addData(10);
    c1.addData(20);
    c1.setInfo("Info1");
    
    // Копирование (автоматически сгенерировано)
    ModernContainer c2 = c1;
    assert(c2.getName() == "Container1");
    assert(c2.getData().size() == 2);
    assert(c2.getData()[0] == 10);
    assert(c2.getData()[1] == 20);
    assert(c2.getInfo() == "Info1");
    
    // Изменение одного не влияет на другой (глубокое копирование)
    c2.addData(30);
    assert(c1.getData().size() == 2);
    assert(c2.getData().size() == 3);
    
    // Присваивание (автоматически сгенерировано)
    ModernContainer c3("Container3");
    c3 = c1;
    assert(c3.getName() == "Container1");
    
    // Перемещение (автоматически сгенерировано)
    ModernContainer c4 = std::move(c1);
    assert(c4.getName() == "Container1");
    assert(c4.getData().size() == 2);
    
    // Перемещающее присваивание
    ModernContainer c5("Temp");
    c5 = std::move(c4);
    assert(c5.getName() == "Container1");
    
    std::cout << "Rule of Zero tests passed!\n";
}

int main() {
    testRuleOfZero();
    return 0;
}

