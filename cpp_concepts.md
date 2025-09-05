# C++ Core Concepts Quick Reference

## Основные концепции C++

### L-value и R-value
Фундаментальная концепция C++, определяющая категории выражений и правила работы с ними.

#### Определение и свойства
- **L-value** (locator value):
  - Имеет конкретный адрес в памяти
  - Может находиться слева от оператора присваивания
  - Существует дольше одного выражения
  - Примеры: переменные, элементы массива, разыменованные указатели

- **R-value** (right value):
  - Временные объекты без адреса
  - Может находиться только справа от присваивания
  - Существует только в рамках выражения
  - Примеры: литералы, результаты функций, временные объекты

#### Ссылки и их особенности
- **L-value reference** (`Type&`):
  ```cpp
  int x = 42;
  int& ref = x;        // OK: x это l-value
  int& ref = 42;       // Ошибка: 42 это r-value
  ```

- **R-value reference** (`Type&&`):
  ```cpp
  int&& rref = 42;     // OK: привязка к r-value
  int y = 42;
  int&& rref = y;      // Ошибка: y это l-value
  ```

#### Практическое применение
1. **Оптимизация передачи объектов:**
   ```cpp
   void process(const std::string& s);     // для l-values
   void process(std::string&& s);          // для r-values
   ```

2. **Move семантика:**
   ```cpp
   std::vector<int> createVector() {
       return std::vector<int>{1,2,3};     // возврат r-value
   }
   auto v = createVector();                // move вместо копирования
   ```

3. **Perfect forwarding:**
   ```cpp
   template<typename T>
   void wrapper(T&& arg) {                 // универсальная ссылка
       process(std::forward<T>(arg));      // сохраняет категорию
   }
   ```

#### Важные моменты
- Функции и операторы могут возвращать как l-value, так и r-value
- Константные l-value ссылки могут привязываться к r-value
- std::move преобразует l-value в r-value reference
- Временные объекты продлевают время жизни при привязке к константной ссылке

### Variadic Templates
Мощный механизм метапрограммирования, позволяющий создавать шаблоны с произвольным количеством параметров.

#### Основные концепции
- **Parameter pack**: набор параметров произвольной длины
- **Pack expansion**: раскрытие пака в список параметров
- **Template parameter pack**: шаблонные параметры (`typename...`)
- **Function parameter pack**: параметры функции (`Args&&...`)

#### Синтаксис и базовые примеры
```cpp
// Базовое объявление
template<typename... Args>
void func(Args... args) {
    // args - pack параметров функции
}

// Получение размера пака
template<typename... Args>
void printSize() {
    std::cout << sizeof...(Args);  // количество типов
}

// Использование
func(1, "hello", 3.14);  // Args = {int, const char*, double}
```

#### Техники работы с паками
1. **Fold expressions** (C++17):
   ```cpp
   template<typename... Args>
   auto sum(Args... args) {
       return (... + args);  // (1 + (2 + (3 + 4)))
   }
   ```

2. **Рекурсивная обработка**:
   ```cpp
   // Базовый случай
   void print() {}
   
   // Рекурсивный случай
   template<typename T, typename... Args>
   void print(T first, Args... rest) {
       std::cout << first;
       print(rest...);  // рекурсивный вызов
   }
   ```

3. **Perfect forwarding**:
   ```cpp
   template<typename... Args>
   void wrapper(Args&&... args) {
       process(std::forward<Args>(args)...);
   }
   ```

#### Продвинутые приемы
1. **Tuple и pack**:
   ```cpp
   template<typename... Args>
   auto makeWrapper(Args&&... args) {
       return std::make_tuple(std::forward<Args>(args)...);
   }
   ```

2. **Variadic inheritance**:
   ```cpp
   template<typename... Mixins>
   class Combined : public Mixins... {
   public:
       Combined(const Mixins&... mixins) : Mixins(mixins)... {}
   };
   ```

#### Важные моменты
- Parameter pack может быть пустым
- Раскрытие пака должно создавать валидное выражение
- C++17 fold expressions упрощают работу с паками
- Можно комбинировать с другими шаблонными механизмами
- При perfect forwarding важно сохранять категории значений

### Rule of Five
Фундаментальное правило C++, определяющее набор специальных функций-членов класса для корректного управления ресурсами.

#### Основные компоненты
1. **Деструктор** (`~Class()`):
   - Освобождает ресурсы
   - Всегда вызывается при уничтожении объекта
   - Должен быть noexcept
   - Виртуальный для базовых классов

