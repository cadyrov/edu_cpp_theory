# Тестовые вопросы по RAII

1. Что означает аббревиатура RAII?
   - A) Resource Allocation Is Initialization
   - B) Resource Acquisition Is Initialization
   - C) Resource Access Is Implementation
   - D) Resource Allocation In Implementation

2. Какой код корректно реализует RAII для файлового дескриптора?
```cpp
// Вариант A
class FileWrapper {
    FILE* file_;
public:
    FileWrapper(const char* name) : file_(fopen(name, "r")) {}
    ~FileWrapper() { fclose(file_); }
};

// Вариант B
class FileWrapper {
    FILE* file_;
public:
    FileWrapper(const char* name) : file_(fopen(name, "r")) {}
    ~FileWrapper() { if(file_) fclose(file_); }
    FileWrapper(const FileWrapper&) = delete;
    FileWrapper& operator=(const FileWrapper&) = delete;
};

// Вариант C
class FileWrapper {
    FILE* file_;
public:
    FileWrapper(const char* name) { file_ = fopen(name, "r"); }
    void close() { fclose(file_); }
};

// Вариант D
struct FileWrapper {
    FILE* file_;
    FileWrapper(const char* name) { file_ = fopen(name, "r"); }
    ~FileWrapper() { if(file_) fclose(file_); }
    FileWrapper(const FileWrapper& other) : file_(other.file_) {}
};
```

3. В каком порядке будут вызваны деструкторы для следующего кода?
```cpp
class A {
public:
    ~A() { std::cout << "A"; }
};
class B {
public:
    ~B() { std::cout << "B"; }
};
int main() {
    A a1;
    B b;
    A a2;
}
```
   - A) ABA
   - B) AAB
   - C) BAA
   - D) ABB

4. Что произойдет при выполнении следующего кода?
```cpp
class Resource {
public:
    ~Resource() { throw std::runtime_error("Error"); }
};
int main() {
    try {
        Resource r;
    } catch(...) {
        std::cout << "Caught";
    }
}
```
   - A) Выведет "Caught"
   - B) Программа завершится с std::terminate
   - C) Ничего не произойдет
   - D) Будет утечка памяти

5. Какой из следующих классов STL НЕ использует RAII?
   - A) std::vector
   - B) std::array
   - C) std::string
   - D) std::map

6. Как правильно использовать std::unique_ptr в функции?
```cpp
// Вариант A
std::unique_ptr<Resource> createResource() {
    return std::unique_ptr<Resource>(new Resource());
}

// Вариант B
std::unique_ptr<Resource> createResource() {
    return std::make_unique<Resource>();
}

// Вариант C
Resource* createResource() {
    return new Resource();
}

// Вариант D
std::unique_ptr<Resource> createResource() {
    auto ptr = new Resource();
    return std::unique_ptr<Resource>(ptr);
}
```

7. Что произойдет при следующем использовании std::lock_guard?
```cpp
std::mutex mtx;
void function() {
    std::lock_guard<std::mutex> lock(mtx);
    throw std::runtime_error("Error");
}
```
   - A) Мьютекс останется заблокированным
   - B) Мьютекс будет автоматически разблокирован
   - C) Программа завершится с ошибкой сегментации
   - D) Произойдет утечка ресурсов

8. Какой из следующих способов управления ресурсами является наиболее безопасным?
```cpp
// Вариант A
void process() {
    auto ptr = new int[1000];
    try {
        // работа с данными
        delete[] ptr;
    } catch(...) {
        delete[] ptr;
        throw;
    }
}

// Вариант B
void process() {
    std::vector<int> data(1000);
    // работа с данными
}

// Вариант C
void process() {
    int* ptr = new int[1000];
    // работа с данными
    delete[] ptr;
}

// Вариант D
void process() {
    std::unique_ptr<int[]> ptr(new int[1000]);
    // работа с данными
}
```

