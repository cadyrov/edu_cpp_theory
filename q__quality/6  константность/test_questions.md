# Тестовые вопросы по константности в C++

1. Что произойдет при компиляции следующего кода?
```cpp
void func(const vector<int>& vec) {
    sort(vec.begin(), vec.end());
}
```
a) Код скомпилируется успешно
b) Ошибка компиляции - нельзя сортировать константный вектор
c) Ошибка компиляции - нельзя получить итераторы от константного вектора
d) Ошибка времени выполнения

2. Какой из следующих способов объявления константного указателя на константные данные является правильным?
a) `const int* ptr;`
b) `int const* ptr;`
c) `const int* const ptr = &value;`
d) `int const* const ptr;`

3. Что выведет данный код?
```cpp
class Counter {
    mutable int count = 0;
public:
    int get() const { 
        count++;
        return count; 
    }
};

int main() {
    const Counter c;
    cout << c.get() << " " << c.get();
}
```
a) 0 0
b) 1 1
c) 1 2
d) Ошибка компиляции

4. В каком случае использование mutable является хорошей практикой?
a) Для счетчика обращений к методу
b) Для кэширования результатов вычислений
c) Для изменения бизнес-данных в константном методе
d) Для обхода ограничений константности

5. Какой код является правильным применением IILE?
```cpp
// Вариант 1
const auto value = 42;

// Вариант 2
const auto value = []{ return 42; }();

// Вариант 3
const auto value = []{
    complex_initialization();
    take_mutex();
    return expensive_calculation();
}();

// Вариант 4
const auto value = invoke([]{ return 42; });
```
a) Вариант 1
b) Вариант 2
c) Вариант 3
d) Вариант 4

[Продолжение вопросов...]

6. Что произойдет при попытке компиляции?
```cpp
class Widget {
    int value_;
public:
    void setValue(int v) const {
        value_ = v;
    }
};
```
a) Код скомпилируется успешно
b) Ошибка компиляции - нельзя модифицировать поля в const методе
c) Предупреждение компилятора
d) Неопределенное поведение

7. Как правильно объявить константный метод, возвращающий константную ссылку?
```cpp
class Container {
    vector<int> data_;
public:
    // Варианты:
    const vector<int>& getData() { return data_; }           // 1
    const vector<int>& getData() const { return data_; }     // 2
    vector<int>& getData() const { return data_; }           // 3
    const vector<int> getData() const { return data_; }      // 4
};
```
a) Вариант 1
b) Вариант 2
c) Вариант 3
d) Вариант 4

8. Какой код демонстрирует правильное использование константных итераторов?
```cpp
vector<int> vec = {1, 2, 3};
// Вариант 1
auto it = vec.cbegin();
*it = 42;

// Вариант 2
const auto it = vec.begin();
*it = 42;

// Вариант 3
const_iterator it = vec.begin();
*it = 42;

// Вариант 4
auto it = vec.cbegin();
it++;
```
a) Вариант 1
b) Вариант 2
c) Вариант 3
d) Вариант 4

[Продолжение следует...] 

9. Что произойдет при компиляции?
```cpp
class Data {
    vector<int> data_;
public:
    const vector<int>& getData() const { return data_; }
    void modify() {
        const auto& d = getData();
        d.push_back(42);
    }
};
```
a) Код скомпилируется успешно
b) Ошибка компиляции в getData()
c) Ошибка компиляции в modify()
d) Неопределенное поведение

10. Какое утверждение о логической константности верно?
a) Логическая константность запрещает любые изменения объекта
b) Логическая константность разрешает изменение только mutable полей
c) Логическая константность гарантирует неизменность наблюдаемого состояния объекта
d) Логическая константность эквивалентна физической константности

11. В каком случае использование const_cast является допустимым?
```cpp
// Вариант 1
void legacy_api(char* str);
void modern_wrapper(const char* str) {
    legacy_api(const_cast<char*>(str));
}

// Вариант 2
class Widget {
    int* ptr_;
public:
    int getValue() const {
        return *const_cast<int*>(ptr_);
    }
};

// Вариант 3
void process(const int& val) {
    int& mutable_val = const_cast<int&>(val);
    mutable_val++;
}

// Вариант 4
template<typename T>
void serialize(T& obj) {
    const T& const_obj = obj;
    T& mutable_obj = const_cast<T&>(const_obj);
    mutable_obj.prepare_for_serialization();
}
```
a) Вариант 1
b) Вариант 2
c) Вариант 3
d) Вариант 4