2. **Конструктор копирования** (`Class(const Class&)`):
   - Создает глубокую копию объекта
   - Обеспечивает сильную гарантию исключений
   - Не должен изменять оригинал

3. **Оператор присваивания копированием** (`Class& operator=(const Class&)`):
   - Копирует ресурсы с проверкой self-assignment
   - Освобождает старые ресурсы
   - Обеспечивает сильную гарантию исключений

4. **Конструктор перемещения** (`Class(Class&&) noexcept`):
   - Забирает ресурсы у другого объекта
   - Всегда помечается noexcept
   - Оставляет источник в валидном состоянии

5. **Оператор присваивания перемещением** (`Class& operator=(Class&&) noexcept`):
   - Освобождает старые ресурсы
   - Забирает ресурсы у другого объекта
   - Всегда помечается noexcept

#### Примеры реализации
```cpp
class ResourceManager {
    Resource* ptr;
public:
    // Деструктор
    ~ResourceManager() noexcept {
        delete ptr;
    }

    // Конструктор копирования
    ResourceManager(const ResourceManager& other) 
        : ptr(other.ptr ? new Resource(*other.ptr) : nullptr) {}

    // Оператор присваивания копированием
    ResourceManager& operator=(const ResourceManager& other) {
        if (this != &other) {
            auto temp = other.ptr ? new Resource(*other.ptr) : nullptr;
            delete ptr;
            ptr = temp;
        }
        return *this;
    }

    // Конструктор перемещения
    ResourceManager(ResourceManager&& other) noexcept
        : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    // Оператор присваивания перемещением
    ResourceManager& operator=(ResourceManager&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
};
```

#### Rule of Zero
Альтернативный подход: делегировать управление ресурсами RAII-классам:
```cpp
class BetterManager {
    std::unique_ptr<Resource> ptr;  // RAII-обертка
public:
    // Все специальные функции генерируются автоматически
    ~BetterManager() = default;
    BetterManager(const BetterManager&) = default;
    BetterManager(BetterManager&&) noexcept = default;
    BetterManager& operator=(const BetterManager&) = default;
    BetterManager& operator=(BetterManager&&) noexcept = default;
};
```

#### Важные моменты
- Если нужна хотя бы одна из пяти функций - реализуй все пять
- Move операции всегда должны быть noexcept
- Деструкторы по умолчанию noexcept
- Rule of Zero предпочтительнее, где возможно
- Виртуальный деструктор для базовых классов
- Self-assignment проверка в операторах присваивания

### Move Semantics
Оптимизационный механизм C++11, позволяющий передавать ресурсы между объектами без копирования.

#### Основные концепции
- **Move**: передача владения ресурсами
- **Shallow copy**: копирование указателей вместо данных
- **Resource stealing**: "кража" ресурсов у источника
- **Source invalidation**: перевод источника в валидное пустое состояние

#### Механизмы работы
1. **std::move**:
   ```cpp
   std::string str1 = "hello";
   std::string str2 = std::move(str1);  // str1 теперь пустая
   ```

2. **Move конструктор**:
   ```cpp
   class Buffer {
       char* data;
   public:
       Buffer(Buffer&& other) noexcept 
           : data(other.data) {
           other.data = nullptr;  // источник обнуляется
       }
   };
   ```

3. **Move assignment**:
   ```cpp
   Buffer& operator=(Buffer&& other) noexcept {
       if (this != &other) {
           delete[] data;         // освобождаем старые ресурсы
           data = other.data;     // забираем новые
           other.data = nullptr;  // обнуляем источник
       }
       return *this;
   }
   ```

#### Применение
1. **Возврат из функции**:
   ```cpp
   std::vector<int> createLarge() {
       std::vector<int> result(10000);
       return result;  // move автоматически
   }
   ```

2. **Вставка в контейнер**:
   ```cpp
   std::vector<std::string> vec;
   std::string str = "hello";
   vec.push_back(std::move(str));  // move вместо копии
   ```

3. **Инициализация полей**:
   ```cpp
   class Wrapper {
       std::unique_ptr<Resource> ptr;
   public:
       Wrapper(Resource&& res)
           : ptr(std::make_unique<Resource>(std::move(res))) {}
   };
   ```

#### Оптимизации компилятора
1. **Return Value Optimization (RVO)**:
   ```cpp
   BigObject createObj() {
       return BigObject();  // копирования нет
   }
   ```