9. Что неправильно в этом RAII-классе?
```cpp
class ConnectionManager {
    Connection* conn_;
public:
    ConnectionManager() : conn_(nullptr) {}
    void connect() { conn_ = new Connection(); }
    ~ConnectionManager() { delete conn_; }
};
```
   - A) Отсутствует обработка исключений
   - B) Не реализовано правило пяти
   - C) Ресурс выделяется не в конструкторе
   - D) Все вышеперечисленное

10. Какой из следующих умных указателей следует использовать для циклических структур данных?
    - A) std::unique_ptr
    - B) std::shared_ptr
    - C) std::weak_ptr
    - D) std::auto_ptr

11. В каком случае может произойти утечка ресурсов при использовании RAII?
```cpp
// Вариант A
class Resource {
    int* data_;
public:
    Resource() : data_(new int[100]) {}
    ~Resource() { delete[] data_; }
};

// Вариант B
class Resource {
    int* data_;
public:
    Resource() : data_(new int[100]) {}
    ~Resource() { delete[] data_; }
    Resource(const Resource& other) : data_(new int[100]) {
        std::copy(other.data_, other.data_ + 100, data_);
    }
};

// Вариант C
class Resource {
    std::unique_ptr<int[]> data_;
public:
    Resource() : data_(std::make_unique<int[]>(100)) {}
};

// Вариант D
class Resource {
    std::vector<int> data_;
public:
    Resource() : data_(100) {}
};
```

12. Какой порядок инициализации и уничтожения будет у полей в следующем классе?
```cpp
class Complex {
    Logger logger_;
    Database db_;
    Network net_;
public:
    Complex() = default;
    ~Complex() = default;
};
```
   - A) Инициализация: logger_, db_, net_; Уничтожение: net_, db_, logger_
   - B) Инициализация: net_, db_, logger_; Уничтожение: logger_, db_, net_
   - C) Порядок может быть любым
   - D) Зависит от компилятора

13. Что произойдет при копировании объекта следующего класса?
```cpp
class Handler {
    Resource* res_;
public:
    Handler(Resource* r) : res_(r) {}
    ~Handler() { delete res_; }
};
```
   - A) Копирование будет запрещено компилятором
   - B) Произойдет двойное удаление
   - C) Скомпилируется, но может привести к неопределенному поведению
   - D) Все будет работать корректно

14. Какой из следующих способов освобождения ресурсов является наиболее надежным?
```cpp
// Вариант A
void cleanup() {
    try {
        resource->release();
    } catch(...) {
        // игнорируем ошибки
    }
}

// Вариант B
void cleanup() noexcept {
    try {
        resource->release();
    } catch(...) {
        std::terminate();
    }
}

// Вариант C
void cleanup() {
    resource->release();
}

// Вариант D
void cleanup() noexcept {
    try {
        resource->release();
    } catch(...) {
        // логируем ошибку
    }
}
```

15. Какой из следующих классов правильно реализует RAII для управления мьютексом?
```cpp
// Вариант A
class LockManager {
    std::mutex& mtx_;
public:
    LockManager(std::mutex& m) : mtx_(m) { mtx_.lock(); }
    ~LockManager() { mtx_.unlock(); }
};

// Вариант B
class LockManager {
    std::mutex& mtx_;
public:
    LockManager(std::mutex& m) : mtx_(m) { mtx_.lock(); }
    ~LockManager() { mtx_.unlock(); }
    LockManager(const LockManager&) = delete;
    LockManager& operator=(const LockManager&) = delete;
};

// Вариант C
class LockManager {
    std::mutex& mtx_;
public:
    LockManager(std::mutex& m) : mtx_(m) {}
    void lock() { mtx_.lock(); }
    void unlock() { mtx_.unlock(); }
    ~LockManager() = default;
};

// Вариант D
class LockManager {
    std::mutex mtx_;
public:
    LockManager() { mtx_.lock(); }
    ~LockManager() { mtx_.unlock(); }
};
```