12. Какой код корректно использует константные методы?
```cpp
class Cache {
    map<string, string> data_;
    mutable mutex mtx_;
public:
    // Вариант 1
    string get(const string& key) {
        lock_guard<mutex> lock(mtx_);
        return data_[key];
    }

    // Вариант 2
    string get(const string& key) const {
        lock_guard<mutex> lock(mtx_);
        return data_[key];
    }

    // Вариант 3
    const string& get(const string& key) const {
        lock_guard<mutex> lock(mtx_);
        return data_.at(key);
    }

    // Вариант 4
    string& get(const string& key) const {
        lock_guard<mutex> lock(mtx_);
        return data_[key];
    }
};
```
a) Вариант 1
b) Вариант 2
c) Вариант 3
d) Вариант 4

13. Что выведет данный код?
```cpp
class Counter {
    int value_ = 0;
public:
    void increment() const {
        const_cast<Counter*>(this)->value_++;
    }
    int getValue() const { return value_; }
};

int main() {
    const Counter c;
    c.increment();
    cout << c.getValue();
}
```
a) 0
b) 1
c) Ошибка компиляции
d) Неопределенное поведение

14. Какой код правильно использует константные параметры?
```cpp
// Вариант 1
void process(const int x) { cout << x; }

// Вариант 2
void process(const string& s) { cout << s; }

// Вариант 3
void process(const unique_ptr<int> ptr) { cout << *ptr; }

// Вариант 4
void process(const int* const ptr) { cout << *ptr; }
```
a) Вариант 1
b) Вариант 2
c) Вариант 3
d) Вариант 4

15. Что произойдет при компиляции?
```cpp
class Widget {
    int value_;
public:
    Widget(int v) : value_(v) {}
    
    Widget& operator=(const Widget& other) const {
        value_ = other.value_;
        return *this;
    }
};
```
a) Код скомпилируется успешно
b) Ошибка компиляции - нельзя модифицировать поля в константном операторе
c) Ошибка компиляции - оператор присваивания не может быть константным
d) Ошибка компиляции - неверный тип возвращаемого значения

16. Какое утверждение о const в шаблонных классах верно?
```cpp
template<typename T>
class Container {
    T data_;
public:
    const T& get() const { return data_; }
    void set(const T& value) { data_ = value; }
};
```
a) Константность метода get() зависит от типа T
b) Константность параметра в set() избыточна для примитивных типов
c) Возвращаемое значение get() всегда константно
d) Все методы должны быть константными для обеспечения type safety

17. Что произойдет при выполнении кода?
```cpp
class Singleton {
    static const Singleton* instance_;
    Singleton() = default;
public:
    static const Singleton& getInstance() {
        if (!instance_) {
            instance_ = new Singleton();
        }
        return *instance_;
    }
};
const Singleton* Singleton::instance_ = nullptr;

int main() {
    const auto& inst1 = Singleton::getInstance();
    const auto& inst2 = Singleton::getInstance();
}
```
a) Код скомпилируется и отработает корректно
b) Ошибка компиляции - нельзя модифицировать статическое константное поле
c) Ошибка компиляции - конструктор должен быть константным
d) Утечка памяти

18. Какой код демонстрирует правильное использование константных итераторов?
```cpp
// Вариант 1
for(const auto it = vec.begin(); it != vec.end(); ++it) {
    cout << *it;
}

// Вариант 2
for(auto it = vec.cbegin(); it != vec.cend(); ++it) {
    cout << *it;
}

// Вариант 3
for(const auto& x : vec) {
    cout << x;
}

// Вариант 4
for(auto cit = vec.cbegin(); cit != vec.cend(); ++cit) {
    *cit = 42;
}
```
a) Вариант 1
b) Вариант 2
c) Вариант 3
d) Все варианты корректны

19. Что произойдет при компиляции?
```cpp
class Base {
public:
    virtual int getValue() const = 0;
};

class Derived : public Base {
    int value_;
public:
    int getValue() { return value_; }
};
```
a) Код скомпилируется успешно
b) Ошибка компиляции - чисто виртуальный метод не реализован
c) Ошибка компиляции - несоответствие константности
d) Ошибка компиляции - неверный тип возвращаемого значения

20. Какой код правильно использует константные указатели на члены класса?
```cpp
class Widget {
    int value_;
public:
    void setValue(int v) { value_ = v; }
    int getValue() const { return value_; }
};

// Вариант 1
const int Widget::* ptr = &Widget::value_;

// Вариант 2
void (Widget::* const ptr)(int) = &Widget::setValue;

// Вариант 3
int (Widget::* const ptr)() const = &Widget::getValue;

// Вариант 4
const int (Widget::* const ptr)() const = &Widget::getValue;
```
a) Вариант 1
b) Вариант 2
c) Вариант 3
d) Вариант 4

[Продолжение следует...] 

