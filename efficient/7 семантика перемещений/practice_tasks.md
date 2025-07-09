# Практические задания по семантике перемещений

## Задание 1: Реализация класса с move-семантикой

### Описание
Реализуйте класс `Buffer`, который управляет динамически выделенной памятью и поддерживает move-семантику. Класс должен содержать:
- Конструктор по умолчанию
- Конструктор с размером буфера
- Конструктор копирования
- Конструктор перемещения
- Оператор присваивания копированием
- Оператор присваивания перемещением
- Деструктор
- Методы для получения размера и данных

```cpp
class Buffer {
private:
    char* data_;
    size_t size_;
    
public:
    // Ваша реализация
};
```

### Тесты
```cpp
// Тест 1: Конструктор по умолчанию
Buffer buf;
assert(buf.size() == 0);
assert(buf.data() == nullptr);

// Тест 2: Конструктор с размером
Buffer buf(100);
assert(buf.size() == 100);
assert(buf.data() != nullptr);

// Тест 3: Конструктор копирования
Buffer buf1(50);
Buffer buf2(buf1);
assert(buf2.size() == 50);
assert(buf2.data() != buf1.data());

// Тест 4: Конструктор перемещения
Buffer buf1(50);
char* original_data = buf1.data();
Buffer buf2(std::move(buf1));
assert(buf2.size() == 50);
assert(buf2.data() == original_data);
assert(buf1.size() == 0);
assert(buf1.data() == nullptr);

// Тест 5: Оператор присваивания копированием
Buffer buf1(30);
Buffer buf2;
buf2 = buf1;
assert(buf2.size() == 30);
assert(buf2.data() != buf1.data());

// Тест 6: Оператор присваивания перемещением
Buffer buf1(30);
Buffer buf2;
char* original_data = buf1.data();
buf2 = std::move(buf1);
assert(buf2.size() == 30);
assert(buf2.data() == original_data);
assert(buf1.size() == 0);

// Тест 7: Самоприсваивание при перемещении
Buffer buf(40);
buf = std::move(buf);
assert(buf.size() == 40);
assert(buf.data() != nullptr);

// Тест 8: Цепочка присваиваний
Buffer buf1(20);
Buffer buf2, buf3;
buf3 = buf2 = buf1;
assert(buf3.size() == 20);

// Тест 9: Перемещение в контейнер
std::vector<Buffer> vec;
vec.push_back(Buffer(60));
assert(vec[0].size() == 60);

// Тест 10: Множественные перемещения
Buffer buf1(25);
Buffer buf2(std::move(buf1));
Buffer buf3(std::move(buf2));
assert(buf3.size() == 25);
assert(buf1.size() == 0);
assert(buf2.size() == 0);
```

## Задание 2: Оптимизация функции с move-семантикой

### Описание
Оптимизируйте следующую функцию для работы с move-семантикой. Функция должна эффективно обрабатывать как lvalue, так и rvalue аргументы:

```cpp
class StringProcessor {
private:
    std::vector<std::string> strings_;
    
public:
    // Оптимизируйте эту функцию
    void AddString(/* параметры */);
    
    // Добавьте перегрузку для множественного добавления
    void AddStrings(/* параметры */);
    
    size_t GetCount() const { return strings_.size(); }
    const std::string& GetString(size_t index) const { return strings_[index]; }
};
```

### Тесты
```cpp
// Тест 1: Добавление lvalue строки
StringProcessor processor;
std::string str = "test";
processor.AddString(str);
assert(processor.GetCount() == 1);
assert(str == "test"); // Строка не должна быть перемещена

// Тест 2: Добавление rvalue строки
processor.AddString(std::string("hello"));
assert(processor.GetCount() == 2);

// Тест 3: Добавление через move
std::string str2 = "world";
processor.AddString(std::move(str2));
assert(processor.GetCount() == 3);
assert(str2.empty()); // Строка должна быть перемещена

// Тест 4: Добавление временной строки
processor.AddString("temporary");
assert(processor.GetCount() == 4);

// Тест 5: Добавление множественных строк через lvalue
std::vector<std::string> strings = {"a", "b", "c"};
processor.AddStrings(strings);
assert(processor.GetCount() == 7);

// Тест 6: Добавление множественных строк через rvalue
processor.AddStrings(std::vector<std::string>{"d", "e"});
assert(processor.GetCount() == 9);

// Тест 7: Добавление множественных строк через move
std::vector<std::string> more_strings = {"f", "g", "h"};
processor.AddStrings(std::move(more_strings));
assert(processor.GetCount() == 12);
assert(more_strings.empty());

// Тест 8: Проверка содержимого
assert(processor.GetString(0) == "test");
assert(processor.GetString(1) == "hello");
assert(processor.GetString(2) == "world");

// Тест 9: Производительность - много добавлений
for (int i = 0; i < 1000; ++i) {
    processor.AddString(std::to_string(i));
}
assert(processor.GetCount() == 1012);

// Тест 10: Смешанное использование
std::string mixed = "mixed";
processor.AddString(mixed);
processor.AddString(std::move(mixed));
assert(processor.GetCount() == 1014);
```