16. Что произойдет при выполнении следующего кода?
```cpp
class Resource {
public:
    Resource() { throw std::runtime_error("Error"); }
    ~Resource() { std::cout << "Destroyed"; }
};

int main() {
    try {
        Resource r;
    } catch(...) {
        std::cout << "Caught";
    }
}
```
   - A) Выведет "Destroyed Caught"
   - B) Выведет "Caught"
   - C) Выведет "Destroyed"
   - D) Программа завершится аварийно

17. Какой из следующих способов передачи владения ресурсом является правильным?
```cpp
// Вариант A
std::unique_ptr<Resource> getResource() {
    auto ptr = std::make_unique<Resource>();
    return ptr;
}

// Вариант B
Resource* getResource() {
    return new Resource();
}

// Вариант C
std::shared_ptr<Resource> getResource() {
    return std::shared_ptr<Resource>(new Resource());
}

// Вариант D
std::unique_ptr<Resource> getResource() {
    Resource* ptr = new Resource();
    return std::unique_ptr<Resource>(ptr);
}
```

18. Какие проблемы могут возникнуть при использовании следующего кода?
```cpp
class Manager {
    std::shared_ptr<Resource> res1_;
    std::shared_ptr<Resource> res2_;
public:
    Manager() {
        res1_ = std::make_shared<Resource>();
        res2_ = std::make_shared<Resource>();
    }
};
```
   - A) Утечка памяти
   - B) Исключение в конструкторе
   - C) Проблемы с порядком инициализации
   - D) Нет проблем

19. Как правильно реализовать перемещающий конструктор для RAII-класса?
```cpp
// Вариант A
class Handler {
    Resource* res_;
public:
    Handler(Handler&& other) { 
        res_ = other.res_;
        other.res_ = nullptr;
    }
};

// Вариант B
class Handler {
    Resource* res_;
public:
    Handler(Handler&& other) noexcept
        : res_(std::exchange(other.res_, nullptr)) {}
};

// Вариант C
class Handler {
    Resource* res_;
public:
    Handler(Handler&& other) {
        std::swap(res_, other.res_);
    }
};

// Вариант D
class Handler {
    Resource* res_;
public:
    Handler(Handler&& other) noexcept {
        delete res_;
        res_ = other.res_;
        other.res_ = nullptr;
    }
};
```

20. Что неправильно в следующей реализации RAII?
```cpp
template<typename T>
class Container {
    T* data_;
    size_t size_;
public:
    Container(size_t size) : size_(size) {
        data_ = new T[size];
    }
    ~Container() {
        delete[] data_;
    }
    Container(const Container& other) : size_(other.size_) {
        data_ = new T[size_];
        std::copy(other.data_, other.data_ + size_, data_);
    }
};
```
   - A) Отсутствует оператор присваивания
   - B) Нет проверки на nullptr
   - C) Не реализован move constructor
   - D) Все вышеперечисленное

21. Какой из следующих паттернов является альтернативой RAII в других языках программирования?
    - A) try-finally
    - B) using statement
    - C) defer
    - D) Все вышеперечисленное

22. Что произойдет при следующем использовании std::shared_ptr?
```cpp
class Resource {
public:
    ~Resource() { std::cout << "Destroyed"; }
};

int main() {
    auto ptr1 = std::make_shared<Resource>();
    {
        auto ptr2 = ptr1;
        auto ptr3 = std::move(ptr1);
    }
    std::cout << (ptr1 ? "Valid" : "Invalid");
}
```
   - A) Выведет "Destroyed Valid"
   - B) Выведет "Invalid"
   - C) Выведет "Destroyed Invalid"
   - D) Выведет "Valid"