21. Что произойдет при компиляции?
```cpp
class Widget {
    mutable int cache_value_ = 0;
    mutable bool is_cached_ = false;
public:
    int getValue() const {
        if (!is_cached_) {
            cache_value_ = heavyComputation();
            is_cached_ = true;
        }
        return cache_value_;
    }
private:
    int heavyComputation() const;
};
```
a) Ошибка компиляции - нельзя модифицировать поля в const методе
b) Ошибка компиляции - heavyComputation должен быть не const
c) Код скомпилируется успешно
d) Неопределенное поведение

22. Какой код правильно использует константные методы в шаблонном классе?
```cpp
template<typename T>
class Container {
    T data_;
public:
    // Вариант 1
    T& get() { return data_; }
    const T& get() const { return data_; }

    // Вариант 2
    const T& get() { return data_; }
    const T& get() const { return data_; }

    // Вариант 3
    T& get() const { return data_; }

    // Вариант 4
    const T& get() { return data_; }
};
```
a) Вариант 1
b) Вариант 2
c) Вариант 3
d) Вариант 4

23. Что выведет данный код?
```cpp
class Value {
    int x_ = 0;
public:
    void setX(int x) const {
        const_cast<Value*>(this)->x_ = x;
    }
    int getX() const { return x_; }
};

int main() {
    const Value v;
    v.setX(42);
    cout << v.getX();
}
```
a) 0
b) 42
c) Ошибка компиляции
d) Неопределенное поведение

24. Какой код демонстрирует правильное использование константных параметров функции?
```cpp
// Вариант 1
void process(const vector<int>& v, const int size);

// Вариант 2
void process(const vector<int>& v, int size);

// Вариант 3
void process(vector<int> v, const int size);

// Вариант 4
void process(const vector<int> v, int size);
```
a) Вариант 1
b) Вариант 2
c) Вариант 3
d) Вариант 4

25. Что произойдет при компиляции?
```cpp
class Base {
public:
    virtual void process() const = 0;
};

class Derived : public Base {
public:
    void process() override {
        // some code
    }
};
```
a) Код скомпилируется успешно
b) Ошибка компиляции - метод не помечен как const
c) Ошибка компиляции - неверное использование override
d) Ошибка компиляции - чисто виртуальный метод не реализован

26. Какой код правильно использует константные итераторы?
```cpp
map<string, int> m;
// Вариант 1
for(auto it = m.begin(); it != m.end(); ++it) {
    cout << it->second;
}

// Вариант 2
for(const auto& [key, value] : m) {
    cout << value;
}

// Вариант 3
for(auto it = m.cbegin(); it != m.cend(); ++it) {
    it->second = 42;
}

// Вариант 4
for(const auto it = m.begin(); it != m.end(); ++it) {
    cout << it->second;
}
```
a) Вариант 1
b) Вариант 2
c) Вариант 3
d) Вариант 4

27. Что произойдет при компиляции?
```cpp
class Widget {
    int value_;
public:
    Widget(int v) : value_(v) {}
    
    const Widget operator+(const Widget& other) const {
        return Widget(value_ + other.value_);
    }
};
```
a) Код скомпилируется успешно
b) Ошибка компиляции - оператор + не может быть константным
c) Ошибка компиляции - возвращаемое значение не должно быть константным
d) Ошибка компиляции - параметр не должен быть константным

28. Какое утверждение о const в многопоточном программировании верно?
a) const методы всегда потокобезопасны
b) const методы могут быть не потокобезопасны при использовании mutable
c) const методы гарантируют отсутствие гонок данных
d) const методы не могут использовать мьютексы

29. Что произойдет при компиляции?
```cpp
class Wrapper {
    unique_ptr<int> ptr_;
public:
    Wrapper(int value) : ptr_(make_unique<int>(value)) {}
    const unique_ptr<int>& getPtr() const { return ptr_; }
};

int main() {
    Wrapper w(42);
    auto ptr = w.getPtr();
    *ptr = 10;
}
```
a) Код скомпилируется успешно
b) Ошибка компиляции - нельзя изменять значение через константный указатель
c) Ошибка компиляции - нельзя копировать unique_ptr
d) Неопределенное поведение

30. Какой код правильно использует константные методы в иерархии классов?
```cpp
class Shape {
public:
    virtual double getArea() const = 0;
};

class Circle : public Shape {
    double radius_;
public:
    // Вариант 1
    double getArea() { return 3.14 * radius_ * radius_; }

    // Вариант 2
    double getArea() const override { return 3.14 * radius_ * radius_; }

    // Вариант 3
    const double getArea() const { return 3.14 * radius_ * radius_; }

    // Вариант 4
    virtual double getArea() const { return 3.14 * radius_ * radius_; }
};
```
a) Вариант 1
b) Вариант 2
c) Вариант 3
d) Вариант 4

