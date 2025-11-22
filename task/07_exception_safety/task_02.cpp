#include <iostream>
#include <cassert>
#include <string>

// Task 2: Строгая гарантия exception safety
//
// Реализуйте класс Account, который:
// 1. Предоставляет строгую гарантию при операциях
// 2. Использует copy-and-swap для атомарных изменений
// 3. Откатывает изменения при исключениях

class Account {
    std::string name_;
    double balance_;
    
public:
    Account(const std::string& name, double balance) 
        : name_(name), balance_(balance) {}
    
    // TODO: Метод обновления с строгой гарантией
    void updateAccount(const std::string& new_name, double new_balance) {
        // TODO: создайте временную копию текущего состояния
        // TODO: выполните изменения на копии
        // TODO: если все успешно, замените текущее состояние (swap)
        // TODO: при исключении состояние не должно измениться
    }
    
    // TODO: Метод перевода с строгой гарантией
    void transfer(Account& to, double amount) {
        // TODO: сохраните старое состояние обоих счетов
        // TODO: выполните перевод
        // TODO: при исключении восстановите старое состояние
        // TODO: используйте try-catch для отката изменений
    }
    
    const std::string& getName() const { return name_; }
    double getBalance() const { return balance_; }
};

// Код для проверки
void testStrongGuarantee() {
    // Тест обновления с успешным выполнением
    Account acc1("Alice", 100.0);
    acc1.updateAccount("Alice Smith", 150.0);
    assert(acc1.getName() == "Alice Smith");
    assert(acc1.getBalance() == 150.0);
    
    // Тест перевода
    Account acc2("Bob", 50.0);
    Account acc3("Charlie", 200.0);
    
    double old_balance2 = acc2.getBalance();
    double old_balance3 = acc3.getBalance();
    
    acc2.transfer(acc3, 25.0);
    assert(acc2.getBalance() == old_balance2 - 25.0);
    assert(acc3.getBalance() == old_balance3 + 25.0);
    
    // Тест что при исключении состояние не меняется
    Account acc4("Test", 100.0);
    std::string old_name = acc4.getName();
    double old_balance = acc4.getBalance();
    
    try {
        // Симуляция операции которая может выбросить исключение
        acc4.updateAccount("", -100.0);  // Невалидные данные
        // Если дошли сюда, проверяем что состояние не изменилось
    } catch (...) {
        // При исключении состояние должно остаться прежним
        assert(acc4.getName() == old_name);
        assert(acc4.getBalance() == old_balance);
    }
    
    std::cout << "Strong guarantee tests passed!\n";
}

int main() {
    testStrongGuarantee();
    return 0;
}

