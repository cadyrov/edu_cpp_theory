# Deduction Guides

## Определение
Deduction guides - механизм C++17, который помогает компилятору выводить правильные типы шаблонных классов при их конструировании.

## Зачем это нужно
- Упрощение использования шаблонных классов
- Улучшение читаемости кода
- Автоматический вывод сложных типов
- Предотвращение ошибок при выводе типов
- Более интуитивное API

## Примеры

### ✅ Хорошо
```cpp
// Базовый класс с deduction guide
template<typename T>
class Container {
    std::vector<T> data_;
public:
    Container(std::initializer_list<T> init) 
        : data_(init) {}
};
// Deduction guide
Container(std::initializer_list<int>) -> Container<int>;

// Использование
Container c{1, 2, 3};  // Container<int>

// Сложный случай
template<typename Key, typename Value>
class Pair {
    Key key_;
    Value value_;
public:
    Pair(Key k, Value v) : key_(k), value_(v) {}
};
// Guide для разных типов
template<typename K, typename V>
Pair(K, V) -> Pair<K, V>;

// Использование
Pair p{"key", 42};  // Pair<const char*, int>
```

### ❌ Плохо
```cpp
// Избыточный guide
template<typename T>
class Simple {
    T value_;
public:
    Simple(T v) : value_(v) {}
};
Simple(auto) -> Simple<auto>;  // Не нужен, компилятор справится сам

// Неправильный guide
template<typename T>
class Wrong {
    std::vector<T> data_;
public:
    Wrong(T first, T second);
};
Wrong(auto, auto) -> Wrong<void>;  // Теряем тип параметров

// Противоречивые guides
template<typename T>
class Confusing {
    T value_;
public:
    Confusing(T v);
};
Confusing(int) -> Confusing<long>;     // Плохо: противоречит
Confusing(int) -> Confusing<int>;      // интуитивному поведению
```

## Нюансы использования

### 1. Implicit guides
```cpp
template<typename T>
struct Wrapper {
    T value;
    Wrapper(T v) : value(v) {}
};
// Компилятор автоматически создаёт:
// Wrapper(T) -> Wrapper<T>;
```

### 2. Aggregate initialization
```cpp
template<typename T, typename U>
struct Aggregate {
    T first;
    U second;
};
// Guide для агрегатов
template<typename T, typename U>
Aggregate(T, U) -> Aggregate<T, U>;
```

### 3. Guide с преобразованием типов
```cpp
template<typename T>
class Number {
    T value_;
public:
    Number(T v) : value_(v) {}
};
// Guide с явным преобразованием
Number(char) -> Number<int>;
Number(short) -> Number<int>;
```

### 4. Deduction для конструкторов
```cpp
template<typename T>
class Smart {
public:
    // Конструктор шаблона
    template<typename U>
    Smart(U&& value);
};
// Guide для perfect forwarding
template<typename U>
Smart(U) -> Smart<std::decay_t<U>>;
```

### 5. CTAD с наследованием
```cpp
template<typename T>
class Derived : public std::vector<T> {
    using std::vector<T>::vector;
};
// Guide для наследника
template<typename T>
Derived(std::initializer_list<T>) -> Derived<T>;
```

### 6. Ограничения
```cpp
// Нельзя использовать с частичной специализацией
template<typename T>
class Special<std::vector<T>> {  // Частичная специализация
    // ...
};
// Deduction guides не работают здесь

// Нельзя с non-type параметрами
template<typename T, size_t N>
class Fixed {
    std::array<T, N> arr_;
};
// Guide не может вывести N
```

### 7. Best practices
```cpp
// 1. Используй guides только когда нужно
template<typename T>
class Optional {
    T* ptr_;
public:
    Optional(T* p) : ptr_(p) {}
};
// Guide не нужен, тип выводится автоматически

// 2. Делай guides максимально общими
template<typename Container>
class Adaptor {
    Container cont_;
public:
    Adaptor(const Container& c) : cont_(c) {}
};
template<typename Container>
Adaptor(Container) -> Adaptor<Container>;
```