23. Какой из следующих способов инициализации является предпочтительным для RAII-класса?
```cpp
// Вариант A
class Handler {
    Resource* res_;
public:
    Handler() { res_ = new Resource(); }
};

// Вариант B
class Handler {
    Resource* res_;
public:
    Handler() : res_(new Resource()) {}
};

// Вариант C
class Handler {
    std::unique_ptr<Resource> res_;
public:
    Handler() : res_(std::make_unique<Resource>()) {}
};

// Вариант D
class Handler {
    Resource res_;
public:
    Handler() = default;
};
```

24. Что произойдет при выполнении следующего кода?
```cpp
class Base {
public:
    virtual ~Base() { throw std::runtime_error("Error"); }
};

class Derived : public Base {
public:
    ~Derived() { std::cout << "Derived"; }
};

int main() {
    try {
        Derived d;
    } catch(...) {
        std::cout << "Caught";
    }
}
```
   - A) Выведет "Derived Caught"
   - B) Программа завершится с std::terminate
   - C) Выведет "Caught"
   - D) Выведет "Derived"

25. Какой из следующих способов освобождения ресурсов является наиболее безопасным при наследовании?
```cpp
// Вариант A
class Base {
public:
    virtual ~Base() = default;
};

// Вариант B
class Base {
public:
    ~Base() {}
};

// Вариант C
class Base {
protected:
    ~Base() = default;
};

// Вариант D
class Base {
public:
    virtual void cleanup() = 0;
    ~Base() { cleanup(); }
};
```

26. Что неправильно в следующей реализации RAII для сетевого соединения?
```cpp
class Connection {
    Socket* socket_;
public:
    Connection(const std::string& address) {
        try {
            socket_ = new Socket(address);
            socket_->connect();
        } catch(...) {
            delete socket_;
            throw;
        }
    }
    ~Connection() {
        if(socket_) {
            socket_->disconnect();
            delete socket_;
        }
    }
};
```
   - A) Отсутствует инициализация socket_ в nullptr
   - B) Не реализовано правило пяти
   - C) Неправильная обработка исключений
   - D) Все вышеперечисленное

27. Какой из следующих способов является правильным для предотвращения исключений в деструкторе?
```cpp
// Вариант A
~Resource() {
    try {
        cleanup();
    } catch(...) {}
}

// Вариант B
~Resource() noexcept {
    try {
        cleanup();
    } catch(...) {
        std::abort();
    }
}

// Вариант C
~Resource() noexcept {
    try {
        cleanup();
    } catch(...) {
        // log error
    }
}

// Вариант D
~Resource() {
    cleanup(); // throws
}
```

28. Что произойдет при выполнении следующего кода?
```cpp
class Resource {
public:
    Resource() { throw std::runtime_error("Constructor error"); }
};

class Handler {
    Resource res_;
    int* data_;
public:
    Handler() : data_(new int[100]) {}
    ~Handler() { delete[] data_; }
};

int main() {
    try {
        Handler h;
    } catch(...) {
        std::cout << "Caught";
    }
}
```
   - A) Утечка памяти
   - B) Выведет "Caught" без утечки
   - C) Программа завершится аварийно
   - D) Деструктор Handler будет вызван

29. Какой из следующих способов является правильным для реализации копирующего присваивания в RAII-классе?
```cpp
// Вариант A
Handler& operator=(const Handler& other) {
    delete resource_;
    resource_ = new Resource(*other.resource_);
    return *this;
}

// Вариант B
Handler& operator=(const Handler& other) {
    if (this != &other) {
        delete resource_;
        resource_ = new Resource(*other.resource_);
    }
    return *this;
}

// Вариант C
Handler& operator=(const Handler& other) {
    auto temp = new Resource(*other.resource_);
    delete resource_;
    resource_ = temp;
    return *this;
}

// Вариант D
Handler& operator=(const Handler& other) {
    Resource* temp = resource_;
    resource_ = new Resource(*other.resource_);
    delete temp;
    return *this;
}
```

