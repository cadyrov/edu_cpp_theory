Вы работаете над новой функцией банковской системы учёта операций. 

Эта функция должна добавлять новую запись в локальное хранилище и в основную базу, а затем обновлять GUI. Текущая реализация — настоящий спагетти-код с кучей try/catch и ручными откатами.

Скопируйте код ниже к себе и перепишите его с помощью макроса BOOST_SCOPE_DEFER из библиотеки Boost.Scope и класса boost::scope_fail по следующему алгоритму:

Перепишите функцию InsertOperation, чтобы убрать try/catch.

Используйте три ScopeGuard:
- Первый BOOST_SCOPE_DEFER откатывает запись в локальном хранилище, если функция не завершилась успешно.
- Второй BOOST_SCOPE_DEFER откатывает запись в базе, если функция не завершилась успешно.
- Третий boost::scope_fail логирует сообщение об ошибке (например, "InsertOperation failed!").

Убедитесь, что в случае успеха функция выводит "Operation inserted successfully!".

```cpp
#include <iostream>
#include <print>
#include <random>
#include <stdexcept>
#include <string>

void MaybeThrow() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(0, 1);

    if (dist(gen) == 0) {
        std::println(std::cerr, "Throw an error");
        throw std::runtime_error("Random failure occurred!");
    }
}

struct FinancialOperation {
    std::string name;
};

struct LocalStorage {
    void PushBack(const FinancialOperation &op) {
        std::println("Local push: {}", op.name);
        MaybeThrow();
    }
    void PopBack() noexcept { std::println("Local pop"); }
} localStorage;

struct Database {
    void PushBack(const FinancialOperation &op) {
        std::println("DB push: {}", op.name);
        MaybeThrow();
    }
    void PopBack() noexcept { std::println("DB pop"); }
} db;

struct WebAPI {
    void UpdateCurrentOp(const FinancialOperation &op) {
        std::println("GUI push: {}", op.name);
        MaybeThrow();
    }
} webApi;

void InsertOperation(const FinancialOperation &op) {
    // Плохой код, который нужно переписать
    try {
        localStorage.PushBack(op);
    } catch (const std::exception &) {
        std::println("InsertOperation failed!");
        throw;
    }

    try {
        db.PushBack(op);
    } catch (const std::exception &) {
        std::println("InsertOperation failed!");
        std::println(std::cerr, "Revert changes in localStorage");
        localStorage.PopBack();
        throw;
    }

    try {
        webApi.UpdateCurrentOp(op);
    } catch (const std::exception &) {
        std::println("InsertOperation failed!");
        std::println(std::cerr, "Revert changes in db");
        db.PopBack();
        std::println(std::cerr, "Revert changes in localStorage");
        localStorage.PopBack();
        throw;
    }

    std::println("Operation inserted successfully!");
}

int main() {
    for (int i = 0; i < 5; ++i) {
        std::println("===== Start new operation =====");
        try {
            InsertOperation({"Pay rent"});
        } catch (...) {
            std::println("Caught an exception");
        }
    }
}
```

    - Помните, что ScopeGuard выполняется в порядке, обратном его созданию.
    - Используйте BOOST_SCOPE_DEFER для любых операций, которые должны выполняться независимо от состояния функции.
    - Используйте boost::scope::scope_fail, чтобы выполнять действия только при возникновении исключения.
    - Убедитесь, что никакие try/catch внутри InsertOperation не нужны.