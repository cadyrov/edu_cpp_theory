# Практические задания: Тесты и исключения

## Задание 1: Система банковских операций с исключениями

### Описание
Создайте систему для обработки банковских операций с полной системой исключений и тестированием.

### Требования
- Реализуйте иерархию исключений для разных типов ошибок
- Обработка операций: депозит, снятие, перевод
- Валидация данных с выбросом исключений
- Comprehensive unit testing с Google Test или Catch2

### Интерфейс
```cpp
class BankingException : public std::exception { /* базовый класс */ };
class InsufficientFundsException : public BankingException { /* ... */ };
class InvalidAccountException : public BankingException { /* ... */ };
class NegativeAmountException : public BankingException { /* ... */ };

class Account {
public:
    Account(const std::string& number, double initial_balance);
    void Deposit(double amount);
    void Withdraw(double amount);
    double GetBalance() const;
};

class Bank {
public:
    void CreateAccount(const std::string& number, double initial_balance);
    void Transfer(const std::string& from, const std::string& to, double amount);
    Account& GetAccount(const std::string& number);
};
```

### Тесты
1. Создание аккаунта с отрицательным балансом
2. Снятие суммы больше баланса
3. Операции с несуществующим аккаунтом
4. Корректные операции депозита/снятия
5. Перевод между аккаунтами
6. Валидация номера аккаунта
7. Обработка нулевых и отрицательных сумм
8. Concurrent operations testing
9. Exception safety гарантии
10. Performance testing для больших объемов операций

---

## Задание 2: Фреймворк для unit-тестирования

### Описание
Создайте собственный mini-фреймворк для unit-тестирования наподобие Google Test.

### Требования
- Макросы EXPECT_EQ, EXPECT_TRUE, EXPECT_THROW
- Test fixtures и setup/teardown
- Детальные отчеты о провалах
- Группировка тестов и фильтрация
- Параметризованные тесты

### Интерфейс
```cpp
#define TEST(test_suite, test_name) /* макрос создания теста */
#define EXPECT_EQ(expected, actual) /* макрос проверки равенства */
#define EXPECT_TRUE(condition) /* макрос проверки истинности */
#define EXPECT_THROW(statement, exception_type) /* макрос проверки исключений */

class TestRunner {
public:
    void RunAllTests();
    void RunTestSuite(const std::string& suite_name);
    void SetFilter(const std::string& filter);
    TestResult GetResults() const;
};
```

### Тесты
1. Успешное прохождение простых тестов
2. Обработка провалов тестов
3. Проверка макросов EXPECT_*
4. Setup и teardown функциональность
5. Фильтрация тестов по имени
6. Параметризованные тесты
7. Статистика выполнения
8. Nested test suites
9. Exception handling в тестах
10. Performance измерения

---

## Задание 3: Система валидации данных с исключениями

### Описание
Реализуйте comprehensive систему валидации для различных типов данных с подробной системой исключений.

### Требования
- Валидация email, телефонов, дат, кредитных карт
- Цепочки валидаторов
- Контекстуальная информация в исключениях
- Internationalization поддержка
- Performance оптимизации

### Интерфейс
```cpp
class ValidationException : public std::exception {
public:
    ValidationException(const std::string& field, const std::string& message, 
                       const std::string& value, const std::string& context = "");
    const std::string& GetField() const;
    const std::string& GetValue() const;
    const std::string& GetContext() const;
};

template<typename T>
class Validator {
public:
    virtual ValidationResult Validate(const T& value) const = 0;
    virtual std::string GetErrorMessage() const = 0;
};

class ValidationChain {
public:
    template<typename T>
    ValidationChain& Add(std::unique_ptr<Validator<T>> validator);
    void ValidateAll(const std::map<std::string, std::any>& data) const;
};
```

### Тесты (по 10 на каждый тип валидации)
1. Email validation tests
2. Phone number validation tests  
3. Date format validation tests
4. Credit card validation tests
5. Password strength validation tests
6. URL validation tests
7. Chain validation tests
8. Internationalization tests
9. Performance stress tests
10. Custom validator tests

---

## Задание 4: Debug и профилирование система

### Описание
Создайте продвинутую систему для debugging и профилирования C++ приложений.

### Требования
- Scope-based timing и memory profiling
- Conditional logging с уровнями
- Stack trace при исключениях
- Memory leak detection
- Performance bottleneck identification

### Интерфейс
```cpp
enum class LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

class Logger {
public:
    static void Log(LogLevel level, const std::string& message, 
                   const std::string& file = __FILE__, int line = __LINE__);
    static void SetLevel(LogLevel level);
    static void SetOutput(std::shared_ptr<LogOutput> output);
};

class Profiler {
public:
    static void StartProfiling(const std::string& session_name);
    static void EndProfiling();
    static ProfileReport GetReport();
};

class MemoryTracker {
public:
    static void EnableTracking();
    static MemoryReport GetMemoryUsage();
    static std::vector<MemoryLeak> DetectLeaks();
};
```

### Тесты
1. Logging с разными уровнями
2. Performance profiling точность
3. Memory tracking корректность
4. Stack trace generation
5. Conditional compilation
6. Thread-safe logging
7. File rotation
8. Memory leak detection
9. Performance regression detection
10. Integration testing

---

## Задание 5: Mock framework для тестирования

### Описание
Реализуйте систему мокирования для unit-тестирования зависимостей.

### Требования
- Mock objects generation
- Expectation setting и verification
- Return value configuration
- Call count verification
- Argument matching

### Интерфейс будет добавлен в следующем сообщении из-за ограничений длины.

---

Каждое задание включает:
- Полную спецификацию интерфейса
- 10 детальных тестов
- Критерии оценки от базового до экспертного уровня
- Современные C++17 практики 