31. Что произойдет при компиляции?
```cpp
template<typename T>
class Container {
    T value_;
public:
    template<typename U>
    void setValue(const U& val) const {
        value_ = static_cast<T>(val);
    }
};
```
a) Код скомпилируется успешно
b) Ошибка компиляции - нельзя модифицировать поля в константном методе
c) Ошибка компиляции - неверное приведение типов
d) Ошибка компиляции - шаблонный метод не может быть константным

32. Какой код демонстрирует правильное использование константных ссылок?
```cpp
class Heavy {
    vector<int> data_;
public:
    // Вариант 1
    const Heavy& operator=(const Heavy& other) {
        data_ = other.data_;
        return *this;
    }

    // Вариант 2
    Heavy& operator=(const Heavy& other) {
        data_ = other.data_;
        return *this;
    }

    // Вариант 3
    const Heavy& operator=(Heavy& other) {
        data_ = other.data_;
        return *this;
    }

    // Вариант 4
    Heavy operator=(const Heavy& other) {
        data_ = other.data_;
        return *this;
    }
};
```
a) Вариант 1
b) Вариант 2
c) Вариант 3
d) Вариант 4

33. Что произойдет при компиляции?
```cpp
class Widget {
    int value_;
public:
    Widget(int v) : value_(v) {}
    
    friend const Widget operator+(const Widget& a, const Widget& b) {
        return Widget(a.value_ + b.value_);
    }
};
```
a) Код скомпилируется успешно
b) Ошибка компиляции - friend функция не может быть константной
c) Ошибка компиляции - возвращаемое значение не должно быть константным
d) Ошибка компиляции - параметры не должны быть константными

34. Какое утверждение о const в умных указателях верно?
a) shared_ptr<const T> запрещает изменение объекта, но разрешает изменение указателя
b) const shared_ptr<T> запрещает изменение указателя, но разрешает изменение объекта
c) const unique_ptr<T> нельзя перемещать
d) Все вышеперечисленное верно

35. Что произойдет при компиляции?
```cpp
class Base {
protected:
    virtual void process() const = 0;
public:
    void execute() const {
        process();
    }
};

class Derived : public Base {
protected:
    void process() const override {
        // some code
    }
};
```
a) Код скомпилируется успешно
b) Ошибка компиляции - protected метод не может быть константным
c) Ошибка компиляции - virtual метод не может быть константным
d) Ошибка компиляции - неверное использование override

36. Какой код правильно использует константные методы в шаблонах?
```cpp
template<typename T>
class Container {
    T data_;
public:
    // Вариант 1
    const T& get() const & { return data_; }
    T&& get() && { return std::move(data_); }

    // Вариант 2
    const T& get() const { return data_; }
    T& get() { return data_; }

    // Вариант 3
    T get() const { return data_; }

    // Вариант 4
    const T& get() { return data_; }
};
```
a) Вариант 1
b) Вариант 2
c) Вариант 3
d) Вариант 4

37. Что произойдет при компиляции?
```cpp
class Widget {
    int value_;
public:
    Widget(int v) : value_(v) {}
    
    operator const int&() const {
        return value_;
    }
};
```
a) Код скомпилируется успешно
b) Ошибка компиляции - оператор приведения не может быть константным
c) Ошибка компиляции - нельзя возвращать константную ссылку
d) Ошибка компиляции - неверный синтаксис оператора приведения

38. Какой код демонстрирует правильное использование const в friend функциях?
```cpp
class Widget {
    int value_;
public:
    // Вариант 1
    friend void process(const Widget& w) {
        w.value_ = 42;
    }

    // Вариант 2
    friend void process(Widget& w) const {
        w.value_ = 42;
    }

    // Вариант 3
    friend const void process(const Widget& w) {
        cout << w.value_;
    }

    // Вариант 4
    friend void process(const Widget& w) {
        cout << w.value_;
    }
};
```
a) Вариант 1
b) Вариант 2
c) Вариант 3
d) Вариант 4

39. Что произойдет при компиляции?
```cpp
class Base {
public:
    virtual const string& getName() const = 0;
};

class Derived : public Base {
    string name_;
public:
    const string& getName() const override {
        return name_;
    }
    void setName(string n) {
        name_ = move(n);
    }
};
```
a) Код скомпилируется успешно
b) Ошибка компиляции - getName должен возвращать не константную ссылку
c) Ошибка компиляции - setName должен быть константным
d) Ошибка компиляции - неверное использование move

40. Какое утверждение о const в лямбда-функциях верно?
```cpp
auto lambda1 = [](const int& x) { return x * 2; };
auto lambda2 = [](int x) const { return x * 2; };
auto lambda3 = [value = 42](int x) const mutable { return x + value++; };
auto lambda4 = [](const int& x) const { return x * 2; };
```
a) lambda1 и lambda2 эквивалентны
b) lambda3 может изменять захваченные значения
c) lambda4 содержит избыточное использование const
d) Все лямбды корректны и имеют разное поведение 