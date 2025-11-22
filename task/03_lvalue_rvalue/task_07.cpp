#include <iostream>
#include <cassert>
#include <string>
#include <utility>

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
    Logger(const Logger& other) {
        // TODO: реализуйте
    }
    // TODO: реализуйте move constructor (с логированием)
    Logger(Logger&& other) {
        // TODO: реализуйте
    }
    
    // TODO: реализуйте copy assignment (с логированием)
    Logger& operator=(const Logger& other) {
        // TODO: реализуйте
        return *this;
    }
    // TODO: реализуйте move assignment (с логированием)
    Logger& operator=(Logger&& other) {
        // TODO: реализуйте
        return *this;
    }

    static void reset() { copy_count = 0; move_count = 0; }
    static int getCopyCount() { return copy_count; }
    static int getMoveCount() { return move_count; }
    
    std::string getData() const { return data_; }
};

// TODO: инициализация static переменных
int Logger::copy_count = 0;
int Logger::move_count = 0;

Logger createLogger() {
    // TODO: return Logger("created");
    return Logger("created");
}

void testRVO() {
    Logger::reset();
    Logger log = createLogger();
    
    assert(Logger::getCopyCount() == 0);
    
    std::cout << "RVO tests passed!\n";
}

int main() {
    testRVO();
    return 0;
}
