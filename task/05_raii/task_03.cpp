#include <iostream>
#include <cassert>
#include <mutex>
#include <thread>

// Task 3: RAII для мьютексов
//
// Реализуйте класс LockGuard, который:
// 1. Блокирует мьютекс в конструкторе
// 2. Разблокирует мьютекс в деструкторе
// 3. Гарантирует разблокировку даже при исключениях
// 4. Запрещает копирование

class LockGuard {
    std::mutex& mutex_;
    bool locked_;
    
public:
    // TODO: Конструктор (блокирует мьютекс)
    explicit LockGuard(std::mutex& m) : mutex_(m), locked_(false) {
        // TODO: заблокируйте мьютекс
        // TODO: установите locked_ в true
    }
    
    // TODO: Деструктор (разблокирует мьютекс)
    ~LockGuard() {
        // TODO: если locked_ == true, разблокируйте мьютекс
    }
    
    // TODO: Запретить копирование
    LockGuard(const LockGuard&) = delete;
    LockGuard& operator=(const LockGuard&) = delete;
    
    // TODO: Ручная разблокировка (опционально)
    void unlock() {
        // TODO: разблокируйте мьютекс и установите locked_ в false
    }
    
    bool isLocked() const { return locked_; }
};

// Глобальный счетчик для тестирования
static int counter = 0;
static std::mutex counter_mutex;

// Код для проверки
void testLockGuard() {
    std::mutex m;
    
    // Базовое использование
    {
        LockGuard lock(m);
        assert(lock.isLocked());
        // Мьютекс заблокирован
    }
    // Мьютекс автоматически разблокирован
    
    // Тест с несколькими потоками
    std::thread t1([]() {
        for (int i = 0; i < 1000; ++i) {
            LockGuard lock(counter_mutex);
            counter++;
        }
    });
    
    std::thread t2([]() {
        for (int i = 0; i < 1000; ++i) {
            LockGuard lock(counter_mutex);
            counter++;
        }
    });
    
    t1.join();
    t2.join();
    
    assert(counter == 2000);
    
    std::cout << "LockGuard RAII tests passed!\n";
}

int main() {
    testLockGuard();
    return 0;
}