2. **Named Return Value Optimization (NRVO)**:
   ```cpp
   BigObject createObj() {
       BigObject obj;
       // ... работа с obj
       return obj;  // обычно оптимизируется
   }
   ```

#### Важные моменты
- Move операции должны быть noexcept
- После move объект остается в валидном состоянии
- std::move сам по себе ничего не перемещает
- Не использовать объект после move
- STL контейнеры поддерживают move семантику
- Move семантика работает только с r-value

### Forward Reference
Механизм для идеальной передачи аргументов с сохранением их типа и категории значения.

#### Основные концепции
- **Universal reference**: `T&&` в контексте шаблонов
- **Perfect forwarding**: передача с сохранением всех свойств
- **Type deduction**: вывод типа и категории значения
- **Reference collapsing**: правила схлопывания ссылок

#### Механизм работы
1. **Universal References**:
   ```cpp
   template<typename T>
   void f(T&& x) {  // universal reference
       // x может быть и l-value и r-value
   }

   void g(int&& x) {  // НЕ universal reference
       // только r-value
   }
   ```

2. **std::forward**:
   ```cpp
   template<typename T>
   void wrapper(T&& arg) {
       process(std::forward<T>(arg));  // сохраняет категорию
   }
   ```

#### Правила схлопывания ссылок
```cpp
using LRef = int&;
using RRef = int&&;

LRef&  -> int&   // & + & = &
LRef&& -> int&   // & + && = &
RRef&  -> int&   // && + & = &
RRef&& -> int&&  // && + && = &&
```

#### Практическое применение
1. **Идеальная передача в конструктор**:
   ```cpp
   template<typename T>
   class Wrapper {
       T value;
   public:
       template<typename U>
       Wrapper(U&& val) : value(std::forward<U>(val)) {}
   };
   ```

2. **Factory функции**:
   ```cpp
   template<typename T, typename... Args>
   std::unique_ptr<T> make_unique(Args&&... args) {
       return std::unique_ptr<T>(
           new T(std::forward<Args>(args)...)
       );
   }
   ```

3. **Обертки функций**:
   ```cpp
   template<typename F, typename... Args>
   auto timing_wrapper(F&& f, Args&&... args) {
       auto start = std::chrono::steady_clock::now();
       auto result = std::forward<F>(f)(
           std::forward<Args>(args)...
       );
       auto end = std::chrono::steady_clock::now();
       return result;
   }
   ```

#### Подводные камни
1. **Проблемы с перегрузкой**:
   ```cpp
   template<typename T>
   void process(T&& x) { /* ... */ }
   
   void process(int x) { /* ... */ }
   
   process(42);  // какая версия вызовется?
   ```

2. **Множественные forwarding**:
   ```cpp
   // Плохо: лишний forward
   template<typename T>
   void bad(T&& x) {
       helper1(std::forward<T>(x));
       helper2(std::forward<T>(x));  // x может быть уже перемещен
   }
   ```

#### Важные моменты
- Universal reference только в контексте вывода типа
- std::forward требует явного указания типа
- Не forwarding один аргумент несколько раз
- Помнить о правилах схлопывания ссылок
- Проблемы с перегрузкой функций
- Не использовать std::forward для не-universal ссылок

### Константность
Система типобезопасности C++, обеспечивающая защиту от нежелательных модификаций данных.

#### Основные виды константности
1. **Константные объекты**:
   ```cpp
   const int x = 42;        // неизменяемое значение
   const std::string s = "hello";  // неизменяемый объект
   ```

2. **Константные указатели**:
   ```cpp
   const int* p1;     // указатель на константу
   int* const p2 = &x;     // константный указатель
   const int* const p3;    // константный указатель на константу
   ```

3. **Константные ссылки**:
   ```cpp
   const int& ref = x;     // ссылка на константу
   int const& ref2 = x;    // альтернативный синтаксис
   ```

#### Константные методы
```cpp
class Counter {
    int count = 0;
    mutable int access_count = 0;  // можно менять в const методах
public:
    int getValue() const {  // метод не меняет объект
        access_count++;     // разрешено благодаря mutable
        return count;
    }
    
    void increment() {      // не const - меняет объект
        count++;
    }
};
```

#### Логическая vs Битовая константность
```cpp
class LogicalConst {
    int* ptr;
public:
    int* getData() const {  // битовая константность
        return ptr;         // но не логическая!
    }
};

class BetterConst {
    int* ptr;
public:
    const int* getData() const {  // и битовая и логическая
        return ptr;
    }
};
```

