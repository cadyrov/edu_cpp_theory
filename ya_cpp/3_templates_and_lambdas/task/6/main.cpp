#include <iostream>
#include <string>

class Logger {
public:
    Logger(std::ostream &stream, const std::string &separator = ", ");
   
    void log() {
        
    }
};

int main() {
    Logger logger(std::cout, ", ");  // Разделитель между аргументами

    logger.log("User logged in", 42, 3.14, "Hello, world!");
    // Пример вывода:
    // [2023-10-05 12:34:56] User logged in, 42, 3.14, Hello, world!

    logger.log("Processing data", 100, 200, 300);
    // Пример вывода:
    // [2023-10-05 12:34:57] Processing data, 100, 200, 300

    return 0;
} 