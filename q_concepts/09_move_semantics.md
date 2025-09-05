# Move Semantics

## Определение
Move семантика - механизм C++, позволяющий передавать владение ресурсами от одного объекта другому без копирования, используя r-value ссылки (&&).

## Зачем это нужно
- Оптимизация производительности
- Избежание ненужного копирования
- Эффективная передача ресурсов
- Уникальное владение ресурсами
- Реализация перемещаемых, но некопируемых типов

## Примеры

### ✅ Хорошо
```cpp
// Эффективная передача строки
std::string createString() {
    return std::string("hello");  // NRVO/move автоматически
}

// Перемещение из временного объекта
void processVector(std::vector<Heavy>&& vec) {
    data_ = std::move(vec);  // Явное перемещение
}

// Move-only тип
class UniqueResource {
public:
    UniqueResource(UniqueResource&& other) noexcept
        : handle_(other.handle_) {
        other.handle_ = nullptr;  // Источник обнуляется
    }
    
    UniqueResource& operator=(UniqueResource&& other) noexcept {
        if (this != &other) {
            cleanup();
            handle_ = other.handle_;
            other.handle_ = nullptr;
        }
        return *this;
    }
    
    // Запрет копирования
    UniqueResource(const UniqueResource&) = delete;
    UniqueResource& operator=(const UniqueResource&) = delete;
private:
    Resource* handle_;
};
```

### ❌ Плохо
```cpp
// Ненужное использование std::move
std::string str = "hello";
return std::move(str);  // Мешает NRVO

// Небезопасное перемещение
void unsafe(std::string&& str) {
    data_ = std::move(str);
    process(str);  // str в неопределённом состоянии!
}

// Неправильная реализация move
class Wrong {
    std::vector<int> data_;
public:
    Wrong(Wrong&& other) {  // Забыли noexcept
        data_ = other.data_;  // Копирование вместо move
    }
};
```

## Нюансы использования

### 1. std::move vs std::forward
```cpp
template<typename T>
void wrapper(T&& arg) {
    // std::move всегда в r-value
    process(std::move(arg));
    
    // std::forward сохраняет категорию
    process(std::forward<T>(arg));
}
```

### 2. noexcept гарантии
```cpp
class Safe {
    std::vector<int> data_;
public:
    // Move операции должны быть noexcept
    Safe(Safe&& other) noexcept = default;
    Safe& operator=(Safe&& other) noexcept = default;
};
```

### 3. Move и исключения
```cpp
void moveAndThrow(std::string&& str) {
    data_ = std::move(str);  // Перемещаем
    throw Error();  // str в валидном но неопределённом состоянии
}
```

### 4. Return Value Optimization
```cpp
std::vector<int> createVector() {
    std::vector<int> result;
    // ... заполнение ...
    return result;  // NRVO/move автоматически
}
```

### 5. Move в контейнерах
```cpp
std::vector<std::unique_ptr<Resource>> vec;
vec.push_back(std::make_unique<Resource>());
vec.emplace_back(new Resource());  // Ещё лучше
```

### 6. Move-only типы
```cpp
// Примеры из стандартной библиотеки:
std::unique_ptr<T>
std::future<T>
std::thread
```

### 7. Состояние после move
```cpp
std::string source = "hello";
std::string dest = std::move(source);
// source теперь в валидном но неопределённом состоянии
// Можно только присваивать и уничтожать
```

### 8. Perfect Forwarding
```cpp
template<typename... Args>
void wrapper(Args&&... args) {
    // Идеальная передача аргументов
    create(std::forward<Args>(args)...);
}
```
