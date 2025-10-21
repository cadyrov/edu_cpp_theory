#include <iostream>
#include <cassert>
#include <string>

// Task 7: RVO (Return Value Optimization) и оптимизация перемещением
//
// Создайте класс Logger, который отслеживает копирования и перемещения.
// Покажите как RVO избегает копирования даже без std::move.

class Logger {
    std::string data_;
    static int copy_count;
    static int move_count;
public:
    Logger(const std::string& s) : data_(s) {}
    
    // TODO: реализуйте copy constructor (с логированием)
    // TODO: реализуйте move constructor (с логированием)
    
    // TODO: реализуйте copy assignment (с логированием)
    // TODO: реализуйте move assignment (с логированием)
    
    static void reset() { copy_count = 0; move_count = 0; }
    static int getCopyCount() { return copy_count; }
    static int getMoveCount() { return move_count; }
    
    std::string getData() const { return data_; }
};

// TODO: инициализация static переменных

Logger createLogger() {
    // TODO: return Logger("created");
    // Компилятор применит RVO и избежит копирования
}

void testRVO() {
    Logger::reset();
    Logger log = createLogger();
    
    // TODO: assert(Logger::getCopyCount() == 0);
    
    std::cout << "RVO tests passed!\n";
}

int main() {
    testRVO();
    return 0;
}