## Задание 3: Реализация move-only класса

### Описание
Реализуйте класс `UniqueResource`, который может быть только перемещен, но не скопирован. Класс должен управлять уникальным ресурсом:

```cpp
class UniqueResource {
private:
    int* resource_;
    int id_;
    
public:
    explicit UniqueResource(int id);
    ~UniqueResource();
    
    // Запретить копирование
    UniqueResource(const UniqueResource&) = delete;
    UniqueResource& operator=(const UniqueResource&) = delete;
    
    // Разрешить перемещение
    UniqueResource(UniqueResource&& other) noexcept;
    UniqueResource& operator=(UniqueResource&& other) noexcept;
    
    int GetId() const;
    int GetValue() const;
    void SetValue(int value);
    bool IsValid() const;
};
```

### Тесты
```cpp
// Тест 1: Создание ресурса
UniqueResource res(42);
assert(res.GetId() == 42);
assert(res.IsValid());

// Тест 2: Попытка копирования (должна не компилироваться)
// UniqueResource res2 = res; // Ошибка компиляции

// Тест 3: Перемещение через конструктор
UniqueResource res1(10);
UniqueResource res2(std::move(res1));
assert(res2.GetId() == 10);
assert(res2.IsValid());
assert(!res1.IsValid());

// Тест 4: Перемещение через оператор присваивания
UniqueResource res3(20);
UniqueResource res4(30);
res4 = std::move(res3);
assert(res4.GetId() == 20);
assert(!res3.IsValid());

// Тест 5: Самоприсваивание
UniqueResource res5(40);
res5 = std::move(res5);
assert(res5.GetId() == 40);
assert(res5.IsValid());

// Тест 6: Работа с значениями
UniqueResource res6(50);
res6.SetValue(100);
assert(res6.GetValue() == 100);

// Тест 7: Перемещение в контейнер
std::vector<UniqueResource> vec;
vec.push_back(UniqueResource(60));
assert(vec[0].GetId() == 60);

// Тест 8: Перемещение из контейнера
std::vector<UniqueResource> vec2;
vec2.push_back(UniqueResource(70));
UniqueResource extracted = std::move(vec2[0]);
assert(extracted.GetId() == 70);
assert(!vec2[0].IsValid());

// Тест 9: Цепочка перемещений
UniqueResource res7(80);
UniqueResource res8(std::move(res7));
UniqueResource res9(std::move(res8));
assert(res9.GetId() == 80);
assert(!res7.IsValid());
assert(!res8.IsValid());

// Тест 10: Перемещение в функцию
auto process = [](UniqueResource r) { return r.GetId(); };
UniqueResource res10(90);
int id = process(std::move(res10));
assert(id == 90);
assert(!res10.IsValid());
```

## Задание 4: Оптимизация с move-итераторами

### Описание
Реализуйте функцию `TransferElements`, которая эффективно перемещает элементы из одного контейнера в другой, используя move-итераторы:

```cpp
template<typename Container>
void TransferElements(Container& source, Container& destination) {
    // Ваша реализация
}

// Дополнительно реализуйте функцию для частичного перемещения
template<typename Container>
void TransferRange(Container& source, Container& destination, 
                   size_t start, size_t count) {
    // Ваша реализация
}
```