#### Работа с константностью
1. **const_cast** (использовать с осторожностью):
   ```cpp
   const int constant = 21;
   const_cast<int&>(constant) = 42;  // UB!

   int regular = 21;
   const int& ref = regular;
   const_cast<int&>(ref) = 42;      // OK
   ```

2. **mutable** для логической константности:
   ```cpp
   class Cache {
       mutable std::mutex mtx;
       mutable std::map<int, int> cache;
   public:
       int compute(int x) const {
           std::lock_guard lock(mtx);  // OK благодаря mutable
           if (auto it = cache.find(x); it != cache.end())
               return it->second;
           auto result = /* тяжелые вычисления */;
           cache[x] = result;  // OK благодаря mutable
           return result;
       }
   };
   ```

#### Лучшие практики
1. **Const by default**:
   ```cpp
   // Хорошо
   void process(const std::string& s);
   
   // Плохо (если не планируем менять)
   void process(std::string& s);
   ```

2. **Const методы для чтения**:
   ```cpp
   class Good {
   public:
       int getValue() const;     // правильно
       const std::string& getName() const;  // правильно
   };
   ```

#### Важные моменты
- Константность по умолчанию (const by default)
- const методы могут вызывать только const методы
- mutable для логической константности
- Избегать const_cast
- Константные ссылки для параметров
- Возврат по константной ссылке для оптимизации
- Логическая константность важнее битовой

### Exception Safety
Механизмы обеспечения корректной работы программы при возникновении исключений.

#### Уровни гарантий
1. **Basic guarantee**:
   - Инварианты класса сохраняются
   - Нет утечек ресурсов
   - Состояние объекта может измениться
   ```cpp
   class BasicSafe {
       std::string str;
       std::vector<int> vec;
   public:
       void modify() {  // basic guarantee
           str += "hello";     // может бросить
           vec.push_back(42);  // может бросить
           // если исключение - объект изменен частично
       }
   };
   ```

2. **Strong guarantee**:
   - Транзакционная семантика
   - Либо операция успешна, либо состояние не меняется
   ```cpp
   class StrongSafe {
       std::string str;
       std::vector<int> vec;
   public:
       void modify() {  // strong guarantee
           auto temp_str = str;
           temp_str += "hello";
           auto temp_vec = vec;
           temp_vec.push_back(42);
           // если исключение - оригиналы не тронуты
           str = std::move(temp_str);
           vec = std::move(temp_vec);
       }
   };
   ```

3. **No-throw guarantee**:
   - Операция всегда успешна
   - Исключения не генерируются
   ```cpp
   class NoThrowSafe {
   public:
       void swap(NoThrowSafe& other) noexcept {
           // обмен примитивными типами
           // или вызов noexcept методов
       }
       
       ~NoThrowSafe() noexcept {  // деструкторы всегда noexcept
           // cleanup
       }
   };
   ```

#### Техники обеспечения безопасности
1. **RAII**:
   ```cpp
   void safeFunction() {
       std::unique_ptr<Resource> res(new Resource());
       // даже при исключении ресурс будет освобожден
   }
   ```

2. **Copy-and-Swap**:
   ```cpp
   class Safe {
       int* data;
   public:
       void assign(const Safe& other) {
           Safe temp(other);        // копируем
           swap(temp);             // атомарно меняем
       }  // temp автоматически удаляется
   };
   ```

3. **Временные объекты**:
   ```cpp
   void modifyState() {
       auto temp = prepareNewState();  // готовим изменения
       validateState(temp);            // проверяем
       commitState(std::move(temp));   // применяем атомарно
   }
   ```

#### Исключения в конструкторах
```cpp
class SafeConstruction {
    std::unique_ptr<Resource1> r1;
    std::unique_ptr<Resource2> r2;
public:
    SafeConstruction() 
        : r1(std::make_unique<Resource1>())  // если исключение
        , r2(std::make_unique<Resource2>())  // r1 освободится
    {}
};
```

#### Важные моменты
- Деструкторы должны быть noexcept
- Move операции предпочтительно noexcept
- Использовать RAII для ресурсов
- Strong guarantee где возможно
- Basic guarantee как минимум
- Документировать гарантии безопасности
- Избегать исключений в деструкторах
- Использовать noexcept для оптимизации

### RAII (Resource Acquisition Is Initialization)
Идиома C++, обеспечивающая автоматическое управление ресурсами через время жизни объектов.

#### Основные принципы
1. **Захват ресурса**:
   - Выполняется в конструкторе
   - Должен быть безопасным к исключениям
   - Гарантирует инициализацию

