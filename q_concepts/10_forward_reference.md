# Forward Reference

## Определение
Forward reference (универсальные ссылки) - это механизм C++, позволяющий функциям принимать как l-value, так и r-value аргументы, сохраняя их категорию значения через type deduction и std::forward.

## Зачем это нужно
- Создание универсальных функций-обёрток
- Perfect forwarding параметров
- Избежание дублирования кода
- Оптимизация производительности
- Сохранение категории значения при передаче

## Примеры

### ✅ Хорошо
```cpp
// Универсальная обёртка
template<typename T>
void wrapper(T&& arg) {
    // Perfect forwarding сохраняет категорию значения
    process(std::forward<T>(arg));
}

// Фабричная функция
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(
        new T(std::forward<Args>(args)...)
    );
}

// Универсальный конструктор
class Container {
public:
    template<typename T>
    void add(T&& value) {
        data_.push_back(std::forward<T>(value));
    }
private:
    std::vector<std::string> data_;
};
```

### ❌ Плохо
```cpp
// Потеря категории значения
template<typename T>
void wrong(T&& arg) {
    process(arg);  // Теряем r-value nature
}

// Неправильное использование std::forward
template<typename T>
void incorrect(T&& arg) {
    process(std::forward<T>(arg));
    process(std::forward<T>(arg));  // Повторное использование
}

// Ошибочное использование std::move вместо std::forward
template<typename T>
void mistake(T&& arg) {
    process(std::move(arg));  // Всегда делает r-value
}
```

## Нюансы использования

### 1. Правила определения универсальной ссылки
```cpp
template<typename T>
void f(T&& param);  // Универсальная ссылка

void f(Widget&& param);  // НЕ универсальная (r-value) ссылка

template<typename T>
void f(const T&& param);  // НЕ универсальная ссылка
```

### 2. auto&& и decltype(auto)
```cpp
// Универсальная ссылка с auto
auto&& val = someValue;  // Тип выводится правильно
```

`decltype(auto)` помогает сохранить точный тип возвращаемого выражения, включая ссылочность, что важно при построении обёрток с perfect forwarding.

#### ✅ Хорошо
```cpp
template<typename T>
decltype(auto) forward_get(T&& obj) {
    // Возвращаем то, что вернул get(), не теряя ссылку
    return std::forward<T>(obj).get();
}

auto&& ref = get_container();
decltype(auto) elem = forward_get(ref);  // Сохраняем l-value ссылку
```

#### ❌ Плохо
```cpp
template<typename T>
auto forward_get_bad(T&& obj) {
    // auto отбрасывает ссылку, возможна лишняя копия
    return std::forward<T>(obj).get();
}

decltype(auto) broken_ref = forward_get_bad(ref_source());  
// Возвращается временный объект → висячая ссылка
```

### 3. Perfect Forwarding в конструкторах
```cpp
class Wrapper {
    template<typename... Args>
    Wrapper(Args&&... args)
        : wrapped_(std::forward<Args>(args)...)
    {}
private:
    Wrapped wrapped_;
};
```

### 4. Проблема с перегрузками
```cpp
template<typename T>
void process(T&& x) { /* ... */ }

void process(int x) { /* ... */ }

// process(42);    // Вызовет НЕ шаблонную версию
// process(var);   // Может быть неоднозначность
```

### 5. Forwarding Reference vs R-value Reference
```cpp
template<typename T>
class Buffer {
    // Это r-value ссылка, НЕ universal reference
    void push(T&& value);
    
    // Это universal reference
    template<typename U>
    void push(U&& value);
};
```

### 6. std::forward vs std::move
```cpp
template<typename T>
void wrapper(T&& arg) {
    // std::forward - условное преобразование
    process(std::forward<T>(arg));
    
    // std::move - безусловное преобразование в r-value
    process(std::move(arg));
}
```

### 7. Множественные параметры
```cpp
template<typename... Args>
void forward_all(Args&&... args) {
    process(std::forward<Args>(args)...);
}
```

### 8. Ограничения
```cpp
// Нельзя использовать с массивами
template<typename T>
void f(T&& arr);  // Не работает с массивами напрямую

// Нельзя с функциями
void g(void (&&f)());  // Не universal reference
```