### Тесты
```cpp
// Тест 1: Перемещение всех элементов
std::vector<std::string> source = {"a", "b", "c"};
std::vector<std::string> dest;
TransferElements(source, dest);
assert(dest.size() == 3);
assert(dest[0] == "a");
assert(source[0].empty()); // Элементы перемещены

// Тест 2: Перемещение в непустой контейнер
std::vector<std::string> source2 = {"d", "e"};
TransferElements(source2, dest);
assert(dest.size() == 5);
assert(dest[3] == "d");

// Тест 3: Перемещение пустого контейнера
std::vector<std::string> empty_source;
std::vector<std::string> dest2;
TransferElements(empty_source, dest2);
assert(dest2.empty());

// Тест 4: Перемещение диапазона
std::vector<std::string> source3 = {"x", "y", "z", "w"};
std::vector<std::string> dest3;
TransferRange(source3, dest3, 1, 2);
assert(dest3.size() == 2);
assert(dest3[0] == "y");
assert(dest3[1] == "z");
assert(source3[1].empty());
assert(source3[2].empty());

// Тест 5: Перемещение с разными типами контейнеров
std::vector<std::string> vec_source = {"1", "2", "3"};
std::deque<std::string> deque_dest;
TransferElements(vec_source, deque_dest);
assert(deque_dest.size() == 3);

// Тест 6: Перемещение больших объектов
std::vector<std::vector<int>> big_source;
big_source.push_back(std::vector<int>(1000, 42));
std::vector<std::vector<int>> big_dest;
TransferElements(big_source, big_dest);
assert(big_dest[0].size() == 1000);
assert(big_source[0].empty());

// Тест 7: Перемещение с выходом за границы
std::vector<std::string> source4 = {"a", "b"};
std::vector<std::string> dest4;
TransferRange(source4, dest4, 0, 5); // Больше чем есть
assert(dest4.size() == 2);

// Тест 8: Перемещение с нулевым количеством
std::vector<std::string> source5 = {"a", "b", "c"};
std::vector<std::string> dest5;
TransferRange(source5, dest5, 1, 0);
assert(dest5.empty());
assert(source5[0] == "a"); // Не перемещены

// Тест 9: Производительность - много элементов
std::vector<std::string> large_source;
for (int i = 0; i < 10000; ++i) {
    large_source.push_back(std::to_string(i));
}
std::vector<std::string> large_dest;
TransferElements(large_source, large_dest);
assert(large_dest.size() == 10000);

// Тест 10: Перемещение уникальных объектов
std::vector<std::unique_ptr<int>> ptr_source;
ptr_source.push_back(std::make_unique<int>(42));
std::vector<std::unique_ptr<int>> ptr_dest;
TransferElements(ptr_source, ptr_dest);
assert(ptr_dest[0] && *ptr_dest[0] == 42);
assert(!ptr_source[0]);
```

## Задание 5: Реализация строкового класса с SSO

### Описание
Реализуйте упрощенную версию строкового класса с Small String Optimization (SSO) и полной поддержкой move-семантики:

```cpp
class MyString {
private:
    static const size_t SMALL_SIZE = 15;
    
    union {
        char small_[SMALL_SIZE + 1];
        struct {
            char* data_;
            size_t capacity_;
        } large_;
    };
    
    size_t size_;
    bool is_small_;
    
public:
    MyString();
    MyString(const char* str);
    MyString(const MyString& other);
    MyString(MyString&& other) noexcept;
    ~MyString();
    
    MyString& operator=(const MyString& other);
    MyString& operator=(MyString&& other) noexcept;
    
    const char* c_str() const;
    size_t size() const;
    bool empty() const;
    void clear();
    
    MyString& operator+=(const MyString& other);
    friend MyString operator+(const MyString& lhs, const MyString& rhs);
};
```