2. **Использование ресурса**:
   - Только через методы класса-владельца
   - Инкапсуляция деталей управления
   - Контроль доступа

3. **Освобождение ресурса**:
   - Автоматически в деструкторе
   - Всегда выполняется при выходе из области видимости
   - Гарантированно noexcept

#### Примеры реализации
1. **Управление памятью**:
   ```cpp
   class Buffer {
       int* data;
   public:
       Buffer(size_t size) : data(new int[size]) {}
       ~Buffer() noexcept { delete[] data; }
       
       Buffer(const Buffer&) = delete;  // запрет копирования
       Buffer& operator=(const Buffer&) = delete;
       
       Buffer(Buffer&& other) noexcept  // перемещение
           : data(other.data) {
           other.data = nullptr;
       }
   };
   ```

2. **Управление файлами**:
   ```cpp
   class FileHandler {
       FILE* file;
   public:
       FileHandler(const char* filename) 
           : file(fopen(filename, "r")) {
           if (!file) throw std::runtime_error("Can't open file");
       }
       ~FileHandler() noexcept {
           if (file) fclose(file);
       }
   };
   ```

3. **Управление блокировками**:
   ```cpp
   class LockGuard {
       std::mutex& mtx;
   public:
       explicit LockGuard(std::mutex& m) : mtx(m) {
           mtx.lock();
       }
       ~LockGuard() noexcept {
           mtx.unlock();
       }
   };
   ```

#### Стандартные RAII классы
1. **Smart Pointers**:
   ```cpp
   std::unique_ptr<Resource> ptr(new Resource());
   std::shared_ptr<Resource> shared = std::make_shared<Resource>();
   ```

2. **Контейнеры**:
   ```cpp
   std::vector<int> vec;  // автоматическое управление памятью
   std::string str;       // автоматическое управление буфером
   ```

3. **Блокировки**:
   ```cpp
   std::lock_guard<std::mutex> lock(mtx);
   std::unique_lock<std::mutex> ulock(mtx);
   ```

#### Лучшие практики
1. **Один ресурс - один класс**:
   ```cpp
   // Плохо: управление несколькими ресурсами
   class BadManager {
       File* file;
       Database* db;
       Network* net;
   };

   // Хорошо: отдельные классы
   class FileManager { File* file; };
   class DBManager { Database* db; };
   class NetManager { Network* net; };
   ```

2. **Использование существующих RAII классов**:
   ```cpp
   // Плохо
   class Bad {
       Resource* ptr = new Resource();
       ~Bad() { delete ptr; }
   };

   // Хорошо
   class Good {
       std::unique_ptr<Resource> ptr;
   };
   ```

#### Важные моменты
- Деструкторы всегда noexcept
- Избегать сырых указателей
- Использовать smart pointers
- Один класс - один ресурс
- Запрещать копирование если нужно
- Обеспечивать безопасность исключений
- Следовать принципу единственной ответственности
- Предпочитать стандартные RAII классы

### Работа с сырой памятью
Низкоуровневые механизмы для прямого управления памятью и объектами.

#### Выделение памяти
1. **Операторы new/delete**:
   ```cpp
   // Выделение одиночного объекта
   int* p1 = new int(42);
   delete p1;

   // Выделение массива
   int* p2 = new int[10];
   delete[] p2;
   ```

2. **Placement new**:
   ```cpp
   char buffer[sizeof(MyClass)];
   MyClass* obj = new (buffer) MyClass();  // конструирование в буфере
   obj->~MyClass();  // явный вызов деструктора
   ```

#### Uninitialized память
1. **Базовые операции**:
   ```cpp
   // Выделение без инициализации
   void* raw = ::operator new(sizeof(int) * n);
   
   // Конструирование объектов
   int* p = static_cast<int*>(raw);
   std::uninitialized_fill_n(p, n, 42);
   
   // Уничтожение объектов
   std::destroy_n(p, n);
   ::operator delete(raw);
   ```

2. **Алгоритмы для uninitialized памяти**:
   ```cpp
   std::vector<char> buffer(sizeof(std::string) * 3);
   std::string* strings = reinterpret_cast<std::string*>(buffer.data());

   // Копирование в uninitialized память
   const std::string src[] = {"one", "two", "three"};
   std::uninitialized_copy_n(src, 3, strings);

   // Перемещение в uninitialized память
   std::uninitialized_move_n(src, 3, strings);

   // Заполнение значением
   std::uninitialized_fill_n(strings, 3, "default");

   // Уничтожение объектов
   std::destroy(strings, strings + 3);
   ```

