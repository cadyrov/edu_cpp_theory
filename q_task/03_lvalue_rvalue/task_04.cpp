#include <iostream>
#include <cassert>
#include <string>

// Task 4: Perfect Forwarding
//
// Реализуйте функцию wrapper, которая сохраняет категорию значения:
// - Если передан L-value, он передается как L-value
// - Если передан R-value, он передается как R-value
// Используйте std::forward для perfect forwarding

class Processor {
public:
    // Функция для L-value
    void process(std::string& s) { s += " (L-value)"; }
    
    // Функция для R-value
    void process(std::string&& s) { s += " (R-value)"; }
};

template<typename T>
void wrapper(Processor& proc,T&& arg) {
    // std::forward сохраняет категорию значения
    proc.process(std::forward<T>(arg));
}

void testPerfectForwarding() {
    Processor proc;
    
    std::string text = "hello";

    wrapper(proc, text);
    assert(text.find("L-value") != std::string::npos);
    
    wrapper(proc, std::string("world"));
    
    std::cout << "Perfect forwarding tests passed!\n";
}

int main() {
    testPerfectForwarding();
    return 0;
}
