# Работа с сырой памятью

## Определение
Прямое управление памятью в C++ через операторы new/delete, размещающий new (placement new) и низкоуровневые операции с памятью.

## Зачем это нужно
- Максимальный контроль над выделением памяти
- Оптимизация производительности
- Реализация специальных аллокаторов
- Работа с устройствами и embedded системами

## Примеры

### ✅ Хорошо
```cpp
// Правильное использование new/delete
class Resource {
    int* data = nullptr;
public:
    Resource() : data(new int[100]) {}
    ~Resource() { delete[] data; }  // Правильное освобождение
};

// Размещающий new для специальных случаев
alignas(16) char buffer[1024];
auto* obj = new (buffer) MyObject();  // Размещение в существующей памяти

// Выравнивание памяти
void* aligned = std::aligned_alloc(64, size);
// использование
std::free(aligned);
```

### ❌ Плохо
```cpp
// Утечка памяти
void leak() {
    int* ptr = new int(42);
    // нет delete
}  // Утечка!

// Неправильное удаление массива
class Wrong {
    int* arr = new int[10];
    ~Wrong() { 
        delete arr;  // Должно быть delete[]
    }
};

// Двойное удаление
int* ptr = new int(42);
delete ptr;
delete ptr;  // Undefined behavior!
```

## Нюансы использования

### 1. Выделение и освобождение
```cpp
// Всегда сочетай:
new с delete
new[] с delete[]
malloc с free
```

### 2. Размещающий new
```cpp
char buffer[sizeof(MyClass)];
MyClass* obj = new (buffer) MyClass();
obj->~MyClass();  // Явный вызов деструктора необходим
```

### 3. Выравнивание
```cpp
// C++17 new с выравниванием
int* aligned = new(std::align_val_t{64}) int[1024];
delete[] aligned;

// std::aligned_storage
using aligned_int = std::aligned_storage_t<sizeof(int), alignof(int)>;
```

### 4. Обработка исключений
```cpp
try {
    auto ptr = new int[huge_number];
    // ...
} catch (const std::bad_alloc& e) {
    // Обработка нехватки памяти
}
```

### 5. Smart pointers вместо сырых указателей
```cpp
// Предпочтительнее использовать
std::unique_ptr<int[]> safe_array(new int[100]);
// Вместо
int* unsafe_array = new int[100];
```

### 6. Нестандартные аллокаторы
```cpp
void* operator new(size_t size) {
    // Кастомная аллокация
    return my_allocator.allocate(size);
}

void operator delete(void* ptr) noexcept {
    // Кастомное освобождение
    my_allocator.deallocate(ptr);
}
