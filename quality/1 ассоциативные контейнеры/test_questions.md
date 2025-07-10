# Тест по ассоциативным контейнерам C++

## Вопросы с вариантами ответов

### 1. Какая асимптотическая сложность поиска элемента в std::map?
A) O(1)
B) O(log n)
C) O(n)
D) O(n log n)

### 2. Что произойдет при выполнении следующего кода?
```cpp
std::map<int, string> m;
std::cout << m[5];
```
A) Программа не скомпилируется
B) Будет выведена пустая строка
C) Будет исключение runtime_error
D) Undefined behavior

### 3. Какие требования предъявляются к ключам в std::unordered_map?
A) Только operator<
B) Только operator== и хеш-функция
C) operator< и operator==
D) operator== и operator!=

### 4. Что выведет следующий код?
```cpp
std::set<int> s{3, 1, 4, 1, 5};
for(int x : s) std::cout << x << " ";
```
A) 3 1 4 1 5
B) 1 1 3 4 5
C) 1 3 4 5
D) 3 1 4 5

### 5. В чем основное отличие std::map от std::unordered_map?
A) map поддерживает дубликаты ключей
B) map гарантирует порядок элементов
C) unordered_map быстрее во всех случаях
D) map может хранить только числовые ключи

### 6. Какой метод следует использовать для безопасной проверки наличия элемента?
A) operator[]
B) at()
C) find()
D) count()

### 7. Что произойдет при выполнении этого кода?
```cpp
std::unordered_set<std::vector<int>> s;
s.insert({1, 2, 3});
```
A) Код скомпилируется и выполнится
B) Ошибка компиляции - нет хеш-функции
C) Runtime error
D) Undefined behavior

### 8. Какая сложность операции insert в std::unordered_map в среднем случае?
A) O(1)
B) O(log n)
C) O(n)
D) O(n log n)

### 9. Для какой структуры нужно определить компаратор для использования в std::set?
```cpp
struct Point {
    int x, y;
};
```
A) Не нужно, структура простая
B) Только operator<
C) Только operator==
D) operator< и operator==

### 10. Что выведет этот код?
```cpp
std::multiset<int> ms{1, 2, 2, 3};
std::cout << ms.count(2);
```
A) 1
B) 2
C) true
D) false

### 11. Какой контейнер лучше выбрать для подсчета частоты слов в большом тексте?
A) std::map<string, int>
B) std::unordered_map<string, int>
C) std::set<pair<string, int>>
D) std::vector<pair<string, int>>

### 12. Что означает is_transparent в компараторе?
A) Компаратор прозрачен для оптимизации
B) Позволяет гетерогенный поиск
C) Указывает на отсутствие побочных эффектов
D) Обозначает inline-компаратор

### 13. Какой результат у следующего кода?
```cpp
std::map<string, int> m{{"a", 1}, {"b", 2}};
auto [it, success] = m.insert({"a", 3});
std::cout << it->second;
```
A) 1
B) 2
C) 3
D) Ошибка компиляции

### 14. В чем проблема следующей хеш-функции?
```cpp
struct BadHasher {
    size_t operator()(const pair<int, int>& p) const {
        return p.first + p.second;
    }
};
```
A) Неправильный тип возвращаемого значения
B) Высокая вероятность коллизий
C) Нет проблем
D) Слишком медленная

### 15. Что произойдет при выполнении этого кода?
```cpp
std::set<int> s{1, 2, 3};
auto it = s.begin();
*it = 10;
```
A) Элемент изменится на 10
B) Ошибка компиляции
C) Runtime error
D) Undefined behavior

### 16. Какой метод C++17 позволяет вставить элемент только если ключа нет?
A) insert()
B) emplace()
C) try_emplace()
D) insert_or_assign()

### 17. Что выведет следующий код?
```cpp
std::unordered_map<int, string> m{{1, "one"}, {2, "two"}};
m.erase(1);
std::cout << m.size();
```
A) 1
B) 2
C) 0
D) Undefined

### 18. Какую сложность имеет операция erase() в std::map?
A) O(1)
B) O(log n)
C) O(n)
D) O(n log n)

### 19. Для чего используется метод reserve() в unordered_контейнерах?
A) Резервирует конкретные ключи
B) Уменьшает количество перехеширований
C) Устанавливает максимальный размер
D) Не существует такого метода

### 20. Что произойдет с итераторами после rehash в unordered_map?
A) Останутся валидными
B) Станут невалидными
C) Зависит от реализации
D) Только некоторые станут невалидными

