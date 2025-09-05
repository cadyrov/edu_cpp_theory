# Тест: Односвязный список и работа с массивами

## Вопрос 1
Какая временная сложность доступа к N-му элементу односвязного списка?

a) O(1)
b) O(log N)
c) O(N)
d) O(N²)

## Вопрос 2
Что произойдет при выполнении следующего кода?
```cpp
int* arr = new int[5];
delete arr;  // Вместо delete[]
```

a) Корректное освобождение памяти
b) Неопределенное поведение
c) Утечка памяти
d) Ошибка компиляции

## Вопрос 3
Какой итератор нужен для вставки элемента в начало односвязного списка?

a) begin()
b) end()
c) before_begin()
d) rbegin()

## Вопрос 4
Что делает следующий код?
```cpp
template<typename Type>
class BasicIterator {
public:
    BasicIterator operator++(int) noexcept {
        auto old_value(*this);
        ++(*this);
        return old_value;
    }
};
```

a) Префиксный инкремент
b) Постфиксный инкремент
c) Декремент
d) Ошибка компиляции

## Вопрос 5
Какая категория итератора у односвязного списка?

a) std::input_iterator_tag
b) std::forward_iterator_tag
c) std::bidirectional_iterator_tag
d) std::random_access_iterator_tag

## Вопрос 6
Что произойдет при выполнении этого кода?
```cpp
int numbers[5];
int* p = &numbers[10];  // Выход за границы
```

a) Корректное получение адреса
b) Неопределенное поведение
c) Ошибка компиляции
d) Исключение runtime_error

## Вопрос 7
Зачем нужен фиктивный узел head_ в односвязном списке?

a) Для хранения размера списка
b) Для упрощения операций вставки в начало
c) Для поддержки итератора before_begin()
d) Все варианты верны

## Вопрос 8
Что делает следующий код?
```cpp
template<typename Type>
void swap(SingleLinkedList<Type>& lhs, SingleLinkedList<Type>& rhs) noexcept {
    lhs.swap(rhs);
}
```

a) Копирует элементы из lhs в rhs
b) Обменивает содержимое двух списков
c) Удаляет содержимое обоих списков
d) Объединяет два списка

## Вопрос 9
Какой тип должен возвращать operator->() для константного итератора?

a) Type*
b) const Type*
c) Type&
d) const Type&

## Вопрос 10
Что произойдет при выполнении следующего кода?
```cpp
SingleLinkedList<int> list{1, 2, 3};
auto it = list.begin();
list.Clear();
int value = *it;  // Использование невалидного итератора
```

a) Вернет 1
b) Вернет 0
c) Неопределенное поведение
d) Исключение

## Вопрос 11
Какая из реализаций конструктора копирования более безопасна?

a) 
```cpp
SingleLinkedList(const SingleLinkedList& other) {
    for (const auto& item : other) {
        PushFront(item);
    }
}
```

b)
```cpp
SingleLinkedList(const SingleLinkedList& other) {
    SingleLinkedList tmp;
    for (const auto& item : other) {
        tmp.PushFront(item);
    }
    swap(tmp);
}
```

c) Обе одинаково безопасны
d) Обе небезопасны

## Вопрос 12
Что означает ключевое слово friend в следующем контексте?
```cpp
class BasicIterator {
private:
    friend class SingleLinkedList;
    Node* node_;
};
```

a) SingleLinkedList наследует от BasicIterator
b) BasicIterator может обращаться к приватным членам SingleLinkedList
c) SingleLinkedList может обращаться к приватным членам BasicIterator
d) Создается двунаправленная связь

## Вопрос 13
Какой результат у следующего кода?
```cpp
int* arr = new int[3]{1, 2, 3};
int* p = arr + 2;
cout << p[-1];
```

a) 1
b) 2
c) 3
d) Неопределенное поведение

## Вопрос 14
Что делает атрибут [[nodiscard]]?

a) Запрещает использование функции
b) Предупреждает, если возвращаемое значение игнорируется
c) Делает функцию constexpr
d) Делает функцию noexcept

