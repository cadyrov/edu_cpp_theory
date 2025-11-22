# Exception Safety

## Определение
Exception Safety - набор гарантий, которые код предоставляет при возникновении исключений. Включает базовую, строгую и нет-исключений гарантии.

## Зачем это нужно
- Предотвращение утечек ресурсов
- Сохранение согласованности данных
- Предсказуемое поведение при ошибках
- Надёжность программы

## Примеры

### ✅ Хорошо
```cpp
// Строгая гарантия через RAII
class BankAccount {
    std::string name_;
    double balance_;
public:
    void transfer(BankAccount& to, double amount) {
        auto old_balance = balance_;
        auto old_to_balance = to.balance_;
        
        try {
            decrease(amount);
            to.increase(amount);
        } catch (...) {
            // Восстановление состояния при ошибке
            balance_ = old_balance;
            to.balance_ = old_to_balance;
            throw;  // Перебрасываем исключение
        }
    }
};

// Базовая гарантия через smart pointers
class Resource {
    std::unique_ptr<Data> data_;
public:
    void process() {
        // При исключении память освободится
        data_ = std::make_unique<Data>();
        data_->doWork();  // Может бросить исключение
    }
};

// No-throw гарантия
class NoThrow {
public:
    void swap(NoThrow& other) noexcept {
        using std::swap;
        swap(data_, other.data_);
    }
private:
    int data_;
};
```

### ❌ Плохо
```cpp
// Утечка при исключении
void leak() {
    Resource* res = new Resource();
    doSomething();  // Может бросить исключение
    delete res;     // Никогда не выполнится
}

// Нарушение инвариантов
class Broken {
    std::string name_;
    std::vector<int> data_;
public:
    void update(const std::string& name, const std::vector<int>& data) {
        name_ = name;   // Если тут исключение
        data_ = data;   // Объект в неконсистентном состоянии
    }
};

// Неправильная обработка исключений
void silentFail() {
    try {
        riskyOperation();
    } catch (...) {
        // Проглатывание исключения без обработки
    }
}
```

## Нюансы использования

### 1. Уровни гарантий
```cpp
// Базовая гарантия - нет утечек
void basic() {
    std::vector<std::string> vec;
    vec.push_back("data");  // Может бросить, но память в порядке
}

// Строгая гарантия - атомарные изменения
class Atomic {
    void update() {
        auto temp = *this;  // Копия текущего состояния
        // Изменения...
        *this = std::move(temp);  // Атомарная замена
    }
};

// Нет исключений
void noexcept_func() noexcept {
    // Гарантированно не бросает
}
```

### 2. RAII и исключения
```cpp
void safe() {
    std::lock_guard<std::mutex> lock(mutex_);
    // Мьютекс освободится даже при исключении
}
```

### 3. Деструкторы
```cpp
class Safe {
    ~Safe() noexcept {  // Деструкторы должны быть noexcept
        try {
            cleanup();
        } catch (...) {
            // Логируем и продолжаем
        }
    }
};
```

### 4. Транзакционное поведение
```cpp
template<typename F>
void transaction(F&& func) {
    auto backup = state_;
    try {
        func();
    } catch (...) {
        state_ = backup;
        throw;
    }
}
```

### 5. std::exception_ptr
```cpp
std::exception_ptr eptr;
try {
    riskyCode();
} catch (...) {
    eptr = std::current_exception();
}
// Позже...
if (eptr) {
    std::rethrow_exception(eptr);
}
```
