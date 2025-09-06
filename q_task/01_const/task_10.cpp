#include <string>
#include <unordered_map>
#include <iostream>

// Task 10: Константные методы и mutable
// Реализуйте класс ExpensiveCalculator, который:
// 1. Имеет константный метод calculate(), выполняющий "дорогие" вычисления
// 2. Использует кэширование для оптимизации повторных вызовов
// 3. Правильно работает в константном контексте
// 4. Следует принципам логической константности

class ExpensiveCalculator {
private:
    // Подсказка: подумайте, какие поля должны быть mutable
    mutable std::unordered_map<int, int> cache_;

    // "Дорогое" вычисление
    int performCalculation(int input) const {
        // Симуляция сложных вычислений
        int result = 0;
        for(int i = 0; i <= input; ++i) {
            result += i * i;
        }
        return result;
    }

public:
    // Реализуйте этот метод
    int calculate(int input) const {
        // TODO: Используйте кэш, если результат уже был вычислен
        // В противном случае выполните вычисление и сохраните в кэш
        return 0; // Заглушка
    }

    // Бонусное задание: реализуйте метод для очистки кэша
    void clearCache() {
        // TODO: Очистите кэш
    }
};

// Код для проверки решения
void testCalculator() {
    const ExpensiveCalculator calc;
    
    // Первый вызов - должен выполнить вычисление
    std::cout << "First call for 5: " << calc.calculate(5) << "\n";
    
    // Второй вызов - должен использовать кэш
    std::cout << "Second call for 5: " << calc.calculate(5) << "\n";
    
    // Другое значение - новое вычисление
    std::cout << "First call for 10: " << calc.calculate(10) << "\n";
    
    // Проверка работы с разными значениями
    for(int i = 0; i < 5; ++i) {
        std::cout << "Value for " << i << ": " << calc.calculate(i) << "\n";
    }
}

int main() {
    testCalculator();
    return 0;
}
