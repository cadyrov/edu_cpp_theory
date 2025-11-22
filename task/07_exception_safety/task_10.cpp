#include <iostream>
#include <cassert>
#include <memory>
#include <vector>
#include <stdexcept>
#include <mutex>

// Task 10: Комбинированная задача - полная exception safety
//
// Реализуйте класс SafeBankAccount, который:
// 1. Использует базовую гарантию для управления ресурсами
// 2. Использует строгую гарантию для операций перевода
// 3. Использует no-throw гарантию для простых операций
// 4. Правильно обрабатывает исключения во всех методах

class SafeBankAccount {
    std::string name_;
    double balance_;
    std::mutex mutex_;
    std::vector<std::unique_ptr<int>> transactions_;  // История транзакций
    
public:
    // TODO: Конструктор
    SafeBankAccount(const std::string& name, double initial_balance) 
        : name_(name), balance_(initial_balance) {
        // TODO: валидируйте initial_balance (должен быть >= 0)
        // TODO: если невалидно, выбросьте std::invalid_argument
    }
    
    // TODO: Метод получения баланса (noexcept, базовая гарантия)
    double getBalance() const noexcept {
        // TODO: используйте lock_guard для защиты
        // TODO: верните баланс
        return 0.0;
    }
    
    // TODO: Метод депозита (строгая гарантия)
    void deposit(double amount) {
        // TODO: валидируйте amount (должен быть > 0)
        // TODO: используйте lock_guard
        // TODO: сохраните старое состояние
        // TODO: выполните депозит
        // TODO: при исключении откатите изменения
    }
    
    // TODO: Метод снятия (строгая гарантия)
    void withdraw(double amount) {
        // TODO: валидируйте amount (должен быть > 0)
        // TODO: проверьте достаточность средств
        // TODO: используйте строгую гарантию для атомарного изменения
        // TODO: при недостатке средств выбросьте std::runtime_error
    }
    
    // TODO: Метод перевода (строгая гарантия)
    void transfer(SafeBankAccount& to, double amount) {
        // TODO: используйте lock для двух мьютексов одновременно
        // TODO: сохраните состояние обоих счетов
        // TODO: выполните перевод атомарно
        // TODO: при исключении откатите оба счета
    }
    
    // TODO: Метод добавления транзакции в историю
    void addTransaction(int transaction_id) {
        // TODO: добавьте транзакцию в transactions_
        // TODO: используйте базовую гарантию (память освободится при исключении)
    }
    
    const std::string& getName() const { return name_; }
    size_t getTransactionCount() const { return transactions_.size(); }
};

// Код для проверки
void testCompleteExceptionSafety() {
    // Создание счетов
    SafeBankAccount acc1("Alice", 1000.0);
    SafeBankAccount acc2("Bob", 500.0);
    
    assert(acc1.getBalance() == 1000.0);
    assert(acc2.getBalance() == 500.0);
    
    // Тест депозита
    acc1.deposit(200.0);
    assert(acc1.getBalance() == 1200.0);
    
    // Тест снятия
    acc1.withdraw(100.0);
    assert(acc1.getBalance() == 1100.0);
    
    // Тест перевода
    acc1.transfer(acc2, 150.0);
    assert(acc1.getBalance() == 950.0);
    assert(acc2.getBalance() == 650.0);
    
    // Тест что перевод атомарный (при исключении оба счета откатываются)
    double old_balance1 = acc1.getBalance();
    double old_balance2 = acc2.getBalance();
    
    try {
        acc1.transfer(acc2, 10000.0);  // Недостаточно средств
        assert(false);
    } catch (const std::runtime_error& e) {
        // Оба счета должны остаться в исходном состоянии
        assert(acc1.getBalance() == old_balance1);
        assert(acc2.getBalance() == old_balance2);
    }
    
    // Тест добавления транзакций
    acc1.addTransaction(1);
    acc1.addTransaction(2);
    assert(acc1.getTransactionCount() == 2);
    
    // Тест создания с невалидным балансом
    try {
        SafeBankAccount acc3("Invalid", -100.0);
        assert(false);
    } catch (const std::invalid_argument& e) {
        // Ожидаемое исключение
    }
    
    // Проверка что getBalance noexcept
    static_assert(noexcept(std::declval<SafeBankAccount>().getBalance()),
                  "getBalance should be noexcept");
    
    std::cout << "Complete exception safety tests passed!\n";
}

int main() {
    testCompleteExceptionSafety();
    return 0;
}

