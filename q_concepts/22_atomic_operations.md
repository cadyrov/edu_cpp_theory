# Atomic Operations

## Определение
Атомарные операции - операции, которые выполняются как единое целое без возможности прерывания другими потоками, обеспечивая потокобезопасный доступ к данным без использования мьютексов.

## Зачем это нужно
- Потокобезопасные операции без блокировок
- Высокопроизводительная синхронизация
- Lock-free алгоритмы
- Избежание overhead мьютексов
- Реализация низкоуровневых примитивов синхронизации

## Примеры

### ✅ Хорошо
```cpp
// Атомарный счётчик
class AtomicCounter {
    std::atomic<int> value_{0};
public:
    void increment() {
        value_.fetch_add(1, std::memory_order_relaxed);
    }
    
    int get() const {
        return value_.load(std::memory_order_acquire);
    }
};

// Атомарный флаг
class AtomicFlag {
    std::atomic<bool> flag_{false};
public:
    void set() {
        flag_.store(true, std::memory_order_release);
    }
    
    bool test_and_set() {
        return flag_.exchange(true);
    }
};

// Lock-free стек
template<typename T>
class LockFreeStack {
    struct Node {
        T data;
        std::atomic<Node*> next;
    };
    
    std::atomic<Node*> head_{nullptr};
public:
    void push(T value) {
        Node* new_node = new Node{value};
        new_node->next = head_.load(std::memory_order_relaxed);
        while (!head_.compare_exchange_weak(
            new_node->next,
            new_node,
            std::memory_order_release,
            std::memory_order_relaxed));
    }
};
```

### ❌ Плохо
```cpp
// Неправильное использование memory order
class Wrong {
    std::atomic<int> value_{0};
public:
    void increment() {
        // Избыточный memory order
        value_.fetch_add(1, std::memory_order_seq_cst);
    }
};

// Смешивание атомарных и неатомарных операций
class Mixed {
    std::atomic<int> atomic_value_{0};
    int normal_value_{0};  // Не атомарное
public:
    void unsafe_update() {
        atomic_value_++;   // Атомарно
        normal_value_++;   // Race condition!
    }
};

// Неправильная синхронизация
class BadSync {
    std::atomic<bool> ready_{false};
    int data_;
public:
    void produce() {
        data_ = 42;
        // Отсутствует барьер памяти
        ready_.store(true);
    }
};
```

## Нюансы использования

### 1. Memory Ordering
```cpp
std::atomic<int> value;

// Различные модели памяти
value.store(1, std::memory_order_relaxed);  // Самый слабый
value.store(2, std::memory_order_release);  // Для публикации
value.load(std::memory_order_acquire);      // Для чтения
value.store(3, std::memory_order_seq_cst);  // Самый строгий
```

### 2. Compare-and-Exchange
```cpp
class AtomicMax {
    std::atomic<int> value_{0};
public:
    void update_max(int new_value) {
        int old_value = value_.load();
        while (new_value > old_value &&
               !value_.compare_exchange_weak(
                   old_value, new_value)) {
            // Повторяем при неудаче
        }
    }
};
```

### 3. Атомарные операции с указателями
```cpp
template<typename T>
class LockFreeQueue {
    struct Node {
        T data;
        std::atomic<Node*> next{nullptr};
    };
    
    std::atomic<Node*> head_{nullptr};
    std::atomic<Node*> tail_{nullptr};
};
```

### 4. Fence операции
```cpp
void producer() {
    data_ = value;  // Неатомарная запись
    std::atomic_thread_fence(std::memory_order_release);
    ready_.store(true, std::memory_order_relaxed);
}

void consumer() {
    while (!ready_.load(std::memory_order_relaxed)) {}
    std::atomic_thread_fence(std::memory_order_acquire);
    // Теперь data_ видно
}
```

### 5. Атомарные флаги
```cpp
class SpinLock {
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
public:
    void lock() {
        while (flag.test_and_set(std::memory_order_acquire)) {
            // Спин-ожидание
        }
    }
    
    void unlock() {
        flag.clear(std::memory_order_release);
    }
};
```

### 6. Lock-free структуры данных
```cpp
template<typename T>
class LockFreeQueue {
    struct Node {
        T data;
        std::atomic<Node*> next;
    };
    
    std::atomic<Node*> head_;
    std::atomic<Node*> tail_;
public:
    void push(T value) {
        Node* new_node = new Node{value};
        Node* old_tail = tail_.load();
        
        while (!tail_.compare_exchange_weak(
            old_tail,
            new_node)) {}
    }
};
```

### 7. Атомарные операции с битовыми полями
```cpp
struct Flags {
    std::atomic<uint32_t> bits_{0};
    
    void set_flag(int position) {
        uint32_t mask = 1u << position;
        bits_.fetch_or(mask, std::memory_order_relaxed);
    }
    
    bool test_flag(int position) {
        uint32_t mask = 1u << position;
        return (bits_.load(std::memory_order_relaxed) & mask) != 0;
    }
};
```

### 8. Best practices
```cpp
// 1. Используй самый слабый достаточный memory order
std::atomic<int> counter{0};
counter.fetch_add(1, std::memory_order_relaxed);  // Для счётчиков

// 2. Избегай смешивания с неатомарными операциями
class Safe {
    std::atomic<int> value_{0};
    std::atomic<int> counter_{0};  // Все поля атомарные
};

// 3. Правильная синхронизация
class Synchronized {
    std::atomic<int> data_{0};
    std::atomic<bool> ready_{false};
    
    void publish(int value) {
        data_.store(value, std::memory_order_release);
        ready_.store(true, std::memory_order_release);
    }
    
    bool try_get(int& result) {
        if (ready_.load(std::memory_order_acquire)) {
            result = data_.load(std::memory_order_acquire);
            return true;
        }
        return false;
    }
};
```