### Тесты
```cpp
// Тест 1: Создание пустой строки
MyString str;
assert(str.empty());
assert(str.size() == 0);

// Тест 2: Создание короткой строки (SSO)
MyString short_str("hello");
assert(short_str.size() == 5);
assert(strcmp(short_str.c_str(), "hello") == 0);

// Тест 3: Создание длинной строки
MyString long_str("this is a very long string that exceeds SSO limit");
assert(long_str.size() > 15);
assert(strstr(long_str.c_str(), "very long") != nullptr);

// Тест 4: Копирование короткой строки
MyString str1("short");
MyString str2(str1);
assert(str2.size() == 5);
assert(strcmp(str2.c_str(), "short") == 0);

// Тест 5: Копирование длинной строки
MyString long1("this is a very long string");
MyString long2(long1);
assert(long2.size() == long1.size());
assert(strcmp(long2.c_str(), long1.c_str()) == 0);

// Тест 6: Перемещение короткой строки
MyString str3("move");
MyString str4(std::move(str3));
assert(str4.size() == 4);
assert(strcmp(str4.c_str(), "move") == 0);

// Тест 7: Перемещение длинной строки
MyString long3("this is a very long string for moving");
MyString long4(std::move(long3));
assert(long4.size() > 15);
assert(long3.empty()); // Перемещена

// Тест 8: Присваивание с перемещением
MyString str5("original");
MyString str6("replacement");
str5 = std::move(str6);
assert(strcmp(str5.c_str(), "replacement") == 0);

// Тест 9: Конкатенация
MyString str7("Hello");
MyString str8(" World");
MyString result = str7 + str8;
assert(strcmp(result.c_str(), "Hello World") == 0);

// Тест 10: Очистка строки
MyString str9("to be cleared");
str9.clear();
assert(str9.empty());
assert(str9.size() == 0);
```

## Задание 6: Реализация кэша с move-семантикой

### Описание
Реализуйте простой LRU кэш, который эффективно работает с move-семантикой:

```cpp
template<typename Key, typename Value>
class LRUCache {
private:
    struct Node {
        Key key;
        Value value;
        Node* prev;
        Node* next;
        
        Node(Key k, Value v) : key(std::move(k)), value(std::move(v)), prev(nullptr), next(nullptr) {}
    };
    
    size_t capacity_;
    std::unordered_map<Key, Node*> cache_;
    Node* head_;
    Node* tail_;
    
public:
    explicit LRUCache(size_t capacity);
    ~LRUCache();
    
    void Put(Key key, Value value);
    std::optional<Value> Get(const Key& key);
    size_t Size() const;
    bool Empty() const;
    void Clear();
};
```

### Тесты
```cpp
// Тест 1: Создание кэша
LRUCache<int, std::string> cache(3);
assert(cache.Empty());
assert(cache.Size() == 0);

// Тест 2: Добавление элементов
cache.Put(1, std::string("one"));
cache.Put(2, std::string("two"));
assert(cache.Size() == 2);

// Тест 3: Получение элементов
auto value = cache.Get(1);
assert(value.has_value());
assert(value.value() == "one");

// Тест 4: Получение несуществующего элемента
auto missing = cache.Get(999);
assert(!missing.has_value());

// Тест 5: Превышение емкости
cache.Put(3, std::string("three"));
cache.Put(4, std::string("four")); // Должен вытеснить элемент
assert(cache.Size() == 3);
assert(!cache.Get(1).has_value()); // Первый элемент вытеснен

// Тест 6: Обновление существующего ключа
cache.Put(2, std::string("two_updated"));
auto updated = cache.Get(2);
assert(updated.value() == "two_updated");

// Тест 7: Перемещение больших объектов
LRUCache<int, std::vector<int>> vec_cache(2);
std::vector<int> big_vec(1000, 42);
vec_cache.Put(1, std::move(big_vec));
assert(big_vec.empty()); // Вектор перемещен

// Тест 8: Очистка кэша
cache.Clear();
assert(cache.Empty());
assert(cache.Size() == 0);

// Тест 9: Работа с move-only типами
LRUCache<int, std::unique_ptr<int>> ptr_cache(2);
ptr_cache.Put(1, std::make_unique<int>(42));
auto ptr = ptr_cache.Get(1);
assert(ptr.has_value());

// Тест 10: Последовательность операций
LRUCache<std::string, int> str_cache(3);
str_cache.Put("a", 1);
str_cache.Put("b", 2);
str_cache.Put("c", 3);
str_cache.Get("a"); // Делает "a" самым свежим
str_cache.Put("d", 4); // Должен вытеснить "b"
assert(!str_cache.Get("b").has_value());
assert(str_cache.Get("a").has_value());
```

## Задание 7: Реализация пула объектов

### Описание
Реализуйте пул объектов, который эффективно переиспользует объекты с помощью move-семантики:

```cpp
template<typename T>
class ObjectPool {
private:
    std::vector<T> pool_;
    std::vector<bool> used_;
    size_t next_free_;
    
public:
    explicit ObjectPool(size_t initial_size = 10);
    
    template<typename... Args>
    T* Acquire(Args&&... args);
    
    void Release(T* obj);
    
    size_t Size() const;
    size_t Available() const;
    void Clear();
    
private:
    size_t FindFreeSlot();
    void Expand();
};
```

