# Aggregate Initialization

## Определение
Aggregate initialization - способ инициализации агрегатных типов (массивов и классов/структур с публичными членами без пользовательских конструкторов) с помощью списка инициализации.

## Зачем это нужно
- Простая и понятная инициализация структур данных
- Уменьшение ошибок инициализации
- Улучшение читаемости кода
- Явное указание инициализируемых членов
- Предотвращение случайного пропуска инициализации

## Примеры

### ✅ Хорошо
```cpp
// Базовая агрегатная инициализация
struct Point {
    int x, y;
};
Point p1{1, 2};  // Прямая инициализация
Point p2 = {1, 2};  // Copy initialization

// Вложенная инициализация
struct Rectangle {
    Point topLeft;
    Point bottomRight;
};
Rectangle rect{{0, 0}, {10, 10}};

// C++20 designated initializers
struct Config {
    int width;
    int height;
    bool fullscreen;
};
Config cfg{
    .width = 1920,
    .height = 1080,
    .fullscreen = false
};

// Массивы
int arr[] = {1, 2, 3, 4, 5};
std::array<int, 3> stdArr{1, 2, 3};
```

### ❌ Плохо
```cpp
// Пропуск инициализации
struct Data {
    int a, b, c;
};
Data d{1, 2};  // c не инициализирован!

// Неправильный порядок designated initializers
struct Settings {
    int x, y;
};
Settings s{
    .y = 2,
    .x = 1  // Должно быть в порядке объявления
};

// Смешивание стилей
struct Mixed {
    int a, b, c;
};
Mixed m{.a = 1, 2, .c = 3};  // Ошибка!
```

## Нюансы использования

### 1. Правила агрегации
```cpp
// Это агрегат:
struct Aggregate {
    int x;
    std::string s;
};

// Это НЕ агрегат:
struct NonAggregate {
    int x;
    NonAggregate(int v) : x(v) {}  // Пользовательский конструктор
};
```

### 2. Вложенная инициализация
```cpp
struct Inner {
    int x, y;
};

struct Outer {
    Inner in;
    int z;
};

// Разные способы инициализации
Outer o1{{1, 2}, 3};        // Вложенные {}
Outer o2{Inner{1, 2}, 3};   // Явное создание Inner
Outer o3{.in = {1, 2}, .z = 3};  // Designated
```

### 3. Designated Initializers
```cpp
struct Config {
    std::string host;
    int port;
    bool secure;
};

// Все поля должны быть указаны в порядке объявления
Config c{
    .host = "localhost",
    .port = 8080,
    .secure = true
};
```

### 4. Инициализация массивов
```cpp
// Базовые массивы
int arr1[3] = {1, 2, 3};
int arr2[] = {1, 2, 3};  // Размер выводится

// std::array
std::array<int, 3> arr3 = {1, 2, 3};
std::array arr4 = {1, 2, 3};  // C++17 CTAD
```

### 5. Zero initialization
```cpp
struct Data {
    int a, b, c;
};

// Все члены zero-initialized
Data d{};

// Частичная инициализация
Data d2{1};  // b и c zero-initialized
```

### 6. Narrowing conversion
```cpp
struct Precise {
    int x;
    double y;
};

Precise p1{1, 2.0};     // OK
Precise p2{1.5, 2.0};   // Error: narrowing
Precise p3 = {1, 2.0};  // OK
```

### 7. Ограничения
```cpp
// Нельзя использовать designated initializers с:
// 1. Базовыми классами
class Derived : Base {
    int x;
};
Derived d{.x = 1};  // Ошибка

// 2. Не-public членами
struct Private {
private:
    int x;
};
Private p{.x = 1};  // Ошибка
```

### 8. Best practices
```cpp
// 1. Используй designated initializers для ясности
struct Settings {
    int width, height;
    bool fullscreen;
};

Settings s1{
    .width = 1920,
    .height = 1080,
    .fullscreen = false
};  // Понятно что инициализируется

// 2. Предпочитай {} вместо ={}
Point p{1, 2};  // Лучше
Point p = {1, 2};  // Допустимо, но менее предпочтительно

// 3. Всегда инициализируй все члены
struct Complete {
    int a = 0;  // Default member initializer
    int b = 0;
};
Complete c{.a = 1};  // b использует default value
```
