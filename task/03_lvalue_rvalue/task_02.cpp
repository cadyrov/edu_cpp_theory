#include <algorithm>
#include <iostream>
#include <cassert>
#include <string>

// Task 2: Привязка ссылок к разным типам значений
//
// Реализуйте класс StringContainer, который хранит строку.
// Методы должны корректно работать с L-value и R-value:
// - setString(const std::string& s) - для L-value
// - setString(std::string&& s) - для R-value

class StringContainer {
    std::string data_;
public:
    StringContainer() = default;
    
    // TODO: Для L-value - копируем
    void setString(const std::string& s) {
        // TODO: реализуйте
    }

    // TODO: Для R-value - перемещаем
    void setString(std::string&& s) {
        // TODO: реализуйте
    }

    std::string getString() const { return data_; }
};

void testStringBinding() {
    StringContainer container;
    
    // L-value: существующая строка
    std::string existing = "hello";
    container.setString(existing);
    assert(container.getString() == "hello");
    
    // R-value: временная строка
    container.setString("world");
    assert(container.getString() == "world");
    
    std::cout << "String binding tests passed!\n";
}

int main() {
    testStringBinding();
    return 0;
}
