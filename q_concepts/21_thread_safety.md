# Thread Safety

## Определение
Thread Safety - свойство кода корректно работать при одновременном выполнении в нескольких потоках, предотвращая race conditions и обеспечивая правильную синхронизацию доступа к разделяемым ресурсам.

## Зачем это нужно
- Предотвращение race conditions
- Безопасный доступ к разделяемым данным
- Корректная работа многопоточных программ
- Повышение производительности
- Обеспечение целостности данных

## Примеры

### ✅ Хорошо
```cpp
// Потокобезопасный синглтон
class Singleton {
public:
    static Singleton& instance() {
        static Singleton instance;
        return instance;
    }

private:
    Singleton() = default;
};

// Защита данных мьютексом
class ThreadSafeCounter {
    mutable std::mutex mutex_;
    int value_ = 0;
public:
    int increment() {
        std::lock_guard<std::mutex> lock(mutex_);
        return ++value_;
    }
    
    int get() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return value_;
    }
};

// RAII блокировка
void process_data(std::vector<int>& data) {
    std::lock_guard<std::mutex> lock(mutex_);
    // Безопасная работа с data
}

// Условные переменные
class ThreadSafeQueue {
    std::queue<int> queue_;
    mutable std::mutex mutex_;
    std::condition_variable not_empty_;
public:
    void push(int value) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(value);
        }
        not_empty_.notify_one();
    }
    
    int pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        not_empty_.wait(lock, [this] { 
            return !queue_.empty(); 
        });
        int value = queue_.front();
        queue_.pop();
        return value;
    }
};
```

### ❌ Плохо
```cpp
// Race condition
class UnsafeCounter {
    int value_ = 0;
public:
    void increment() { ++value_; }  // Не потокобезопасно
    int get() const { return value_; }
};

// Возможный deadlock
class Deadlock {
    std::mutex mutex1_, mutex2_;
public:
    void operation1() {
        std::lock_guard<std::mutex> lock1(mutex1_);
        std::lock_guard<std::mutex> lock2(mutex2_);
        // Возможен deadlock
    }
    
    void operation2() {
        std::lock_guard<std::mutex> lock2(mutex2_);
        std::lock_guard<std::mutex> lock1(mutex1_);
        // Обратный порядок блокировки
    }
};

// Утечка мьютекса
void unsafe_function() {
    mutex_.lock();
    // Если будет исключение, мьютекс останется заблокированным
    process_data();
    mutex_.unlock();
}
```

## Нюансы использования

### 1. RAII и мьютексы
```cpp
class SafeResource {
    std::mutex mutex_;
    Resource resource_;
public:
    void use() {
        std::lock_guard<std::mutex> lock(mutex_);
        resource_.process();
    }  // Автоматическая разблокировка
};
```

### 2. Типы блокировок
```cpp
// Эксклюзивная блокировка
std::lock_guard<std::mutex> lock(mutex_);

// Разделяемая блокировка
std::shared_lock<std::shared_mutex> lock(mutex_);

// Уникальная блокировка (можно разблокировать)
std::unique_lock<std::mutex> lock(mutex_);
```

### 3. Условные переменные
```cpp
class WaitQueue {
    std::condition_variable cv_;
    std::mutex mutex_;
    bool ready_ = false;
public:
    void wait() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] { return ready_; });
    }
    
    void signal() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            ready_ = true;
        }
        cv_.notify_one();
    }
};
```

### 4. Atomic операции
```cpp
class LockFreeCounter {
    std::atomic<int> value_{0};
public:
    void increment() {
        value_.fetch_add(1, std::memory_order_relaxed);
    }
    
    int get() const {
        return value_.load(std::memory_order_acquire);
    }
};
```

### 5. Предотвращение deadlock
```cpp
void safe_operation() {
    std::scoped_lock lock(mutex1_, mutex2_);
    // Автоматически предотвращает deadlock
}

// Или с std::lock
void safe_operation2() {
    std::unique_lock<std::mutex> lock1(mutex1_, std::defer_lock);
    std::unique_lock<std::mutex> lock2(mutex2_, std::defer_lock);
    std::lock(lock1, lock2);
}
```

### 6. Thread-local storage
```cpp
class ThreadSafeLogger {
    static thread_local std::string thread_name_;
public:
    static void log(const std::string& message) {
        std::cout << thread_name_ << ": " << message << '\n';
    }
};
```

### 7. Read-Write мьютексы
```cpp
class ThreadSafeCache {
    mutable std::shared_mutex mutex_;
    std::map<int, std::string> cache_;
public:
    std::string read(int key) const {
        std::shared_lock lock(mutex_);  // Множество читателей
        return cache_[key];
    }
    
    void write(int key, std::string value) {
        std::unique_lock lock(mutex_);  // Эксклюзивная запись
        cache_[key] = std::move(value);
    }
};
```

### 8. Best practices
```cpp
// 1. Минимизация критических секций
void process() {
    // Подготовка без блокировки
    Data data = prepare();
    
    {
        std::lock_guard<std::mutex> lock(mutex_);
        // Минимальная критическая секция
        update(data);
    }
    
    // Продолжение без блокировки
}

// 2. RAII для всех ресурсов
class SafeHandler {
    std::mutex mutex_;
    std::condition_variable cv_;
    bool ready_ = false;
    
    void process() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] { return ready_; });
        // Безопасная обработка
    }
};
```
