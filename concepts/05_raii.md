# RAII (Resource Acquisition Is Initialization)

## Определение
RAII - идиома C++, где управление ресурсами (память, файлы, мьютексы и т.д.) привязано к времени жизни объекта: ресурс приобретается в конструкторе и освобождается в деструкторе.

## Зачем это нужно
- Автоматическое освобождение ресурсов
- Защита от утечек памяти
- Exception-safety
- Детерминированное время освобождения ресурсов
- Упрощение кода

## Примеры

### ✅ Хорошо
```cpp
// RAII для файла
class File {
    FILE* handle_;
public:
    File(const char* name) : handle_(fopen(name, "r")) {
        if (!handle_) throw std::runtime_error("Failed to open file");
    }
    ~File() { 
        if (handle_) fclose(handle_); 
    }
    // Запрет копирования
    File(const File&) = delete;
    File& operator=(const File&) = delete;
};

// RAII для мьютекса
class LockGuard {
    std::mutex& mutex_;
public:
    explicit LockGuard(std::mutex& m) : mutex_(m) {
        mutex_.lock();
    }
    ~LockGuard() {
        mutex_.unlock();
    }
};

// Использование smart pointers
class Resource {
    std::unique_ptr<int[]> data_;
public:
    Resource() : data_(new int[1000]) {}
    // Деструктор не нужен - cleanup автоматический
};
```

### ❌ Плохо
```cpp
// Ручное управление ресурсами
void processFile() {
    FILE* file = fopen("data.txt", "r");
    // Обработка... что если будет исключение?
    fclose(file);  // Может не выполниться
}

// Незащищенный мьютекс
void unsafeFunction(std::mutex& m) {
    m.lock();
    // Если исключение - мьютекс останется заблокированным
    m.unlock();
}

// Сырые указатели без RAII
class Leaky {
    int* data_ = new int[1000];
    // Забыли деструктор - утечка!
};
```

## Нюансы использования

### 1. Правило нуля
```cpp
class Modern {
    std::string str_;        // RAII-типы
    std::vector<int> vec_;   // управляют ресурсами
    std::unique_ptr<Resource> ptr_;
    // Не нужен деструктор/копирование/перемещение
};
```

### 2. Порядок уничтожения
```cpp
class Order {
    std::unique_ptr<A> a_;  // Уничтожается последним
    std::unique_ptr<B> b_;  // Вторым
    std::unique_ptr<C> c_;  // Первым
    // Порядок уничтожения обратен порядку объявления
};
```

### 3. Exception Safety
```cpp
void safe() {
    std::unique_ptr<Resource> res(new Resource());
    // Даже если будет исключение, память освободится
}
```

### 4. Кастомные делитеры
```cpp
auto deleter = [](FILE* f) { fclose(f); };
std::unique_ptr<FILE, decltype(deleter)> 
    file(fopen("data.txt", "r"), deleter);
```

### 5. Типичные RAII-обёртки
```cpp
// Для мьютексов
std::lock_guard<std::mutex>
std::unique_lock<std::mutex>

// Для памяти
std::unique_ptr<T>
std::shared_ptr<T>

// Для массивов
std::vector<T>
std::array<T, N>

// Для строк
std::string
```
