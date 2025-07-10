# Тест по неопределенному поведению в C++

## Вопрос 1
Что произойдет при выполнении следующего кода?
```cpp
#include <vector>
int main() {
    std::vector<int> v{1, 2, 3};
    int x = v[10];
    return 0;
}
```
a) Программа выведет 0
b) Программа выбросит исключение std::out_of_range
c) Неопределенное поведение
d) Программа скомпилируется с ошибкой

## Вопрос 2
Какой из следующих способов доступа к элементам vector безопасен?
```cpp
std::vector<int> vec{1, 2, 3, 4, 5};
size_t index = 10;
```
a) `int val = vec[index];`
b) `int val = vec.at(index);`
c) `int val = *(vec.data() + index);`
d) Все варианты безопасны

## Вопрос 3
Что происходит при следующем коде?
```cpp
int main() {
    int* ptr = new int(42);
    delete ptr;
    delete ptr;
    return 0;
}
```
a) Программа корректно завершится
b) Выбросится исключение
c) Неопределенное поведение
d) Ошибка компиляции

## Вопрос 4
Какое поведение демонстрирует этот код при переполнении?
```cpp
#include <climits>
bool test(int n) {
    return n < n + 1;
}
int main() {
    return test(INT_MAX) ? 0 : 1;
}
```
a) Всегда возвращает false
b) Всегда возвращает true
c) Неопределенное поведение при n = INT_MAX
d) Ошибка компиляции

## Вопрос 5
Что неправильно в следующем коде?
```cpp
#include <vector>
void duplicate(std::vector<int>& v) {
    for (const auto& elem : v) {
        v.push_back(elem * 2);
    }
}
```
a) Нарушение const-корректности
b) Модификация контейнера во время итерации
c) Неправильное использование auto
d) Код корректен

## Вопрос 6
Какой результат у этого кода?
```cpp
int& getRef() {
    int x = 42;
    return x;
}
int main() {
    int& ref = getRef();
    return ref;
}
```
a) Вернет 42
b) Вернет 0
c) Неопределенное поведение
d) Ошибка компиляции

## Вопрос 7
Что происходит в многопоточном коде?
```cpp
#include <thread>
int counter = 0;
void increment() {
    ++counter;
}
int main() {
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join(); t2.join();
    return 0;
}
```
a) counter всегда равен 2
b) counter может быть 1 или 2
c) Неопределенное поведение из-за гонки данных
d) Ошибка компиляции

## Вопрос 8
Какое утверждение верно о переполнении unsigned типов?
```cpp
unsigned int x = UINT_MAX;
unsigned int y = x + 1;
```
a) Неопределенное поведение
b) Поведение определено: y == 0
c) Выбрасывается исключение
d) Ошибка компиляции

## Вопрос 9
Что неправильно в этом коде?
```cpp
std::string_view getView() {
    std::string temp = "Hello";
    return temp;
}
```
a) string_view не может быть создан из string
b) temp уничтожается, string_view становится недействительным
c) Неправильный тип возвращаемого значения
d) Код корректен

## Вопрос 10
Какой компилятор может оптимизировать этот код до "return true;"?
```cpp
bool always_less(int n) {
    return n < n + 1;  // при любом n кроме INT_MAX
}
```
a) Никакой, это невозможно
b) Только старые компиляторы
c) GCC с оптимизацией, предполагая отсутствие UB
d) Только в debug режиме

## Вопрос 11
Что произойдет при выполнении?
```cpp
union Data {
    int i;
    float f;
};
int main() {
    Data d;
    d.i = 42;
    float result = d.f;
    return 0;
}
```
a) result будет интерпретацией битов 42 как float
b) Неопределенное поведение
c) result будет равен 42.0f
d) Ошибка компиляции

## Вопрос 12
Какая проблема с этим кодом?
```cpp
int arr[5] = {1, 2, 3, 4, 5};
const int NUM_ELEMENTS = 6;
for (int i = 0; i < NUM_ELEMENTS; ++i) {
    std::cout << arr[i] << " ";
}
```
a) Неправильная инициализация массива
b) Выход за границы массива
c) Неправильное использование const
d) Код корректен

## Вопрос 13
Что происходит после std::move?
```cpp
std::string str = "Hello";
std::string moved = std::move(str);
std::cout << str.length();  // Что здесь?
```
a) Выведет 5
b) Выведет 0
c) Неопределенное поведение
d) Ошибка компиляции

## Вопрос 14
Какой инструмент поможет обнаружить UB во время выполнения?
a) clang-tidy
b) UndefinedBehaviorSanitizer
c) cppcheck
d) Все перечисленные

## Вопрос 15
Что неправильно в этом коде?
```cpp
void process(std::vector<int>& vec) {
    auto it = vec.begin();
    vec.resize(vec.size() * 2);
    std::cout << *it;  // Проблема здесь
}
```
a) Неправильное использование auto
b) Итератор может быть инвалидирован после resize
c) Неправильное использование resize
d) Код корректен