## Вопрос 15
Какая временная сложность операции PushFront в односвязном списке?

a) O(1)
b) O(log N)
c) O(N)
d) O(N²)

## Вопрос 16
Что произойдет при выполнении этого кода?
```cpp
template<typename Type>
class ArrayPtr {
public:
    ArrayPtr(size_t size) : ptr_(new Type[size]) {}
    // Нет деструктора
private:
    Type* ptr_;
};
```

a) Корректная работа
b) Утечка памяти
c) Двойное удаление
d) Ошибка компиляции

## Вопрос 17
Какой из вариантов правильно реализует операцию разыменования итератора?

a) `Type operator*() const { return node_->value; }`
b) `Type& operator*() const { return node_->value; }`
c) `Type* operator*() const { return &node_->value; }`
d) `const Type& operator*() const { return node_->value; }`

## Вопрос 18
Что делает следующий код?
```cpp
Iterator EraseAfter(ConstIterator pos) {
    Node* to_delete = pos.node_->next_node;
    pos.node_->next_node = to_delete->next_node;
    delete to_delete;
    --size_;
    return Iterator{pos.node_->next_node};
}
```

a) Удаляет элемент на позиции pos
b) Удаляет элемент после позиции pos
c) Удаляет элемент перед позицией pos
d) Очищает весь список

## Вопрос 19
Какой тип должен иметь difference_type для итератора?

a) int
b) size_t
c) std::ptrdiff_t
d) long long

## Вопрос 20
Что произойдет при выполнении следующего кода?
```cpp
int arr[5] = {1, 2, 3, 4, 5};
int* begin_ptr = arr;
int* end_ptr = arr + 5;
// Можно ли разыменовать end_ptr?
int value = *end_ptr;
```

a) Вернет 5
b) Вернет 0
c) Неопределенное поведение
d) Ошибка компиляции

## Вопрос 21
Какая из реализаций operator== более эффективна?

a)
```cpp
bool operator==(const SingleLinkedList& other) const {
    return std::equal(begin(), end(), other.begin(), other.end());
}
```

b)
```cpp
bool operator==(const SingleLinkedList& other) const {
    if (size_ != other.size_) return false;
    return std::equal(begin(), end(), other.begin());
}
```

c) Обе одинаково эффективны
d) Нельзя определить без дополнительной информации

## Вопрос 22
Что делает perfect forwarding в следующем коде?
```cpp
template<typename T>
void PushFront(T&& value) {
    head_.next_node = new Node(std::forward<T>(value), head_.next_node);
}
```

a) Всегда копирует значение
b) Всегда перемещает значение
c) Сохраняет категорию значения (lvalue/rvalue)
d) Преобразует в rvalue

## Вопрос 23
Какой метод позволяет получить сырой указатель из умного указателя без передачи владения?

a) Release()
b) Get()
c) Reset()
d) Swap()

## Вопрос 24
Что произойдет при выполнении этого кода?
```cpp
std::vector<int> vec{1, 2, 3, 4, 5};
int* data = vec.data();
vec.clear();
int value = data[0];  // Использование после clear()
```

a) Вернет 1
b) Вернет 0
c) Неопределенное поведение
d) Исключение

## Вопрос 25
Какая из версий инкремента более эффективна для итераторов?

a) Префиксная (++it)
b) Постфиксная (it++)
c) Обе одинаково эффективны
d) Зависит от реализации

## Вопрос 26
Что делает следующий код?
```cpp
template<typename Type>
ArrayPtr<Type>::ArrayPtr(ArrayPtr&& other) noexcept 
    : raw_ptr_(other.Release()) {}
```

a) Конструктор копирования
b) Конструктор перемещения
c) Оператор присваивания
d) Деструктор

## Вопрос 27
Какой недостаток у односвязного списка по сравнению с массивом?

a) Больше памяти на элемент
b) Плохая локальность данных
c) Линейный доступ к элементам
d) Все варианты верны