30. Что произойдет при использовании следующего кода?
```cpp
class Resource {
public:
    Resource() { throw std::runtime_error("Error"); }
};

class Handler {
    std::unique_ptr<Resource> ptr1_;
    std::unique_ptr<Resource> ptr2_;
public:
    Handler() : ptr1_(std::make_unique<Resource>()),
                ptr2_(std::make_unique<Resource>()) {}
};

int main() {
    try {
        Handler h;
    } catch(...) {
        std::cout << "Caught";
    }
}
```
   - A) Утечка памяти
   - B) Выведет "Caught" без утечки
   - C) Программа завершится аварийно
   - D) Оба указателя будут корректно освобождены

31. Какой из следующих способов является правильным для реализации перемещающего присваивания?
```cpp
// Вариант A
Handler& operator=(Handler&& other) {
    resource_ = other.resource_;
    other.resource_ = nullptr;
    return *this;
}

// Вариант B
Handler& operator=(Handler&& other) noexcept {
    if (this != &other) {
        delete resource_;
        resource_ = other.resource_;
        other.resource_ = nullptr;
    }
    return *this;
}

// Вариант C
Handler& operator=(Handler&& other) {
    std::swap(resource_, other.resource_);
    return *this;
}

// Вариант D
Handler& operator=(Handler&& other) noexcept {
    resource_ = std::exchange(other.resource_, nullptr);
    return *this;
}
```

32. Что неправильно в следующей реализации RAII для файлового потока?
```cpp
class FileHandler {
    std::ofstream file_;
public:
    FileHandler(const std::string& filename) {
        file_.open(filename);
    }
    ~FileHandler() {
        if(file_.is_open()) {
            file_.close();
        }
    }
};
```
   - A) Нет проверки успешности открытия файла
   - B) Не реализовано правило пяти
   - C) Избыточная проверка в деструкторе
   - D) Все правильно

33. Какой из следующих способов является наиболее безопасным для работы с несколькими мьютексами?
```cpp
// Вариант A
void process() {
    std::lock_guard<std::mutex> lock1(mutex1);
    std::lock_guard<std::mutex> lock2(mutex2);
}

// Вариант B
void process() {
    std::scoped_lock lock(mutex1, mutex2);
}

// Вариант C
void process() {
    mutex1.lock();
    mutex2.lock();
    // ... work ...
    mutex2.unlock();
    mutex1.unlock();
}

// Вариант D
void process() {
    std::unique_lock<std::mutex> lock1(mutex1);
    std::unique_lock<std::mutex> lock2(mutex2);
}
```

34. Что произойдет при выполнении следующего кода?
```cpp
class Resource {
public:
    ~Resource() { throw std::runtime_error("Error in destructor"); }
};

class Handler {
    Resource res1_;
    Resource res2_;
public:
    ~Handler() noexcept {
        try {
            // cleanup
        } catch(...) {}
    }
};

int main() {
    Handler h;
}
```
   - A) Программа завершится нормально
   - B) Программа завершится с std::terminate
   - C) Будет утечка ресурсов
   - D) Исключения будут проигнорированы

35. Какой из следующих способов является правильным для реализации RAII с условной инициализацией ресурса?
```cpp
// Вариант A
class Handler {
    Resource* res_ = nullptr;
public:
    Handler(bool init) {
        if(init) {
            res_ = new Resource();
        }
    }
    ~Handler() { delete res_; }
};

// Вариант B
class Handler {
    std::unique_ptr<Resource> res_;
public:
    Handler(bool init) {
        if(init) {
            res_ = std::make_unique<Resource>();
        }
    }
};

// Вариант C
class Handler {
    std::optional<Resource> res_;
public:
    Handler(bool init) {
        if(init) {
            res_.emplace();
        }
    }
};

// Вариант D
class Handler {
    Resource* res_;
public:
    Handler(bool init) : res_(init ? new Resource() : nullptr) {}
    ~Handler() { delete res_; }
};
```

