# Rule of Five

## Определение
Правило пяти в C++ гласит, что если класс определяет одну из следующих функций, он должен явно определить все пять:
1. Деструктор
2. Конструктор копирования
3. Оператор присваивания копированием
4. Конструктор перемещения
5. Оператор присваивания перемещением

## Зачем это нужно
- Полный контроль над жизненным циклом объекта
- Корректная работа с ресурсами
- Оптимизация производительности через перемещение
- Предотвращение утечек памяти
- Обеспечение exception safety

## Примеры

### ✅ Хорошо
```cpp
class Buffer {
private:
    size_t size_;
    std::unique_ptr<char[]> data_;

public:
    // 1. Деструктор (часто = default достаточно из-за smart pointer)
    ~Buffer() = default;

    // 2. Конструктор копирования
    Buffer(const Buffer& other)
        : size_(other.size_)
        , data_(std::make_unique<char[]>(size_))
    {
        std::copy(other.data_.get(), other.data_.get() + size_, data_.get());
    }

    // 3. Оператор присваивания копированием
    Buffer& operator=(const Buffer& other) {
        if (this != &other) {
            Buffer temp(other);  // Copy-and-swap идиома
            swap(temp);
        }
        return *this;
    }

    // 4. Конструктор перемещения
    Buffer(Buffer&& other) noexcept
        : size_(other.size_)
        , data_(std::move(other.data_))
    {
        other.size_ = 0;
    }

    // 5. Оператор присваивания перемещением
    Buffer& operator=(Buffer&& other) noexcept {
        if (this != &other) {
            size_ = other.size_;
            data_ = std::move(other.data_);
            other.size_ = 0;
        }
        return *this;
    }

    // Вспомогательный метод для copy-and-swap
    void swap(Buffer& other) noexcept {
        using std::swap;
        swap(size_, other.size_);
        swap(data_, other.data_);
    }
};
```

### ❌ Плохо
```cpp
class Wrong {
    int* data_;
public:
    // Только деструктор - нарушение правила пяти
    ~Wrong() { delete data_; }
    
    // Остальные операции используют дефолтную реализацию
    // Приведёт к double-delete или утечкам!
};

class Incomplete {
    std::unique_ptr<Resource> res_;
public:
    // Забыли определить move операции
    Incomplete(const Incomplete&) = delete;
    Incomplete& operator=(const Incomplete&) = delete;
    // Теперь объект нельзя перемещать!
};
```

## Нюансы использования

### 1. Rule of Zero
```cpp
class Modern {
    std::string str_;        // RAII-типы
    std::vector<int> vec_;   // сами управляют
    std::unique_ptr<Resource> ptr_; // ресурсами
    // Не нужно определять ни одну из пяти функций!
};
```

### 2. noexcept для move операций
```cpp
class Safe {
    std::string data_;
public:
    // Move операции должны быть noexcept
    Safe(Safe&& other) noexcept = default;
    Safe& operator=(Safe&& other) noexcept = default;
};
```

### 3. Copy-and-Swap идиома
```cpp
class Swappable {
    Resource* res_;
public:
    void swap(Swappable& other) noexcept {
        using std::swap;
        swap(res_, other.res_);
    }
    
    Swappable& operator=(Swappable other) {
        swap(other);
        return *this;
    }
};
```

### 4. =default и =delete
```cpp
class Special {
public:
    // Явно запрещаем копирование
    Special(const Special&) = delete;
    Special& operator=(const Special&) = delete;
    
    // Но разрешаем перемещение
    Special(Special&&) = default;
    Special& operator=(Special&&) = default;
};
```

### 5. Виртуальный деструктор
```cpp
class Base {
public:
    virtual ~Base() = default;  // Если класс базовый
    
    // Остальные операции тоже виртуальные
    virtual Base* clone() const = 0;
};
```

### 6. Strong Exception Guarantee
```cpp
class Exception {
    std::unique_ptr<Resource> res_;
public:
    Exception& operator=(const Exception& other) {
        auto temp = std::make_unique<Resource>(*other.res_);
        res_ = std::move(temp);
        return *this;
    }
};
```