## Вопрос 28
Что произойдет при выполнении этого кода?
```cpp
int* arr1 = new int[10];
int* arr2 = new int[10];
std::ptrdiff_t diff = arr1 - arr2;  // Разность указателей на разные массивы
```

a) Корректное вычисление разности
b) Неопределенное поведение
c) Ошибка компиляции
d) Исключение

## Вопрос 29
Какой из способов инициализации массива в куче правильный?

a) `int* arr = new int[5];`
b) `int* arr = new int[5]{};`
c) `int* arr = new int[5]{1, 2, 3};`
d) Все варианты правильные

## Вопрос 30
Что делает следующий код?
```cpp
SingleLinkedList<int> list;
auto pos = list.before_begin();
for (int i = 0; i < 5; ++i) {
    pos = list.InsertAfter(pos, i);
}
```

a) Создает список {0, 1, 2, 3, 4}
b) Создает список {4, 3, 2, 1, 0}
c) Создает пустой список
d) Приводит к неопределенному поведению

## Вопрос 31
Какая проблема с этим кодом?
```cpp
class Iterator {
public:
    Iterator& operator++() {
        node_ = node_->next_node;
        return *this;
    }
    
    Iterator operator++(int) {
        node_ = node_->next_node;
        return *this;
    }
};
```

a) Нет проблем
b) Постфиксный инкремент не сохраняет старое значение
c) Префиксный инкремент работает неправильно
d) Отсутствует noexcept

## Вопрос 32
Что означает std::forward_iterator_tag?

a) Итератор поддерживает только чтение
b) Итератор поддерживает движение только вперед
c) Итератор поддерживает произвольный доступ
d) Итератор поддерживает движение в обе стороны

## Вопрос 33
Какой результат у следующего кода?
```cpp
int arr[3] = {10, 20, 30};
int* p = arr + 1;
cout << p[1] << " " << p[-1];
```

a) 20 10
b) 30 10
c) 20 30
d) 10 30

## Вопрос 34
Что делает идиома copy-and-swap?

a) Копирует объект и обменивает его с другим
b) Обеспечивает строгую гарантию безопасности исключений
c) Упрощает реализацию присваивания
d) Все варианты верны

## Вопрос 35
Какая проблема с этим кодом?
```cpp
template<typename Type>
class SingleLinkedList {
    SingleLinkedList& operator=(const SingleLinkedList& other) {
        if (this == &other) return *this;
        Clear();
        for (const auto& item : other) {
            PushFront(item);
        }
        return *this;
    }
};
```

a) Нет проблем
b) Нет проверки на самоприсваивание
c) Не обеспечивает строгую гарантию безопасности исключений
d) Неправильный порядок элементов

## Вопрос 36
Что произойдет при выполнении этого кода?
```cpp
int* createArray() {
    int arr[5] = {1, 2, 3, 4, 5};
    return arr;  // Возврат указателя на локальный массив
}
```

a) Корректный возврат массива
b) Неопределенное поведение
c) Ошибка компиляции
d) Утечка памяти

## Вопрос 37
Какой из методов итератора должен быть noexcept?

a) Только конструктор
b) Только операторы сравнения
c) Все методы, которые не могут выбросить исключение
d) Никакие методы

## Вопрос 38
Что делает следующий код?
```cpp
template<typename Type>
void ArrayPtr<Type>::swap(ArrayPtr& other) noexcept {
    std::swap(raw_ptr_, other.raw_ptr_);
}
```

a) Копирует массивы
b) Обменивает указатели на массивы
c) Объединяет массивы
d) Удаляет массивы

## Вопрос 39
Какая временная сложность операции Clear() в односвязном списке?

a) O(1)
b) O(log N)
c) O(N)
d) O(N²)

## Вопрос 40
Что произойдет при выполнении этого кода?
```cpp
SingleLinkedList<std::string> list{"hello", "world"};
auto it = list.begin();
++it;
list.Clear();
std::string str = *it;  // Использование итератора после Clear()
```

a) Вернет "world"
b) Вернет пустую строку
c) Неопределенное поведение
d) Исключение std::runtime_error 