36. Что произойдет при следующем использовании std::shared_ptr?
```cpp
class Resource {
public:
    ~Resource() { std::cout << "Destroyed"; }
};

int main() {
    std::weak_ptr<Resource> weak;
    {
        auto shared = std::make_shared<Resource>();
        weak = shared;
    }
    if(auto locked = weak.lock()) {
        std::cout << "Valid";
    } else {
        std::cout << "Invalid";
    }
}
```
   - A) Выведет "Destroyed Valid"
   - B) Выведет "Destroyed Invalid"
   - C) Выведет "Valid Destroyed"
   - D) Выведет "Invalid"

37. Какой из следующих способов является правильным для реализации RAII с несколькими ресурсами?
```cpp
// Вариант A
class Handler {
    Resource1* res1_;
    Resource2* res2_;
public:
    Handler() {
        try {
            res1_ = new Resource1();
            res2_ = new Resource2();
        } catch(...) {
            delete res1_;
            throw;
        }
    }
    ~Handler() {
        delete res2_;
        delete res1_;
    }
};

// Вариант B
class Handler {
    std::unique_ptr<Resource1> res1_;
    std::unique_ptr<Resource2> res2_;
public:
    Handler() : res1_(std::make_unique<Resource1>()),
                res2_(std::make_unique<Resource2>()) {}
};

// Вариант C
class Handler {
    Resource1 res1_;
    Resource2 res2_;
public:
    Handler() = default;
};

// Вариант D
class Handler {
    std::shared_ptr<Resource1> res1_;
    std::shared_ptr<Resource2> res2_;
public:
    Handler() {
        res1_ = std::make_shared<Resource1>();
        res2_ = std::make_shared<Resource2>();
    }
};
```

38. Что неправильно в следующей реализации RAII для базы данных?
```cpp
class DBConnection {
    Connection* conn_;
    Transaction* trans_;
public:
    DBConnection(const std::string& connection_string) {
        conn_ = new Connection(connection_string);
        try {
            trans_ = new Transaction(*conn_);
        } catch(...) {
            delete conn_;
            throw;
        }
    }
    ~DBConnection() {
        delete trans_;
        delete conn_;
    }
};
```
   - A) Отсутствует обработка исключений в деструкторе
   - B) Не реализовано правило пяти
   - C) Неправильный порядок удаления ресурсов
   - D) Все вышеперечисленное

39. Какой из следующих способов является правильным для реализации RAII с отложенной инициализацией?
```cpp
// Вариант A
class Handler {
    std::unique_ptr<Resource> res_;
public:
    void init() {
        res_ = std::make_unique<Resource>();
    }
};

// Вариант B
class Handler {
    std::unique_ptr<Resource> res_;
public:
    void init() {
        if(!res_) {
            res_ = std::make_unique<Resource>();
        }
    }
};

// Вариант C
class Handler {
    std::optional<Resource> res_;
public:
    void init() {
        if(!res_) {
            res_.emplace();
        }
    }
};

// Вариант D
class Handler {
    Resource* res_ = nullptr;
public:
    void init() {
        if(!res_) {
            res_ = new Resource();
        }
    }
    ~Handler() { delete res_; }
};
```

40. Что произойдет при выполнении следующего кода?
```cpp
class Resource {
public:
    Resource() { throw std::runtime_error("Error"); }
};

class Handler {
    std::shared_ptr<Resource> res1_;
    std::shared_ptr<Resource> res2_;
public:
    Handler() {
        res1_ = std::make_shared<Resource>();
        res2_ = std::make_shared<Resource>();
    }
};

int main() {
    try {
        Handler h;
    } catch(const std::exception& e) {
        std::cout << "Caught: " << e.what();
    }
}
```
   - A) Выведет "Caught: Error" без утечки памяти
   - B) Программа завершится аварийно
   - C) Будет утечка памяти
   - D) Деструктор Handler будет вызван 