## Вопрос 16
Какое поведение у этого кода?
```cpp
int i = 1;
int result = ++i + i++;
```
a) result == 5
b) result == 4
c) Неопределенное поведение
d) Ошибка компиляции

## Вопрос 17
Что происходит при обращении к nullptr?
```cpp
int* ptr = nullptr;
int value = *ptr;
```
a) value == 0
b) Выбрасывается исключение
c) Неопределенное поведение
d) Ошибка компиляции

## Вопрос 18
Какой правильный способ проверки переполнения?
```cpp
bool safe_add(int a, int b) {
    // Какой вариант правильный?
}
```
a) `return (a + b) >= a;`
b) `return a <= INT_MAX - b;`
c) `return (long long)a + b <= INT_MAX;`
d) Варианты b и c правильные

## Вопрос 19
Что происходит при использовании инвалидированного итератора?
```cpp
std::vector<int> v{1, 2, 3};
auto it = v.begin();
v.clear();
++it;  // Что здесь?
```
a) it указывает на начало пустого вектора
b) Неопределенное поведение
c) it == v.end()
d) Ошибка компиляции

## Вопрос 20
Какая ошибка в этом коде?
```cpp
class Resource {
    int* data;
public:
    Resource() : data(new int[100]) {}
    ~Resource() { delete[] data; }
};

int main() {
    Resource r1;
    Resource r2 = r1;  // Проблема
    return 0;
}
```
a) Неправильная инициализация
b) Двойное удаление памяти
c) Утечка памяти
d) Все варианты

## Вопрос 21
Что выведет этот код при оптимизации -O2?
```cpp
bool check_planets(const std::string planets[], int count) {
    for (int i = 0; i <= count; ++i) {  // <= вместо <
        if (planets[i] == "Earth") return true;
    }
    return false;
}
// Вызов: check_planets(planets_array, 8) где массив содержит 8 элементов
```
a) Всегда false
b) Всегда true (из-за UB и оптимизации)
c) Корректно найдет "Earth"
d) Ошибка компиляции

## Вопрос 22
Какая проблема с этим кодом?
```cpp
std::vector<int*> ptrs;
for (int i = 0; i < 10; ++i) {
    int value = i * 2;
    ptrs.push_back(&value);  // Проблема
}
```
a) Неправильная инициализация вектора
b) Сохранение указателей на локальные переменные
c) Утечка памяти
d) Код корректен

## Вопрос 23
Что происходит при strict aliasing violation?
```cpp
int i = 0x42424242;
float* f = reinterpret_cast<float*>(&i);
float result = *f;
```
a) result содержит интерпретацию битов i как float
b) Неопределенное поведение
c) result == 0.0f
d) Ошибка компиляции

## Вопрос 24
Какой способ правильный для безопасного доступа?
```cpp
std::vector<int> vec{1, 2, 3};
size_t index = getUserInput();  // может быть любое значение
```
a) `if (index >= 0 && index < vec.size()) return vec[index];`
b) `if (index < vec.size()) return vec[index];`
c) `return vec.at(index);`
d) Варианты b и c правильные

## Вопрос 25
Что неправильно в этой функции?
```cpp
template<typename T>
void unsafe_swap(T& a, T& b) {
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
    // Использование a или b после этого
    std::cout << a << " " << b;  // Проблема?
}
```
a) Неправильное использование move
b) Объекты могут быть в moved-from состоянии, но это не UB
c) Шаблон неправильно объявлен
d) Код корректен, moved-from объекты могут использоваться

## Вопрос 26
Какая оптимизация может произойти с этим кодом?
```cpp
void test() {
    int* p = nullptr;
    if (p != nullptr) {
        std::cout << "Not null";
    }
    *p = 42;  // UB
    std::cout << "After assignment";
}
```
a) Код будет работать как написано
b) Компилятор может удалить весь код после *p = 42
c) Компилятор может удалить проверку if
d) Компилятор не может ничего оптимизировать

## Вопрос 27
Что происходит в этом коде?
```cpp
char buffer[10];
char* ptr = buffer + 15;  // ptr за пределами массива
if (ptr > buffer + 9) {   // сравнение
    std::cout << "Out of bounds";
}
```
a) Код корректно определит выход за границы
b) Неопределенное поведение при создании ptr
c) Неопределенное поведение при сравнении
d) Ошибка компиляции

## Вопрос 28
Какая проблема с этим кодом RAII?
```cpp
class FileHandler {
    FILE* file;
public:
    FileHandler(const char* name) : file(fopen(name, "r")) {}
    ~FileHandler() { fclose(file); }  // Проблема?
    FILE* get() { return file; }
};
```
a) Неправильное использование fopen
b) Отсутствие проверки file на nullptr
c) Неправильная передача параметра
d) Код корректен

