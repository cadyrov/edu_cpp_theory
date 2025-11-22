# Оптимизации производительности

## Определение
Оптимизации производительности в C++ - набор техник и подходов для улучшения скорости выполнения, уменьшения потребления памяти и повышения эффективности программы.

## Зачем это нужно
- Ускорение выполнения программы
- Уменьшение потребления памяти
- Улучшение отзывчивости
- Снижение нагрузки на систему
- Оптимизация использования ресурсов

## Примеры

### ✅ Хорошо
```cpp
// Cache-friendly структуры данных
struct AoS {  // Array of Structures
    std::array<Object, 1000> objects;
};

struct SoA {  // Structure of Arrays
    std::array<float, 1000> x;
    std::array<float, 1000> y;
    std::array<float, 1000> z;
};

// Избегание виртуальных вызовов в критических участках
template<typename Strategy>
class FastProcessor {
    Strategy strategy_;
public:
    void process() {
        strategy_.execute();  // Статический полиморфизм
    }
};

// Пул объектов
class ObjectPool {
    std::vector<std::unique_ptr<Object>> pool_;
    std::queue<Object*> free_objects_;
public:
    Object* acquire() {
        if (free_objects_.empty()) {
            pool_.push_back(std::make_unique<Object>());
            free_objects_.push(pool_.back().get());
        }
        Object* obj = free_objects_.front();
        free_objects_.pop();
        return obj;
    }
    
    void release(Object* obj) {
        free_objects_.push(obj);
    }
};

// Small String Optimization
class SmallString {
    static constexpr size_t SMALL_SIZE = 16;
    union {
        char small_[SMALL_SIZE];
        char* large_;
    };
    size_t size_;
    bool is_small_;
};
```

### ❌ Плохо
```cpp
// Неэффективные копирования
void slow_process(std::vector<BigObject> objects) {  // Копирование
    for (auto obj : objects) {  // Ещё копирование
        obj.process();
    }
}

// Cache-unfriendly доступ
class CacheMiss {
    std::vector<int*> pointers_;  // Разбросанные по памяти данные
public:
    void process() {
        for (auto* ptr : pointers_) {
            *ptr += 1;  // Cache misses
        }
    }
};

// Излишняя виртуализация
class OverEngineered {
    std::vector<std::unique_ptr<Interface>> items_;
public:
    void simple_task() {
        for (auto& item : items_) {
            item->trivial_operation();  // Виртуальный вызов для простой операции
        }
    }
};
```

## Нюансы использования

### 1. Memory Layout
```cpp
// Выравнивание данных
struct Aligned {
    alignas(64) std::array<float, 16> data;  // Cache line
};

// Группировка часто используемых данных
struct HotCold {
    // Hot данные (часто используемые)
    int hot_data_;
    float more_hot_;
    
    // Cold данные (редко используемые)
    std::string cold_data_;
    std::vector<int> more_cold_;
};
```

### 2. Inline и констексты
```cpp
// Явный inline для критических функций
inline int fast_operation(int x) {
    return x * 2 + 1;
}

// Constexpr вычисления
constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}
```

### 3. Move семантика
```cpp
class Optimized {
    std::vector<BigObject> data_;
public:
    void add(BigObject&& obj) {
        data_.push_back(std::move(obj));  // Избегаем копирования
    }
};
```

### 4. Резервирование памяти
```cpp
void process_data(size_t n) {
    std::vector<int> data;
    data.reserve(n);  // Избегаем реаллокаций
    
    for (size_t i = 0; i < n; ++i) {
        data.push_back(i);
    }
}
```

### 5. Профилирование и бенчмарки
```cpp
class Benchmark {
    using Clock = std::chrono::high_resolution_clock;
    Clock::time_point start_;
public:
    Benchmark() : start_(Clock::now()) {}
    
    ~Benchmark() {
        auto duration = Clock::now() - start_;
        std::cout << "Duration: " 
                  << std::chrono::duration_cast<
                         std::chrono::microseconds
                     >(duration).count() 
                  << "us\n";
    }
};
```

### 6. SIMD оптимизации
```cpp
// Векторизация циклов
void vectorized_add(float* a, float* b, float* c, size_t n) {
    #pragma omp simd
    for (size_t i = 0; i < n; ++i) {
        c[i] = a[i] + b[i];
    }
}
```

### 7. Пулы памяти
```cpp
template<typename T, size_t BlockSize = 4096>
class MemoryPool {
    union Block {
        T data;
        Block* next;
    };
    
    Block* free_list_ = nullptr;
    
public:
    T* allocate() {
        if (!free_list_) {
            // Аллоцируем новый блок
            auto new_block = 
                reinterpret_cast<Block*>(
                    new char[sizeof(Block) * BlockSize]
                );
            
            // Инициализируем список
            for (size_t i = 0; i < BlockSize - 1; ++i) {
                new_block[i].next = &new_block[i + 1];
            }
            new_block[BlockSize - 1].next = nullptr;
            free_list_ = new_block;
        }
        
        Block* block = free_list_;
        free_list_ = block->next;
        return &block->data;
    }
    
    void deallocate(T* ptr) {
        Block* block = reinterpret_cast<Block*>(ptr);
        block->next = free_list_;
        free_list_ = block;
    }
};
```

### 8. Best practices
```cpp
// 1. Избегай динамических аллокаций в критических участках
class FastProcessor {
    std::array<int, 1000> buffer_;  // Stack allocation
    
    void process() {
        // Работаем с buffer_ напрямую
    }
};

// 2. Используй view типы
void process_string(std::string_view str) {
    // Нет копирования строки
}

// 3. Правильная передача параметров
void optimal(const BigObject& obj);     // Для больших объектов
void optimal(int x);                    // Для маленьких типов
void optimal(std::string&& str);        // Для перемещаемых объектов

// 4. Локальность данных
class CacheFriendly {
    std::vector<Object> objects_;  // Все объекты рядом в памяти
    
    void process() {
        for (auto& obj : objects_) {
            // Хороший cache hit rate
        }
    }
};
```
