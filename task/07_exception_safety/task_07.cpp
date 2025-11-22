#include <iostream>
#include <cassert>
#include <exception>
#include <stdexcept>

// Task 7: std::exception_ptr
//
// Реализуйте функции для работы с exception_ptr:
// 1. Сохранение исключения в exception_ptr
// 2. Передача исключения между потоками
// 3. Повторное выбрасывание исключения

// TODO: Функция которая может выбросить исключение
void riskyFunction(bool should_throw) {
    // TODO: если should_throw == true, выбросьте std::runtime_error
    // TODO: иначе выполните нормальную работу
}

// TODO: Функция сохранения исключения
std::exception_ptr captureException() {
    std::exception_ptr eptr = nullptr;
    // TODO: вызовите riskyFunction(true) в try-catch
    // TODO: сохраните исключение в eptr используя std::current_exception()
    return eptr;
}

// TODO: Функция повторного выбрасывания исключения
void rethrowException(std::exception_ptr eptr) {
    // TODO: если eptr не nullptr, выбросьте исключение используя std::rethrow_exception
}

// TODO: Функция выполнения в отдельном потоке
std::exception_ptr executeInThread() {
    std::exception_ptr eptr = nullptr;
    // TODO: создайте std::promise для передачи исключения
    // TODO: запустите поток который вызывает riskyFunction(true)
    // TODO: сохраните исключение из future в eptr
    return eptr;
}

// Код для проверки
void testExceptionPtr() {
    // Тест захвата исключения
    auto eptr1 = captureException();
    assert(eptr1 != nullptr);
    
    // Тест повторного выбрасывания
    try {
        rethrowException(eptr1);
        assert(false);  // Не должно дойти сюда
    } catch (const std::runtime_error& e) {
        // Исключение успешно переброшено
        assert(std::string(e.what()).find("risky") != std::string::npos ||
               std::string(e.what()).length() > 0);
    }
    
    // Тест передачи исключения между потоками
    auto eptr2 = executeInThread();
    assert(eptr2 != nullptr);
    
    try {
        rethrowException(eptr2);
        assert(false);
    } catch (const std::runtime_error& e) {
        // Исключение успешно передано между потоками
    }
    
    // Тест что нормальная работа не создает exception_ptr
    try {
        riskyFunction(false);
        // Не должно быть исключения
    } catch (...) {
        assert(false);  // Не должно быть исключения
    }
    
    std::cout << "Exception_ptr tests passed!\n";
}

int main() {
    testExceptionPtr();
    return 0;
}