### 21. Какой код демонстрирует правильное использование emplace?
A) `m.emplace(make_pair("key", "value"))`
B) `m.emplace("key", "value")`
C) `m.emplace({"key", "value"})`
D) Все варианты правильные

### 22. Что выведет этот код?
```cpp
std::map<int, int> m;
m[1] = 10;
m[1] += 5;
std::cout << m[1];
```
A) 10
B) 15
C) 5
D) Ошибка компиляции

### 23. В чем основная проблема использования std::map для случайных ключей?
A) Большой расход памяти
B) Медленный поиск
C) Плохая локальность ссылок
D) Нет проблем

### 24. Какой тип лучше использовать для хранения больших объектов в качестве значений?
A) Сами объекты
B) Указатели на объекты
C) shared_ptr на объекты
D) unique_ptr на объекты

### 25. Что произойдет при выполнении этого кода?
```cpp
std::set<int*> s;
int a = 5, b = 5;
s.insert(&a);
s.insert(&b);
std::cout << s.size();
```
A) 1
B) 2
C) Ошибка компиляции
D) Undefined behavior

### 26. Какая функция позволяет узнать load_factor в unordered_map?
A) load_factor()
B) bucket_count()
C) size() / bucket_count()
D) max_load_factor()

### 27. Что выведет следующий код?
```cpp
std::multimap<int, string> mm;
mm.insert({1, "first"});
mm.insert({1, "second"});
std::cout << mm.count(1);
```
A) 1
B) 2
C) true
D) false

### 28. Какой способ итерирования по map наиболее эффективен в C++17?
A) `for(auto it = m.begin(); it != m.end(); ++it)`
B) `for(const auto& p : m)`
C) `for(const auto& [key, value] : m)`
D) Все способы одинакового эффективны

### 29. В чем проблема следующего кода?
```cpp
std::unordered_map<std::string, int> m;
const char* key = "test";
std::cout << m[key];
```
A) Создается временный string объект
B) Ошибка компиляции
C) Runtime error
D) Нет проблем

### 30. Что произойдет при повторной вставке одного ключа в std::map?
A) Значение перезапишется
B) Значение не изменится
C) Будет исключение
D) Undefined behavior

### 31. Какой контейнер позволяет эффективно найти все элементы в диапазоне ключей?
A) std::unordered_map
B) std::map
C) std::unordered_set
D) std::vector

### 32. Что выведет этот код?
```cpp
std::set<string> s{"abc", "def", "abc"};
std::cout << s.size();
```
A) 2
B) 3
C) 1
D) Ошибка компиляции

### 33. Какой заголовочный файл нужен для std::unordered_map?
A) <map>
B) <unordered_map>
C) <hash_map>
D) <associative>

### 34. Что произойдет при выполнении этого кода?
```cpp
std::map<int, int> m{{1, 10}, {2, 20}};
auto node = m.extract(1);
m.insert(std::move(node));
```
A) Элемент удалится
B) Элемент переместится в конец
C) Элемент вернется в map
D) Ошибка компиляции

### 35. В чем преимущество метода at() перед operator[]?
A) Быстрее работает
B) Не создает новые элементы
C) Поддерживает const объекты
D) Все перечисленное

### 36. Что выведет следующий код?
```cpp
std::map<string, int> m{{"a", 1}};
try {
    std::cout << m.at("b");
} catch (const std::out_of_range&) {
    std::cout << "Not found";
}
```
A) 0
B) Not found
C) Пустая строка
D) Ошибка компиляции

### 37. Какая структура данных лежит в основе std::map?
A) Хеш-таблица
B) Красно-черное дерево
B) AVL-дерево
D) B-дерево

### 38. Что произойдет при выполнении этого кода?
```cpp
std::unordered_set<int> s{1, 2, 3};
for (auto it = s.begin(); it != s.end(); ++it) {
    if (*it == 2) s.erase(it);
}
```
A) Элемент 2 удалится
B) Undefined behavior
C) Ошибка компиляции
D) Исключение runtime_error

### 39. Какой способ лучше для проверки существования ключа?
A) `if (m[key] != default_value)`
B) `if (m.find(key) != m.end())`
C) `if (m.count(key) > 0)`
D) B и C равноценны

### 40. Что выведет этот код?
```cpp
std::map<int, int> m;
auto result = m.insert_or_assign(1, 10);
std::cout << result.second;
```
A) true
B) false
C) 1
D) 10 