#### Выравнивание памяти
```cpp
// Проверка выравнивания
alignof(std::max_align_t);  // максимальное выравнивание
alignof(int);              // выравнивание типа

// Выровненное выделение
void* aligned = std::aligned_alloc(alignof(int), sizeof(int));
std::free(aligned);

// alignas спецификатор
struct alignas(32) AlignedStruct {
    int x;
    char c;
};
```

#### Работа с POD типами
```cpp
struct POD {
    int x;
    char c;
};

// Прямое копирование памяти
POD src = {42, 'A'};
POD dst;
std::memcpy(&dst, &src, sizeof(POD));

// Установка байтов
std::memset(&dst, 0, sizeof(POD));
```

#### Продвинутые техники
1. **Small Object Optimization**:
   ```cpp
   class SmallString {
       static constexpr size_t SMALL_SIZE = 16;
       union {
           char small[SMALL_SIZE];
           char* large;
       };
       size_t size;
       bool is_small;
   public:
       // ... методы для работы с разными буферами
   };
   ```

2. **Кастомные аллокаторы**:
   ```cpp
   template<typename T>
   class StackAllocator {
       char buffer[1024];
       char* ptr;
   public:
       T* allocate(size_t n) {
           // выделение из буфера
           return reinterpret_cast<T*>(ptr);
       }
       void deallocate(T* p, size_t n) {
           // возврат в пул
       }
   };
   ```

#### Важные моменты
- Избегать прямой работы с сырой памятью
- Использовать RAII и умные указатели
- Помнить о выравнивании
- Правильно парное использование new/delete
- Осторожно с placement new
- Всегда проверять выделение памяти
- Использовать std::unique_ptr для сырых ресурсов
- POD типы можно копировать memcpy
- Не забывать про исключения при конструировании

### Полиморфизм
Механизм работы с объектами разных типов через общий интерфейс:
- **Статический**: на этапе компиляции (перегрузка функций, шаблоны)
- **Динамический**: на этапе выполнения (виртуальные функции)
- **Ad-hoc**: специализация поведения (перегрузка операторов)
- **Параметрический**: обобщенное программирование (шаблоны)

#### Виртуальные функции
- Ключевое слово `virtual`
- Таблица виртуальных функций (vtable)
- Динамическая диспетчеризация
- Чисто виртуальные функции: `virtual void foo() = 0;`
- Виртуальный деструктор для базовых классов

#### Правила и практики
✅ Виртуальный деструктор в базовом классе  
❌ Виртуальный конструктор (невозможен)  

✅ Override для переопределения  
❌ Неявное переопределение  

✅ Final где нужно запретить наследование  
❌ Глубокая иерархия наследования  

#### Раннее и позднее связывание

```cpp
// Раннее связывание (на этапе компиляции)
class Early {
public:
    void process() { std::cout << "Early binding\n"; }
};

void useEarly(Early& e) {
    e.process();  // компилятор знает какой метод вызвать
}

// Позднее связывание (на этапе выполнения)
class Late {
public:
    virtual void process() { std::cout << "Base\n"; }
};

class Derived : public Late {
public:
    void process() override { std::cout << "Derived\n"; }
};

void useLate(Late& l) {
    l.process();  // решается в runtime через vtable
}

int main() {
    Derived d;
    Late& l = d;
    l.process();  // выведет "Derived"
}
```

## Хорошие и плохие практики

### L/R-value
✅ `void process(const T& lval)` - для l-value  
❌ `void process(T& val)` - без const для чтения  

✅ `void process(T&& rval)` - для r-value  
❌ `void process(const T&& rval)` - const для r-value бессмысленен  

### Variadic Templates
✅ `template<typename... Args> void forward(Args&&... args)`  
❌ `template<typename... Args> void forward(Args... args)` - теряем категорию значения  

### Rule of Five
✅ Объявить все 5 или ни одного (Rule of Zero)  
❌ Объявить только часть специальных функций-членов  

### Move Semantics
✅ `v2 = std::move(v1)` - явное перемещение  
❌ `v2 = std::forward<T>(v1)` - forward для move  

### Forward Reference
✅ `template<typename T> void wrapper(T&& arg)`  
❌ `void wrapper(T&& arg)` - без template не universal reference  

### Константность
✅ `void process(const T& data) const`  
❌ `void process(T& data)` - изменяемость без необходимости  

## Частые ошибки

### Утечки и Dangling
- Забытый delete в исключении
- Dangling reference после move
- Raw pointer без ownership семантики
- Циклические shared_ptr

