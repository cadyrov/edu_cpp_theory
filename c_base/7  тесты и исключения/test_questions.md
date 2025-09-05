# Тест по теме "Тесты и исключения в C++" (40 вопросов)

## Вопрос 1
Что такое юнит-тест?

A) Тест, который проверяет работу всей программы целиком
B) Тест, который проверяет работу отдельных частей кода (функций, методов)
C) Тест, который проверяет только пользовательский интерфейс
D) Тест, который проверяет только производительность

## Вопрос 2
Какие основные принципы должны соблюдать юнит-тесты?

A) Быть медленными и зависимыми друг от друга
B) Быть автоматическими, независимыми и быстрыми
C) Требовать ручного ввода данных
D) Тестировать только успешные сценарии

## Вопрос 3
Что выведет следующий код?
```cpp
#include <cassert>
int main() {
    int x = 5;
    assert(x > 10);
    std::cout << "Test passed" << std::endl;
    return 0;
}
```

A) Test passed
B) Программа завершится с ошибкой
C) Ничего не выведет
D) Ошибка компиляции

## Вопрос 4
Что означает TDD (Test-Driven Development)?

A) Написание тестов после реализации кода
B) Написание тестов одновременно с кодом
C) Написание тестов до реализации кода
D) Отказ от написания тестов

## Вопрос 5
Какой заголовочный файл нужно подключить для использования assert?

A) `#include <assert>`
B) `#include <cassert>`
C) `#include <test>`
D) `#include <debug>`

## Вопрос 6
Что произойдет при выполнении этого кода в Google Test?
```cpp
TEST(MathTest, Addition) {
    EXPECT_EQ(2 + 2, 5);
    EXPECT_EQ(3 + 3, 6);
}
```

A) Тест пройдет успешно
B) Тест упадет на первой проверке и не выполнит вторую
C) Тест упадет на первой проверке, но выполнит вторую
D) Ошибка компиляции

## Вопрос 7
В чем разница между EXPECT_EQ и ASSERT_EQ в Google Test?

A) Никакой разницы нет
B) EXPECT_EQ продолжает выполнение теста при ошибке, ASSERT_EQ завершает тест
C) ASSERT_EQ продолжает выполнение теста при ошибке, EXPECT_EQ завершает тест
D) EXPECT_EQ работает только с числами

## Вопрос 8
Что такое мок (mock) в контексте тестирования?

A) Ошибка в тестах
B) Объект, который имитирует поведение реального компонента
C) Тип данных для тестирования
D) Специальный макрос для тестов

## Вопрос 9
Какой макрос используется в Catch2 для создания теста?

A) `TEST`
B) `TEST_CASE`
C) `UNIT_TEST`
D) `CREATE_TEST`

## Вопрос 10
Что выведет следующий код?
```cpp
#include <QDebug>
int main() {
    qDebug() << "Debug message";
    qInfo() << "Info message";
    return 0;
}
```

A) Только Debug message
B) Только Info message
C) Debug message и Info message
D) Ошибка компиляции

## Вопрос 11
Что такое логирование?

A) Процесс удаления ошибок из кода
B) Запись информации о работе программы в файлы или консоль
C) Процесс компиляции программы
D) Тестирование пользовательского интерфейса

## Вопрос 12
Какие уровни логирования существуют (от наименее к наиболее критичным)?

A) DEBUG, INFO, WARN, ERROR, CRITICAL
B) INFO, DEBUG, WARN, ERROR, CRITICAL
C) ERROR, WARN, INFO, DEBUG, CRITICAL
D) CRITICAL, ERROR, WARN, INFO, DEBUG

## Вопрос 13
Что делает точка остановки (breakpoint) в отладчике?

A) Удаляет строку кода
B) Приостанавливает выполнение программы на указанной строке
C) Исправляет ошибки автоматически
D) Компилирует программу

## Вопрос 14
Какая клавиша используется для пошагового выполнения кода в Qt Creator (Step Over)?

A) F5
B) F9
C) F10
D) F11

## Вопрос 15
Что такое исключение (exception) в C++?

