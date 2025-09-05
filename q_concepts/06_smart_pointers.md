# Smart Pointers

## Определение
Умные указатели - классы-обёртки над сырыми указателями, реализующие RAII для автоматического управления динамической памятью.

## Зачем это нужно
- Автоматическое освобождение памяти
- Защита от утечек
- Явное выражение владения ресурсом
- Exception-safety
- Предотвращение проблем с сырыми указателями

## Примеры

### ✅ Хорошо
```cpp
// unique_ptr для эксклюзивного владения
std::unique_ptr<Resource> createResource() {
    return std::make_unique<Resource>();
}

// shared_ptr для разделяемого владения
class SharedState {
    std::shared_ptr<State> state_;
public:
    void share(Other& other) {
        other.setState(state_);  // Безопасная передача владения
    }
};

// weak_ptr для предотвращения циклических ссылок
class Node {
    std::shared_ptr<Node> next_;
    std::weak_ptr<Node> parent_;  // Слабая ссылка
};
```

### ❌ Плохо
```cpp
// Смешивание сырых и умных указателей
void wrong(Resource* res) {
    std::unique_ptr<Resource> ptr(res);
    // res может быть удалён где-то ещё
}

// Ручное удаление из unique_ptr
auto ptr = std::make_unique<Resource>();
delete ptr.get();  // НИКОГДА так не делай!

// Неправильное использование shared_ptr
std::shared_ptr<Resource> global_ptr;  // Глобальные shared_ptr опасны
```

## Нюансы использования

### 1. Создание
```cpp
// Предпочитай make_функции
auto u = std::make_unique<Resource>();
auto s = std::make_shared<Resource>();

// Избегай
std::unique_ptr<Resource> u(new Resource());  // Менее безопасно
```

### 2. Преобразования
```cpp
std::unique_ptr<Base> b = std::make_unique<Derived>();
std::shared_ptr<Base> s = std::make_shared<Derived>();

// Нельзя преобразовать unique_ptr в shared_ptr напрямую
auto s2 = std::shared_ptr<Resource>(std::move(u));
```

### 3. Кастомные делитеры
```cpp
auto deleter = [](FILE* f) { fclose(f); };
std::unique_ptr<FILE, decltype(deleter)> 
    file(fopen("data.txt", "r"), deleter);
```

### 4. Циклические ссылки
```cpp
struct Node {
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;  // Используй weak_ptr
};
```

### 5. Производительность
```cpp
// shared_ptr имеет overhead
struct Control {
    std::atomic<int> ref_count;
    Resource* ptr;
};

// unique_ptr - zero overhead
static_assert(sizeof(std::unique_ptr<int>) == sizeof(int*));
```

### 6. Array форма
```cpp
// Для массивов используй специальную форму
auto arr = std::make_unique<int[]>(100);
// или лучше vector
std::vector<int> vec(100);
```

### 7. enable_shared_from_this
```cpp
class Shared : public std::enable_shared_from_this<Shared> {
public:
    std::shared_ptr<Shared> getPtr() {
        return shared_from_this();
    }
};
```