### Неопределённое поведение
- Move из const объекта
- Использование после move
- Неинициализированные переменные
- Выход за границы массива

### Exception Safety
- Исключения в деструкторах
- Нарушение strong guarantee
- Утечки в конструкторах
- Отсутствие noexcept для move

### RAII
- Ручное управление ресурсами
- Множественная ответственность
- Неявные зависимости
- Смешивание raw и smart pointers

## Примеры кода

### Move Semantics и Rule of Five
```cpp
// Плохо: только часть special members
class Bad {
    std::string* data;
public:
    Bad(const Bad& other) { data = new std::string(*other.data); }
    ~Bad() { delete data; }
    // Забыли move и assignment операторы - утечки!
};

// Хорошо: RAII и Rule of Five
class Good {
    std::unique_ptr<std::string> data;
public:
    Good(const Good& other) : data(std::make_unique<std::string>(*other.data)) {}
    Good(Good&& other) noexcept = default;
    Good& operator=(const Good& other) {
        if (this != &other) data = std::make_unique<std::string>(*other.data);
        return *this;
    }
    Good& operator=(Good&& other) noexcept = default;
    ~Good() = default;
};
```

### Variadic Templates и Perfect Forwarding
```cpp
// Плохо: теряем категорию значения
template<typename... Args>
void badForward(Args... args) {
    process(args...);  // L-value всегда!
}

// Хорошо: perfect forwarding
template<typename... Args>
void goodForward(Args&&... args) {
    process(std::forward<Args>(args)...);
}
```

### RAII и Exception Safety
```cpp
// Плохо: ручное управление ресурсами
void badFunction() {
    auto* p = new Resource();
    try {
        process(p);
    } catch (...) {
        delete p;  // легко забыть
        throw;
    }
    delete p;
}

// Хорошо: RAII
void goodFunction() {
    auto p = std::make_unique<Resource>();
    process(p.get());  // автоматическая очистка
}
```

### Константность и References
```cpp
// Плохо: избыточная изменяемость
void badConst(std::string& s) {
    std::cout << s;  // для чтения нужен const
}

// Хорошо: const для read-only
void goodConst(const std::string& s) {
    std::cout << s;
}

// Хорошо: r-value reference для перемещения
void moveStr(std::string&& s) {
    strings_.push_back(std::move(s));
}
```

### Циклические зависимости и shared_ptr
```cpp
// Плохо: циклическая зависимость
struct BadNode {
    std::shared_ptr<BadNode> next;
    std::shared_ptr<BadNode> prev;  // утечка!
};

// Хорошо: weak_ptr для обратных ссылок
struct GoodNode {
    std::shared_ptr<GoodNode> next;
    std::weak_ptr<GoodNode> prev;  // нет цикла
};
```

### Dangling References
```cpp
// Плохо: dangling после move
std::string& badRef(std::string& s1, std::string& s2) {
    s1 = std::move(s2);
    return s2;  // s2 в неопределенном состоянии!
}

// Хорошо: возврат по значению
std::string goodMove(std::string& s1, std::string& s2) {
    std::string old = std::move(s2);
    s1 = std::move(s2);
    return old;
}
```

### Exception Safety в Конструкторах
```cpp
// Плохо: возможна утечка
class BadClass {
    Resource* r1;
    Resource* r2;
public:
    BadClass() {
        r1 = new Resource();  // если тут исключение
        r2 = new Resource();  // r1 утечет
    }
};

// Хорошо: RAII члены
class GoodClass {
    std::unique_ptr<Resource> r1;
    std::unique_ptr<Resource> r2;
public:
    GoodClass() : 
        r1(std::make_unique<Resource>()),
        r2(std::make_unique<Resource>()) {}  // безопасно
};
```

### Universal References и Overloading
```cpp
// Плохо: universal reference перехватывает всё
template<typename T>
void bad(T&& x) { /* ... */ }
void bad(int x) { /* ... */ }  // никогда не вызовется

// Хорошо: используем enable_if
template<typename T>
std::enable_if_t<!std::is_same_v<std::decay_t<T>, int>>
good(T&& x) { /* ... */ }
void good(int x) { /* ... */ }
```

### Const Member Functions
```cpp
// Плохо: изменяемый метод без причины
class BadCounter {
    int count = 0;
public:
    int getCount() { return count; }  // почему не const?
};

// Хорошо: const везде где можно
class GoodCounter {
    int count = 0;
    mutable std::mutex mtx;  // mutable для синхронизации
public:
    int getCount() const {  // thread-safe и const-correct
        std::lock_guard lock(mtx);
        return count;
    }
};
```