### Тесты
```cpp
// Тест 1: Создание пула
ObjectPool<std::string> pool(5);
assert(pool.Size() == 5);
assert(pool.Available() == 5);

// Тест 2: Получение объекта
auto* str = pool.Acquire("hello");
assert(str != nullptr);
assert(*str == "hello");
assert(pool.Available() == 4);

// Тест 3: Освобождение объекта
pool.Release(str);
assert(pool.Available() == 5);

// Тест 4: Множественное получение
std::vector<std::string*> ptrs;
for (int i = 0; i < 3; ++i) {
    ptrs.push_back(pool.Acquire(std::to_string(i)));
}
assert(pool.Available() == 2);

// Тест 5: Освобождение множественных объектов
for (auto* ptr : ptrs) {
    pool.Release(ptr);
}
assert(pool.Available() == 5);

// Тест 6: Расширение пула
for (int i = 0; i < 7; ++i) {
    pool.Acquire("test");
}
assert(pool.Size() > 5); // Пул расширился

// Тест 7: Работа с move-only типами
ObjectPool<std::unique_ptr<int>> ptr_pool(3);
auto* unique_ptr = ptr_pool.Acquire(std::make_unique<int>(42));
assert(unique_ptr != nullptr);
assert(**unique_ptr == 42);

// Тест 8: Очистка пула
pool.Clear();
assert(pool.Available() == 0);
assert(pool.Size() == 0);

// Тест 9: Пул для сложных объектов
struct ComplexObject {
    std::string name;
    std::vector<int> data;
    
    ComplexObject(std::string n, std::vector<int> d) 
        : name(std::move(n)), data(std::move(d)) {}
};

ObjectPool<ComplexObject> complex_pool(2);
auto* complex = complex_pool.Acquire("test", std::vector<int>{1, 2, 3});
assert(complex->name == "test");
assert(complex->data.size() == 3);

// Тест 10: Производительность - много операций
ObjectPool<std::vector<int>> vec_pool(100);
for (int i = 0; i < 1000; ++i) {
    auto* vec = vec_pool.Acquire(100, i);
    assert(vec->size() == 100);
    vec_pool.Release(vec);
}
```

## Задание 8: Реализация функции perfect forwarding

### Описание
Реализуйте шаблонную функцию `MakeAndProcess`, которая создает объект и передает его в функцию обработки с идеальной передачей параметров:

```cpp
template<typename T, typename Processor, typename... Args>
auto MakeAndProcess(Processor&& processor, Args&&... args) {
    // Ваша реализация
}

// Дополнительно реализуйте фабрику объектов
template<typename T>
class Factory {
public:
    template<typename... Args>
    static T Create(Args&&... args) {
        // Ваша реализация
    }
    
    template<typename... Args>
    static std::unique_ptr<T> CreateUnique(Args&&... args) {
        // Ваша реализация
    }
};
```

