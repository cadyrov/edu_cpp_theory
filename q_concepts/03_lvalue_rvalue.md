# L-value и R-value

## Определение
L-value - выражение, которое ссылается на объект с определенным адресом памяти.
R-value - временное значение или объект, который можно только использовать, но нельзя присвоить.

## Зачем это нужно
- Основа для понимания семантики перемещения
- Оптимизация передачи объектов
- Контроль над временными объектами
- Предотвращение ненужного копирования

## Примеры

### ✅ Хорошо
```cpp
// L-value ссылки для избежания копирования
void process(const std::string& text) {  // L-value ссылка
    // Работаем с text без копирования
}

// R-value ссылки для перемещения
void store(std::string&& text) {  // R-value ссылка
    data_ = std::move(text);  // Перемещаем содержимое
}

// Перегрузка для обоих случаев
class Container {
public:
    void add(const T& value);      // Для L-values
    void add(T&& value);           // Для R-values
};
```

### ❌ Плохо
```cpp
// Неоправданное копирование
void process(std::string text) {  // Передача по значению
    // text - копия, когда могла быть ссылка
}

// Неправильное использование std::move
std::string getName() {
    std::string name = "John";
    return std::move(name);  // Ненужно, RVO сработает сама
}

// Небезопасное сохранение R-value ссылки
class Wrong {
    std::string&& data_;  // Опасно! R-value ссылка как поле
};
```

## Нюансы использования

### 1. Категории значений
```cpp
int x = 42;        // x - L-value
int& ref = x;      // ref - L-value reference
42;                // R-value
std::move(x);      // R-value (xvalue)
```

### 2. Правила привязки ссылок
- L-value ссылка может привязываться только к L-value
- Const L-value ссылка может привязываться к чему угодно
- R-value ссылка может привязываться только к R-value

### 3. Временные объекты
```cpp
std::string s1 = "hello";          // "hello" - R-value
std::string&& ref = std::move(s1); // Теперь ref владеет содержимым
// s1 после move считается valid но empty
```

### 4. Perfect Forwarding
```cpp
template<typename T>
void wrapper(T&& arg) {
    // std::forward сохраняет категорию значения
    process(std::forward<T>(arg));
}
```

### 5. Особые случаи
- Функции всегда L-value
- Имена переменных всегда L-value (даже если тип T&&)
- Литералы всегда R-value
- std::move конвертирует в R-value, но не перемещает
- Результат new всегда R-value