### Битовые поля и упаковка данных
Механизмы для эффективного хранения и управления данными на уровне битов.

#### Битовые поля
1. **Базовый синтаксис**:
   ```cpp
   struct Flags {
       uint32_t read    : 1;  // 1 бит
       uint32_t write   : 1;  // 1 бит
       uint32_t execute : 1;  // 1 бит
       uint32_t unused  : 29; // остальные биты
   };
   ```

2. **Применение с enum**:
   ```cpp
   enum class Color : uint8_t {
       Red, Green, Blue
   };

   struct Pixel {
       uint32_t alpha : 8;    // прозрачность
       Color    color : 2;    // цвет (нужно 2 бита для 3 значений)
       uint32_t bright : 3;   // яркость
   };
   ```

#### Выравнивание и упаковка
1. **Контроль выравнивания**:
   ```cpp
   // Принудительное выравнивание
   struct alignas(8) AlignedStruct {
       char c;     // 1 байт
       int32_t i;  // 4 байта
   };  // размер 8 байт

   // Упаковка без выравнивания
   #pragma pack(push, 1)
   struct PackedStruct {
       char c;     // 1 байт
       int32_t i;  // 4 байта
   };  // размер 5 байт
   #pragma pack(pop)
   ```

2. **Атрибуты упаковки**:
   ```cpp
   struct [[gnu::packed]] PackedGNU {
       char c;
       int32_t i;
   };
   ```

#### Фиксированные типы
1. **Целочисленные типы**:
   ```cpp
   #include <cstdint>
   
   uint8_t  byte;    // ровно 8 бит без знака
   int16_t  short;   // ровно 16 бит со знаком
   uint32_t uint;    // ровно 32 бита без знака
   int64_t  long;    // ровно 64 бита со знаком
   
   // Минимальные типы
   int_least8_t  min8;   // минимум 8 бит
   uint_least16_t min16; // минимум 16 бит
   
   // Быстрые типы
   int_fast32_t  fast32;  // оптимальный >= 32 бит
   uint_fast64_t fast64;  // оптимальный >= 64 бит
   ```

2. **Специальные типы**:
   ```cpp
   intptr_t  ptr;      // для хранения указателя
   uintmax_t biggest;  // максимально возможный
   ```

#### Оптимизация размера
1. **Порядок полей**:
   ```cpp
   // Плохо: много паддинга
   struct BadLayout {
       char a;      // 1 байт + 3 паддинг
       int32_t b;   // 4 байта
       char c;      // 1 байт + 3 паддинг
   };  // всего 12 байт

   // Хорошо: минимум паддинга
   struct GoodLayout {
       int32_t b;   // 4 байта
       char a;      // 1 байт
       char c;      // 1 байт + 2 паддинг
   };  // всего 8 байт
   ```

2. **Использование union**:
   ```cpp
   union DataUnion {
       struct {
           uint32_t flag1 : 1;
           uint32_t flag2 : 1;
       } flags;
       uint32_t raw;  // прямой доступ ко всем битам
   };
   ```

#### Работа с битовыми полями
1. **Операции**:
   ```cpp
   struct Control {
       uint16_t enabled : 1;
       uint16_t ready   : 1;
       uint16_t mode    : 2;
   };

   Control ctrl{};
   ctrl.enabled = true;
   ctrl.mode = 2;
   
   // Атомарные операции
   std::atomic<Control> atomic_ctrl;
   Control old = atomic_ctrl.load(std::memory_order_relaxed);
   ```

2. **Битовые маски**:
   ```cpp
   struct Permissions {
       static constexpr uint32_t Read    = 0b001;
       static constexpr uint32_t Write   = 0b010;
       static constexpr uint32_t Execute = 0b100;
       
       uint32_t flags : 3;
       
       bool canRead() const { return flags & Read; }
       void setWrite(bool enable) {
           flags = enable ? (flags | Write) : (flags & ~Write);
       }
   };
   ```

#### Важные моменты
- Порядок битов зависит от платформы
- Битовые поля не имеют адреса
- Возможны проблемы с выравниванием при packed структурах
- Атомарные операции могут быть медленнее для packed структур
- Размер структуры может быть больше суммы размеров полей
- Фиксированные типы гарантируют размер на всех платформах
- Выравнивание влияет на производительность
- Packed структуры могут замедлить доступ к данным