### Тесты
```cpp
// Тест 1: Создание и обработка простого объекта
auto processor = [](const std::string& s) { return s.size(); };
auto result = MakeAndProcess<std::string>(processor, "hello");
assert(result == 5);

// Тест 2: Создание с множественными параметрами
struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

auto point_processor = [](const Point& p) { return p.x + p.y; };
auto sum = MakeAndProcess<Point>(point_processor, 3, 4);
assert(sum == 7);

// Тест 3: Передача lvalue параметров
std::string name = "test";
int value = 42;
auto complex_processor = [](const std::string& n, int v) { return n + std::to_string(v); };
auto complex_result = MakeAndProcess<std::pair<std::string, int>>(
    [](const std::pair<std::string, int>& p) { return p.first + std::to_string(p.second); },
    name, value
);
assert(name == "test"); // Не должно быть перемещено

// Тест 4: Передача rvalue параметров
auto rvalue_result = MakeAndProcess<std::string>(
    [](const std::string& s) { return s.length(); },
    std::string("temporary")
);
assert(rvalue_result == 9);

// Тест 5: Фабрика с простым типом
auto str = Factory<std::string>::Create("factory");
assert(str == "factory");

// Тест 6: Фабрика с unique_ptr
auto unique_str = Factory<std::string>::CreateUnique("unique");
assert(*unique_str == "unique");

// Тест 7: Фабрика с move-only типом
auto unique_vec = Factory<std::vector<int>>::CreateUnique(5, 42);
assert(unique_vec->size() == 5);
assert((*unique_vec)[0] == 42);

// Тест 8: Передача move-only параметров
auto move_processor = [](std::unique_ptr<int> ptr) { return *ptr; };
auto move_result = MakeAndProcess<std::unique_ptr<int>>(
    move_processor, std::make_unique<int>(100)
);
assert(move_result == 100);

// Тест 9: Сложная фабрика
struct ComplexType {
    std::string name;
    std::vector<int> data;
    std::unique_ptr<int> ptr;
    
    ComplexType(std::string n, std::vector<int> d, std::unique_ptr<int> p)
        : name(std::move(n)), data(std::move(d)), ptr(std::move(p)) {}
};

auto complex = Factory<ComplexType>::Create(
    std::string("complex"),
    std::vector<int>{1, 2, 3},
    std::make_unique<int>(42)
);
assert(complex.name == "complex");
assert(complex.data.size() == 3);
assert(*complex.ptr == 42);

// Тест 10: Производительность - избежание копирований
struct ExpensiveObject {
    std::vector<int> data;
    explicit ExpensiveObject(size_t size) : data(size, 42) {}
};

auto expensive_processor = [](const ExpensiveObject& obj) { return obj.data.size(); };
auto expensive_result = MakeAndProcess<ExpensiveObject>(expensive_processor, 10000);
assert(expensive_result == 10000);
```

## Задание 9: Оптимизация алгоритма сортировки

### Описание
Реализуйте оптимизированную версию алгоритма сортировки, которая эффективно использует move-семантику:

```cpp
template<typename Iterator>
void OptimizedSort(Iterator begin, Iterator end) {
    // Ваша реализация быстрой сортировки с move-семантикой
}

template<typename Iterator, typename Compare>
void OptimizedSort(Iterator begin, Iterator end, Compare comp) {
    // Ваша реализация с кастомным компаратором
}

// Дополнительно реализуйте функцию для удаления дубликатов
template<typename Container>
void RemoveDuplicatesInPlace(Container& container) {
    // Ваша реализация
}
```

### Тесты
```cpp
// Тест 1: Сортировка строк
std::vector<std::string> strings = {"zebra", "apple", "banana", "cherry"};
OptimizedSort(strings.begin(), strings.end());
assert(strings[0] == "apple");
assert(strings[1] == "banana");
assert(strings[2] == "cherry");
assert(strings[3] == "zebra");

// Тест 2: Сортировка с кастомным компаратором
std::vector<int> numbers = {5, 2, 8, 1, 9};
OptimizedSort(numbers.begin(), numbers.end(), std::greater<int>());
assert(numbers[0] == 9);
assert(numbers[4] == 1);

// Тест 3: Сортировка пустого контейнера
std::vector<int> empty;
OptimizedSort(empty.begin(), empty.end());
assert(empty.empty());

// Тест 4: Сортировка одного элемента
std::vector<std::string> single = {"alone"};
OptimizedSort(single.begin(), single.end());
assert(single[0] == "alone");

// Тест 5: Сортировка больших объектов
std::vector<std::vector<int>> big_vectors;
for (int i = 5; i > 0; --i) {
    big_vectors.push_back(std::vector<int>(i, i));
}
OptimizedSort(big_vectors.begin(), big_vectors.end(), 
    [](const std::vector<int>& a, const std::vector<int>& b) {
        return a.size() < b.size();
    });
assert(big_vectors[0].size() == 1);
assert(big_vectors[4].size() == 5);

// Тест 6: Удаление дубликатов
std::vector<int> with_duplicates = {1, 2, 2, 3, 3, 3, 4};
RemoveDuplicatesInPlace(with_duplicates);
assert(with_duplicates.size() == 4);
assert(with_duplicates[0] == 1);
assert(with_duplicates[3] == 4);

// Тест 7: Удаление дубликатов строк
std::vector<std::string> string_duplicates = {"a", "b", "a", "c", "b"};
RemoveDuplicatesInPlace(string_duplicates);
assert(string_duplicates.size() == 3);

// Тест 8: Сортировка move-only объектов
std::vector<std::unique_ptr<int>> unique_ptrs;
for (int i = 5; i > 0; --i) {
    unique_ptrs.push_back(std::make_unique<int>(i));
}
OptimizedSort(unique_ptrs.begin(), unique_ptrs.end(),
    [](const std::unique_ptr<int>& a, const std::unique_ptr<int>& b) {
        return *a < *b;
    });
assert(*unique_ptrs[0] == 1);
assert(*unique_ptrs[4] == 5);

// Тест 9: Производительность - большой массив
std::vector<int> large_array;
for (int i = 10000; i > 0; --i) {
    large_array.push_back(i);
}
OptimizedSort(large_array.begin(), large_array.end());
assert(large_array[0] == 1);
assert(large_array[9999] == 10000);

// Тест 10: Стабильность сортировки
struct Item {
    int value;
    int id;
};

std::vector<Item> items = {{3, 1}, {1, 2}, {3, 3}, {2, 4}};
OptimizedSort(items.begin(), items.end(),
    [](const Item& a, const Item& b) {
        return a.value < b.value;
    });
assert(items[0].value == 1);
assert(items[3].value == 3);
```