## Вопрос 29
Что происходит при переполнении стека?
```cpp
void recursive_function() {
    int large_array[10000];
    recursive_function();  // Бесконечная рекурсия
}
```
a) Неопределенное поведение
b) Выбрасывается std::bad_alloc
c) Программа корректно завершится
d) Ошибка компиляции

## Вопрос 30
Какая правильная последовательность действий?
```cpp
std::vector<int> vec{1, 2, 3, 4, 5};
// Нужно удалить все четные элементы
```
a) Использовать range-based for с erase
b) Использовать итераторы с erase в цикле
c) Использовать remove_if + erase idiom
d) Использовать clear() + заполнить заново

## Вопрос 31
Что неправильно в этом многопоточном коде?
```cpp
std::vector<int> shared_vector;
std::mutex mtx;

void thread1() {
    std::lock_guard<std::mutex> lock(mtx);
    shared_vector.push_back(1);
}

void thread2() {
    if (!shared_vector.empty()) {  // Без блокировки!
        std::cout << shared_vector.back();
    }
}
```
a) Неправильное использование lock_guard
b) Доступ к shared_vector без синхронизации в thread2
c) push_back не потокобезопасен
d) Неправильное использование mutex

## Вопрос 32
Какое поведение у этого кода?
```cpp
int main() {
    int arr[] = {1, 2, 3};
    int* end = arr + sizeof(arr)/sizeof(arr[0]);
    for (int* p = arr; p != end; ++p) {
        std::cout << *p;
    }
    std::cout << *end;  // Что здесь?
}
```
a) Выведет мусор
b) Неопределенное поведение
c) Выведет 0
d) Ошибка компиляции

## Вопрос 33
Что происходит при неправильном приведении типов?
```cpp
double d = 3.14159;
int* iptr = reinterpret_cast<int*>(&d);
int result = *iptr;
```
a) result содержит целую часть d
b) result содержит битовое представление части d
c) Неопределенное поведение
d) Ошибка компиляции

## Вопрос 34
Какая ошибка в этом коде с placement new?
```cpp
void test() {
    alignas(int) char buffer[sizeof(int)];
    int* p = new(buffer) int(42);
    std::cout << *p;
    // Что забыли?
}
```
a) Неправильное использование alignas
b) Забыли вызвать деструктор явно
c) Неправильное использование placement new
d) Код корректен

## Вопрос 35
Что происходит с lifetime объектов?
```cpp
std::string* create_string() {
    std::string local = "Hello";
    return &local;  // Возврат адреса локальной переменной
}
```
a) Вернется указатель на корректную строку
b) Неопределенное поведение при использовании указателя
c) Вернется nullptr
d) Ошибка компиляции

## Вопрос 36
Какая проблема с этим кодом использования памяти?
```cpp
void process_data() {
    int* data = new int[1000];
    // ... обработка данных ...
    if (some_condition) {
        return;  // Ранний выход
    }
    delete[] data;
}
```
a) Неправильное использование new[]
b) Потенциальная утечка памяти
c) Неправильное использование delete[]
d) Код корректен

## Вопрос 37
Что неправильно в этом использовании контейнеров?
```cpp
std::vector<int> get_vector() {
    return {1, 2, 3, 4, 5};
}

void process() {
    auto it = get_vector().begin();  // Проблема
    std::cout << *it;
}
```
a) Неправильное использование auto
b) Итератор указывает на временный объект
c) get_vector() работает неправильно
d) Код корректен

## Вопрос 38
Какое поведение при использовании uninitialized переменных?
```cpp
int main() {
    int x;  // Не инициализирована
    if (x > 0) {
        std::cout << "Positive";
    }
    return 0;
}
```
a) x будет равна 0
b) Неопределенное поведение
c) x будет содержать мусор, но поведение определено
d) Ошибка компиляции

## Вопрос 39
Что происходит при нарушении инварианта класса?
```cpp
class SafeArray {
    int* data;
    size_t size;
public:
    SafeArray(size_t s) : size(s), data(new int[s]) {}
    int& operator[](size_t index) {
        return data[index];  // Нет проверки границ
    }
    ~SafeArray() { delete[] data; }
};
```
a) Класс всегда безопасен
b) Возможно неопределенное поведение при неправильном индексе
c) Автоматическая проверка границ
d) Ошибка компиляции

## Вопрос 40
Какой инструмент лучше всего подходит для обнаружения этой ошибки?
```cpp
void test() {
    std::vector<int> v{1, 2, 3};
    for (auto it = v.begin(); it != v.end(); ++it) {
        if (*it == 2) {
            v.erase(it);  // Инвалидация итератора
        }
    }
}
```
a) Static analyzer (clang-tidy)
b) Debug режим STL
c) UndefinedBehaviorSanitizer  
d) Все перечисленные могут помочь 