A) Ошибка компиляции
B) Специальный объект, создаваемый в исключительных ситуациях
C) Комментарий в коде
D) Тип данных

## Вопрос 16
Что выведет следующий код?
```cpp
try {
    std::vector<int> vec = {1, 2, 3};
    std::cout << vec.at(5) << std::endl;
} catch (const std::exception& e) {
    std::cout << "Exception caught" << std::endl;
}
std::cout << "Program continues" << std::endl;
```

A) Программа завершится с ошибкой
B) Exception caught\nProgram continues
C) Только Program continues
D) Ничего не выведет

## Вопрос 17
Какой тип исключения выбрасывается при выходе за границы контейнера?

A) `std::runtime_error`
B) `std::logic_error`
C) `std::out_of_range`
D) `std::invalid_argument`

## Вопрос 18
Что произойдет при выполнении этого кода?
```cpp
void func() {
    throw std::runtime_error("Error in func");
}

int main() {
    try {
        func();
    } catch (const std::logic_error& e) {
        std::cout << "Logic error caught" << std::endl;
    }
    return 0;
}
```

A) Выведет "Logic error caught"
B) Программа завершится с ошибкой
C) Ничего не произойдет
D) Ошибка компиляции

## Вопрос 19
Как правильно выбросить исключение в C++?

A) `exception std::runtime_error("message");`
B) `throw std::runtime_error("message");`
C) `catch std::runtime_error("message");`
D) `try std::runtime_error("message");`

## Вопрос 20
Что такое RAII в контексте обработки исключений?

A) Техника автоматического управления ресурсами
B) Тип исключения
C) Макрос для отладки
D) Библиотека для тестирования

## Вопрос 21
Что выведет следующий код с использованием C++17?
```cpp
#include <optional>
std::optional<int> divide(int a, int b) {
    if (b == 0) return std::nullopt;
    return a / b;
}

int main() {
    auto result = divide(10, 2);
    if (result.has_value()) {
        std::cout << *result << std::endl;
    }
    return 0;
}
```

A) 5
B) 10
C) 2
D) Ошибка компиляции

## Вопрос 22
Какое преимущество дает использование структурированных привязок в тестах?

A) Ускоряет компиляцию
B) Делает код более читаемым при работе с парами и кортежами
C) Уменьшает размер исполняемого файла
D) Автоматически исправляет ошибки

## Вопрос 23
Что делает следующий код?
```cpp
TEST(ExceptionTest, ThrowsCorrectException) {
    EXPECT_THROW(riskyFunction(), std::runtime_error);
}
```

A) Проверяет, что функция не выбрасывает исключений
B) Проверяет, что функция выбрасывает исключение типа std::runtime_error
C) Выбрасывает исключение
D) Ловит любое исключение

## Вопрос 24
Что такое Setup и Teardown в тестировании?

A) Типы исключений
B) Методы для подготовки и очистки ресурсов до и после тестов
C) Макросы для отладки
D) Уровни логирования

## Вопрос 25
Что выведет следующий код?
```cpp
class TestLogger {
public:
    ~TestLogger() { std::cout << "Destructor called" << std::endl; }
};

int main() {
    try {
        TestLogger logger;
        throw std::runtime_error("Error");
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
```

A) Только "Exception: Error"
B) "Destructor called\nException: Error"
C) "Exception: Error\nDestructor called"
D) Программа завершится с ошибкой

## Вопрос 26
Какой макрос в Qt Test используется для сравнения значений?

A) `QVERIFY`
B) `QCOMPARE`
C) `QTEST`
D) `QCHECK`

## Вопрос 27
Что такое покрытие кода (code coverage) в тестировании?

A) Количество строк кода в программе
B) Процент строк кода, которые были выполнены во время тестирования
C) Количество тестов в проекте
D) Время выполнения тестов

## Вопрос 28
Что произойдет при выполнении этого кода?
```cpp
std::vector<int> vec;
try {
    vec.push_back(1);
    vec.push_back(2);
    std::cout << vec.at(1) << std::endl;
} catch (const std::out_of_range& e) {
    std::cout << "Out of range" << std::endl;
}
```

