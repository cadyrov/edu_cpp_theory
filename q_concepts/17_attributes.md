# Атрибуты

## Определение
Атрибуты в C++ - это стандартизированный способ передачи дополнительной информации компилятору о коде, который может влиять на оптимизацию, предупреждения и поведение программы.

## Зачем это нужно
- Предоставление подсказок компилятору
- Улучшение оптимизации
- Предотвращение ошибок
- Документирование намерений
- Улучшение безопасности кода

## Примеры

### ✅ Хорошо
```cpp
// Указание что функция никогда не возвращает управление
[[noreturn]] void throwError() {
    throw std::runtime_error("Error");
}

// Пометка устаревшего API
[[deprecated("Use newFunction() instead")]]
void oldFunction() { }

// Подсказка для оптимизации
[[likely]] if (condition) {
    // Этот путь вероятнее
}

// Предотвращение случайного игнорирования результата
[[nodiscard]] bool checkStatus() {
    return status_;
}

// Указание что функция не выбрасывает исключений
void process() noexcept {
    [[assume(condition)]]; // Подсказка компилятору
}
```

### ❌ Плохо
```cpp
// Неправильное использование noreturn
[[noreturn]] void wrongNoreturn() {
    if (condition)
        return;  // Можем вернуться!
}

// Избыточное использование nodiscard
[[nodiscard]] void setFlag(bool flag);  // Нет возвращаемого значения

// Неправильные ожидания
[[likely]] if (rare_condition) {  // Вводит в заблуждение
    // ...
}

// Противоречивые атрибуты
[[deprecated]]
[[nodiscard]] // Смешанные сигналы
int getValue();
```

## Нюансы использования

### 1. nodiscard
```cpp
// На типах
[[nodiscard]] struct ErrorCode { };

// На функциях
[[nodiscard]] std::unique_ptr<Resource> create();

// С сообщением (C++20)
[[nodiscard("Memory leak if ignored")]]
void* allocate(size_t size);
```

### 2. deprecated
```cpp
// Базовое использование
[[deprecated]]
void old();

// С сообщением
[[deprecated("Use new_func() instead")]]
void old_func();

// На типах
[[deprecated]]
struct OldType { };
```

### 3. likely/unlikely
```cpp
// C++20
if (error) [[unlikely]] {
    handle_error();
}

switch (value) {
    [[likely]] case 0: 
        handle_common();
        break;
    [[unlikely]] default:
        handle_rare();
}
```

### 4. no_unique_address
```cpp
class Empty {};

class Optimized {
    int data;
    [[no_unique_address]] Empty e;  // Может не занимать память
};
```

### 5. maybe_unused
```cpp
void process([[maybe_unused]] int debug_level) {
#ifdef DEBUG
    setDebugLevel(debug_level);
#endif
}

[[maybe_unused]] static const int UNUSED_CONSTANT = 42;
```

### 6. noreturn
```cpp
[[noreturn]] void terminate() {
    std::abort();
}

[[noreturn]] void throwAlways() {
    throw std::runtime_error("Always throws");
}
```

### 7. carries_dependency
```cpp
[[carries_dependency]] int* load_ptr() {
    return ptr_.load(std::memory_order_consume);
}
```

### 8. Комбинации атрибутов
```cpp
[[nodiscard, deprecated("Use new_api()")]]
int old_api();

class [[deprecated]] [[nodiscard]]
OldButImportant { };
```

### 9. Атрибуты для оптимизации
```cpp
void process(int* data, size_t size) {
    [[assume(size > 0)]];  // Подсказка компилятору
    [[assume(data != nullptr)]];
    
    for (size_t i = 0; i < size; ++i) {
        // Оптимизированный код
    }
}
```

### 10. Вендор-специфичные атрибуты
```cpp
// GNU
__attribute__((always_inline))
void performance_critical();

// MSVC
__declspec(dllexport)
void exported_function();

// Стандартный способ (если поддерживается)
[[gnu::always_inline]]
void performance_critical();
```