## Задание 10: Реализация асинхронного обработчика

### Описание
Реализуйте асинхронный обработчик задач, который эффективно использует move-семантику для передачи задач:

```cpp
template<typename T>
class AsyncProcessor {
private:
    std::queue<std::function<T()>> tasks_;
    std::mutex mutex_;
    std::condition_variable cv_;
    std::vector<std::thread> workers_;
    std::atomic<bool> stop_;
    
public:
    explicit AsyncProcessor(size_t num_workers = std::thread::hardware_concurrency());
    ~AsyncProcessor();
    
    template<typename F>
    std::future<T> Submit(F&& task);
    
    void Stop();
    size_t PendingTasks() const;
    
private:
    void WorkerLoop();
};
```

### Тесты
```cpp
// Тест 1: Создание процессора
AsyncProcessor<int> processor(2);
assert(processor.PendingTasks() == 0);

// Тест 2: Отправка простой задачи
auto future = processor.Submit([]() { return 42; });
assert(future.get() == 42);

// Тест 3: Отправка задачи с захватом по значению
int value = 100;
auto future2 = processor.Submit([value]() { return value * 2; });
assert(future2.get() == 200);

// Тест 4: Отправка задачи с захватом по перемещению
std::string text = "hello";
auto future3 = processor.Submit([text = std::move(text)]() { return text.length(); });
assert(future3.get() == 5);
assert(text.empty()); // Строка была перемещена

// Тест 5: Множественные задачи
std::vector<std::future<int>> futures;
for (int i = 0; i < 10; ++i) {
    futures.push_back(processor.Submit([i]() { return i * i; }));
}
for (int i = 0; i < 10; ++i) {
    assert(futures[i].get() == i * i);
}

// Тест 6: Задачи с различным временем выполнения
auto slow_future = processor.Submit([]() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return 1;
});
auto fast_future = processor.Submit([]() { return 2; });
assert(fast_future.get() == 2);
assert(slow_future.get() == 1);

// Тест 7: Обработка исключений
auto exception_future = processor.Submit([]() -> int {
    throw std::runtime_error("Test exception");
});
try {
    exception_future.get();
    assert(false); // Не должно выполниться
} catch (const std::runtime_error& e) {
    assert(std::string(e.what()) == "Test exception");
}

// Тест 8: Работа с move-only типами
AsyncProcessor<std::unique_ptr<int>> ptr_processor(1);
auto ptr_future = ptr_processor.Submit([]() {
    return std::make_unique<int>(42);
});
auto result_ptr = ptr_future.get();
assert(*result_ptr == 42);

// Тест 9: Остановка процессора
processor.Stop();
auto stopped_future = processor.Submit([]() { return 999; });
// Задача может быть не выполнена после остановки

// Тест 10: Производительность - много задач
AsyncProcessor<void> void_processor(4);
std::atomic<int> counter(0);
std::vector<std::future<void>> void_futures;

for (int i = 0; i < 1000; ++i) {
    void_futures.push_back(void_processor.Submit([&counter]() {
        counter.fetch_add(1);
    }));
}

for (auto& future : void_futures) {
    future.wait();
}
assert(counter.load() == 1000);
```

Каждое задание развивает понимание move-семантики в различных контекстах и помогает освоить практические навыки оптимизации кода с использованием современных возможностей C++. 