A) Выведет "Out of range"
B) Выведет "2"
C) Программа завершится с ошибкой
D) Ничего не выведет

## Вопрос 29
Что такое регрессионные тесты?

A) Тесты, которые проверяют новую функциональность
B) Тесты, которые подтверждают работоспособность старого кода
C) Тесты, которые проверяют производительность
D) Тесты, которые проверяют пользовательский интерфейс

## Вопрос 30
Что выведет следующий код с std::variant?
```cpp
#include <variant>
std::variant<int, std::string> getValue(bool flag) {
    if (flag) return 42;
    return std::string("error");
}

int main() {
    auto result = getValue(true);
    if (std::holds_alternative<int>(result)) {
        std::cout << std::get<int>(result) << std::endl;
    }
    return 0;
}
```

A) error
B) 42
C) true
D) Ошибка компиляции

## Вопрос 31
Какой принцип организации тестов означает AAA?

A) Assert-Act-Arrange
B) Arrange-Act-Assert
C) Act-Assert-Arrange
D) Arrange-Assert-Act

## Вопрос 32
Что делает следующий код?
```cpp
#ifdef DEBUG
    #define DEBUG_PRINT(x) std::cout << "[DEBUG] " << x << std::endl
#else
    #define DEBUG_PRINT(x)
#endif
```

A) Всегда выводит отладочную информацию
B) Выводит отладочную информацию только в режиме отладки
C) Никогда не выводит отладочную информацию
D) Вызывает ошибку компиляции

## Вопрос 33
Что такое исключение std::bad_alloc?

A) Ошибка при приведении типов
B) Ошибка выделения памяти
C) Ошибка доступа к файлу
D) Ошибка деления на ноль

## Вопрос 34
Что выведет следующий код?
```cpp
try {
    try {
        throw std::runtime_error("Inner error");
    } catch (const std::logic_error& e) {
        std::cout << "Inner catch" << std::endl;
    }
} catch (const std::runtime_error& e) {
    std::cout << "Outer catch: " << e.what() << std::endl;
}
```

A) Inner catch
B) Outer catch: Inner error
C) Программа завершится с ошибкой
D) Ничего не выведет

## Вопрос 35
Что такое интеграционные тесты?

A) Тесты отдельных функций
B) Тесты взаимодействия между компонентами системы
C) Тесты производительности
D) Тесты пользовательского интерфейса

## Вопрос 36
Что делает std::current_exception()?

A) Выбрасывает текущее исключение
B) Возвращает указатель на текущее обрабатываемое исключение
C) Удаляет текущее исключение
D) Создает новое исключение

## Вопрос 37
Что выведет следующий код?
```cpp
class Resource {
public:
    Resource() { std::cout << "Constructor "; }
    ~Resource() { std::cout << "Destructor "; }
};

void func() {
    Resource r;
    throw std::runtime_error("Error");
}

int main() {
    try {
        func();
    } catch (...) {
        std::cout << "Caught ";
    }
    return 0;
}
```

A) Constructor Caught Destructor
B) Constructor Destructor Caught
C) Constructor Caught
D) Destructor Caught

## Вопрос 38
Какой заголовочный файл нужно подключить для std::exception_ptr?

A) `#include <exception>`
B) `#include <stdexcept>`
C) `#include <memory>`
D) `#include <future>`

## Вопрос 39
Что такое параметризованные тесты?

A) Тесты с фиксированными данными
B) Тесты, которые выполняются с разными наборами входных данных
C) Тесты без параметров
D) Тесты только для функций с параметрами

## Вопрос 40
Что выведет следующий код?
```cpp
#include <chrono>
#include <thread>

class Timer {
    std::chrono::high_resolution_clock::time_point start;
public:
    Timer() : start(std::chrono::high_resolution_clock::now()) {}
    ~Timer() {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Time: " << duration.count() << "ms" << std::endl;
    }
};

int main() {
    Timer t;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return 0;
}
```

A) Time: 0ms
B) Time: примерно 100ms
C) Ошибка компиляции
D) Ничего не выведет 