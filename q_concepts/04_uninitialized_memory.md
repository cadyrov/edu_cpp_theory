# Uninitialized Memory

## Определение
Работа с неинициализированной памятью в C++ - набор техник и алгоритмов для оптимизации производительности путем разделения выделения и инициализации памяти.

## Зачем это нужно
- Оптимизация производительности
- Контроль над инициализацией объектов
- Реализация аллокаторов и контейнеров
- Работа с POD типами
- Избежание двойной инициализации

## Примеры

### ✅ Хорошо
```cpp
// Эффективное создание массива
void create_array(size_t n) {
    // Выделение памяти без инициализации
    auto* storage = static_cast<int*>(::operator new[](n * sizeof(int)));
    
    try {
        // Инициализация только нужных элементов
        std::uninitialized_fill_n(storage, n, 42);
    } catch (...) {
        ::operator delete[](storage);
        throw;
    }
    // Использование...
    std::destroy_n(storage, n);
    ::operator delete[](storage);
}

// Оптимизированное копирование
template<typename T>
class Buffer {
    alignas(T) unsigned char* data_ = nullptr;
    size_t size_ = 0;

public:
    void assign(const T* src, size_t count) {
        if (size_ < count) {
            clear();
            data_ = new unsigned char[count * sizeof(T)];
            std::uninitialized_copy_n(src, count, 
                reinterpret_cast<T*>(data_));
            size_ = count;
        }
    }

    void clear() {
        if (data_) {
            std::destroy_n(reinterpret_cast<T*>(data_), size_);
            delete[] data_;
            data_ = nullptr;
            size_ = 0;
        }
    }

    ~Buffer() { clear(); }
};
```

### ❌ Плохо
```cpp
// Неэффективная двойная инициализация
void inefficient(size_t n) {
    std::vector<int> vec(n);  // Инициализация нулями
    std::fill(vec.begin(), vec.end(), 42);  // Перезапись
}

// Опасное использование неинициализированной памяти
void dangerous() {
    int* ptr = static_cast<int*>(malloc(sizeof(int)));
    *ptr = 42;  // UB если int не является POD типом
    free(ptr);
}

// Забыли про исключения
void unsafe(size_t n) {
    auto* data = new unsigned char[n * sizeof(int)];
    // Нет try-catch - возможна утечка при исключении
    std::uninitialized_fill_n(
        reinterpret_cast<int*>(data), n, 42);
}
```

## Нюансы использования

### 1. std::uninitialized_* алгоритмы
```cpp
// Основные алгоритмы
std::uninitialized_copy
std::uninitialized_copy_n
std::uninitialized_fill
std::uninitialized_fill_n
std::uninitialized_move
std::uninitialized_move_n
std::uninitialized_default_construct
std::uninitialized_value_construct

// Пример использования
alignas(T) unsigned char buffer[N * sizeof(T)];
auto* ptr = reinterpret_cast<T*>(buffer);
std::uninitialized_fill_n(ptr, N, value);
```

### 2. Placement new
```cpp
// Ручное размещение объекта
alignas(T) unsigned char buffer[sizeof(T)];
T* obj = new(buffer) T(args...);
// ...
obj->~T();  // Явный вызов деструктора

// Массив через placement new
char* buffer = new char[N * sizeof(T)];
for(size_t i = 0; i < N; ++i) {
    new(buffer + i * sizeof(T)) T();
}
```

### 3. POD типы
```cpp
// Работа с POD типами безопаснее
struct POD {
    int x;
    double y;
};

void pod_example() {
    unsigned char buffer[sizeof(POD)];
    std::memcpy(&buffer, &pod_source, sizeof(POD));
    // Безопасно для POD типов
}
```

### 4. Exception Safety
```cpp
template<typename T>
class SafeBuffer {
    unsigned char* buffer_ = nullptr;
    size_t size_ = 0;

    void safe_construct(size_t n) {
        unsigned char* new_buffer = 
            new unsigned char[n * sizeof(T)];
        
        try {
            std::uninitialized_default_construct_n(
                reinterpret_cast<T*>(new_buffer), n);
            
            // Если успешно - обновляем члены
            delete[] buffer_;
            buffer_ = new_buffer;
            size_ = n;
        } catch (...) {
            delete[] new_buffer;
            throw;
        }
    }
};
```

### 5. Оптимизация производительности
```cpp
// Быстрая реализация вектора
template<typename T>
class FastVector {
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;

public:
    void reserve(size_t new_cap) {
        if (new_cap <= capacity_) return;
        
        // Выделяем память без инициализации
        T* new_data = static_cast<T*>(
            ::operator new[](new_cap * sizeof(T)));
        
        try {
            // Перемещаем существующие элементы
            std::uninitialized_move_n(
                data_, size_, new_data);
            
            // Очищаем старые элементы
            std::destroy_n(data_, size_);
            ::operator delete[](data_);
            
            data_ = new_data;
            capacity_ = new_cap;
        } catch (...) {
            ::operator delete[](new_data);
            throw;
        }
    }
};
```

### 6. Выравнивание памяти
```cpp
// Правильное выравнивание
template<typename T>
class AlignedBuffer {
    static constexpr size_t alignment = alignof(T);
    alignas(alignment) unsigned char* buffer_ = nullptr;
    
    void* get_aligned_ptr() {
        return std::align(
            alignment,
            sizeof(T),
            reinterpret_cast<void*&>(buffer_),
            sizeof(T)
        );
    }
};
```
