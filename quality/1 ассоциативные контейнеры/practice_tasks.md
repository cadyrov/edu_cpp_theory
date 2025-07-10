# Практические задания по ассоциативным контейнерам

## Задание 1: Частотный анализ текста

**Описание:** Реализуй класс TextAnalyzer, который подсчитывает частоту слов в тексте и позволяет получать статистику.

**Требования:**
- Используй unordered_map для хранения частот
- Игнорируй регистр букв
- Реализуй методы: addText(), getFrequency(), getMostFrequent(), getWordsWithMinFrequency()

**Тесты:**
```cpp
// Тест 1: Основной функционал
TextAnalyzer analyzer;
analyzer.addText("Hello world hello");
assert(analyzer.getFrequency("hello") == 2);
assert(analyzer.getFrequency("world") == 1);

// Тест 2: Игнорирование регистра
analyzer.addText("HELLO Hello");
assert(analyzer.getFrequency("hello") == 4);

// Тест 3: Самое частое слово
assert(analyzer.getMostFrequent() == "hello");

// Тест 4: Пустой текст
TextAnalyzer empty;
assert(empty.getFrequency("test") == 0);

// Тест 5: Слова с минимальной частотой
auto minWords = analyzer.getWordsWithMinFrequency(1);
assert(minWords.size() == 2);

// Тест 6: Добавление нового текста
analyzer.addText("new word new");
assert(analyzer.getFrequency("new") == 2);

// Тест 7: Несуществующее слово
assert(analyzer.getFrequency("nonexistent") == 0);

// Тест 8: Множественные пробелы
analyzer.addText("word    word");
assert(analyzer.getFrequency("word") >= 2);

// Тест 9: Пустая строка
analyzer.addText("");
// Не должно сломаться

// Тест 10: Одно слово
TextAnalyzer single;
single.addText("test");
assert(single.getMostFrequent() == "test");
```

## Задание 2: Кэш с LRU-политикой

**Описание:** Создай LRU (Least Recently Used) кэш используя unordered_map и list для эффективного доступа и обновления.

**Требования:**
- Фиксированный размер кэша
- O(1) для get и put операций
- При переполнении удаляется наименее недавно использованный элемент

**Тесты:**
```cpp
// Тест 1: Базовое добавление и получение
LRUCache<int, string> cache(2);
cache.put(1, "one");
assert(cache.get(1) == "one");

// Тест 2: Переполнение кэша
cache.put(2, "two");
cache.put(3, "three"); // должно вытеснить 1
assert(!cache.contains(1));
assert(cache.contains(2));
assert(cache.contains(3));

// Тест 3: Обновление существующего ключа
cache.put(2, "updated_two");
assert(cache.get(2) == "updated_two");

// Тест 4: LRU порядок
cache.get(2); // делаем 2 недавно использованным
cache.put(4, "four"); // должно вытеснить 3
assert(!cache.contains(3));
assert(cache.contains(2));

// Тест 5: Пустой кэш
LRUCache<int, int> empty(1);
assert(!empty.contains(1));

// Тест 6: Размер кэша 1
LRUCache<int, int> tiny(1);
tiny.put(1, 100);
tiny.put(2, 200);
assert(!tiny.contains(1));
assert(tiny.contains(2));

// Тест 7: Повторное получение
cache.put(5, "five");
cache.put(6, "six");
string val = cache.get(5);
assert(val == "five");

// Тест 8: Множественные обновления
cache.put(5, "five_updated");
cache.put(5, "five_final");
assert(cache.get(5) == "five_final");

// Тест 9: Большой кэш
LRUCache<int, int> big(1000);
for(int i = 0; i < 500; ++i) {
    big.put(i, i * 2);
}
assert(big.get(100) == 200);

// Тест 10: Нулевой размер кэша (edge case)
LRUCache<int, int> zero(0);
zero.put(1, 1);
assert(!zero.contains(1));
```

## Задание 3: Граф и поиск в ширину

**Описание:** Реализуй неориентированный граф с использованием unordered_map<int, unordered_set<int>> и алгоритм BFS для поиска кратчайшего пути.

**Требования:**
- Методы: addEdge(), removeEdge(), hasEdge(), getNeighbors()
- BFS для поиска кратчайшего пути между вершинами
- Возврат пути как vector<int>

**Тесты:**
```cpp
// Тест 1: Добавление ребер
Graph g;
g.addEdge(1, 2);
g.addEdge(2, 3);
assert(g.hasEdge(1, 2));
assert(g.hasEdge(2, 1)); // неориентированный

// Тест 2: Поиск пути
auto path = g.shortestPath(1, 3);
assert(path.size() == 3);
assert(path[0] == 1 && path[2] == 3);

// Тест 3: Нет пути
g.addEdge(4, 5);
auto noPath = g.shortestPath(1, 4);
assert(noPath.empty());

// Тест 4: Удаление ребра
g.removeEdge(2, 3);
assert(!g.hasEdge(2, 3));
auto brokenPath = g.shortestPath(1, 3);
assert(brokenPath.empty());

// Тест 5: Самозацикливание
g.addEdge(1, 1);
assert(g.hasEdge(1, 1));

// Тест 6: Путь к самому себе
auto selfPath = g.shortestPath(1, 1);
assert(selfPath.size() == 1);

// Тест 7: Соседи вершины
g.addEdge(1, 6);
auto neighbors = g.getNeighbors(1);
assert(neighbors.size() >= 2);

// Тест 8: Несуществующая вершина
auto noNeighbors = g.getNeighbors(999);
assert(noNeighbors.empty());

// Тест 9: Сложный граф
for(int i = 0; i < 10; ++i) {
    g.addEdge(i, i + 1);
}
auto longPath = g.shortestPath(0, 10);
assert(longPath.size() == 11);

// Тест 10: Удаление несуществующего ребра
g.removeEdge(100, 200); // не должно сломаться
```

## Задание 4: Группировка объектов

**Описание:** Создай класс ObjectGrouper, который группирует объекты по заданному критерию используя map.

**Требования:**
- Шаблонный класс для любых типов объектов
- Функция-предикат для определения группы
- Методы: addObject(), getGroup(), getAllGroups(), getGroupCount()

**Тесты:**
```cpp
// Тест 1: Группировка чисел по четности
ObjectGrouper<int, bool> grouper([](int x) { return x % 2 == 0; });
grouper.addObject(1);
grouper.addObject(2);
grouper.addObject(3);
grouper.addObject(4);
assert(grouper.getGroup(true).size() == 2); // четные
assert(grouper.getGroup(false).size() == 2); // нечетные

// Тест 2: Группировка строк по длине
ObjectGrouper<string, int> strGrouper([](const string& s) { return s.length(); });
strGrouper.addObject("a");
strGrouper.addObject("bb");
strGrouper.addObject("cc");
strGrouper.addObject("ddd");
assert(strGrouper.getGroup(1).size() == 1);
assert(strGrouper.getGroup(2).size() == 2);

// Тест 3: Количество групп
assert(strGrouper.getGroupCount() == 3);

// Тест 4: Все группы
auto allGroups = strGrouper.getAllGroups();
assert(allGroups.size() == 3);

// Тест 5: Пустая группа
assert(grouper.getGroup(100).empty());

// Тест 6: Добавление в существующую группу
grouper.addObject(6);
assert(grouper.getGroup(true).size() == 3);

// Тест 7: Группировка по первой букве
ObjectGrouper<string, char> charGrouper([](const string& s) { 
    return s.empty() ? '\0' : s[0]; 
});
charGrouper.addObject("apple");
charGrouper.addObject("apricot");
charGrouper.addObject("banana");
assert(charGrouper.getGroup('a').size() == 2);

// Тест 8: Пустой группировщик
ObjectGrouper<int, int> empty([](int x) { return x; });
assert(empty.getGroupCount() == 0);
assert(empty.getAllGroups().empty());

// Тест 9: Одинаковые объекты
grouper.addObject(2);
assert(grouper.getGroup(true).size() == 4);

// Тест 10: Сложная группировка
ObjectGrouper<int, string> complexGrouper([](int x) {
    if (x < 0) return "negative";
    if (x == 0) return "zero";
    return "positive";
});
complexGrouper.addObject(-5);
complexGrouper.addObject(0);
complexGrouper.addObject(10);
assert(complexGrouper.getGroupCount() == 3);
```

## Задание 5: Индекс полнотекстового поиска

**Описание:** Создай простой поисковый индекс, который позволяет быстро находить документы по ключевым словам.

**Требования:**
- unordered_map<string, unordered_set<int>> для инвертированного индекса
- Методы: addDocument(), search(), searchAND(), searchOR()
- Поддержка булевых операторов

**Тесты:**
```cpp
// Тест 1: Добавление документов
SearchIndex index;
index.addDocument(1, "hello world programming");
index.addDocument(2, "world peace programming");
index.addDocument(3, "hello everyone");

// Тест 2: Простой поиск
auto results = index.search("hello");
assert(results.count(1) && results.count(3));
assert(!results.count(2));

// Тест 3: AND поиск
auto andResults = index.searchAND({"hello", "world"});
assert(andResults.size() == 1);
assert(andResults.count(1));

// Тест 4: OR поиск
auto orResults = index.searchOR({"hello", "peace"});
assert(orResults.size() == 3);

// Тест 5: Поиск несуществующего слова
auto noResults = index.search("nonexistent");
assert(noResults.empty());

// Тест 6: Пустой запрос
auto emptyResults = index.searchAND({});
assert(emptyResults.empty());

// Тест 7: Обновление документа
index.addDocument(1, "updated content here");
auto oldResults = index.search("hello");
assert(!oldResults.count(1));

// Тест 8: Регистронезависимый поиск
index.addDocument(4, "HELLO WORLD");
auto caseResults = index.search("hello");
assert(caseResults.count(4));

// Тест 9: Множественные вхождения
index.addDocument(5, "test test test");
auto testResults = index.search("test");
assert(testResults.count(5));

// Тест 10: Сложный AND запрос
index.addDocument(6, "complex search query test");
auto complexResults = index.searchAND({"complex", "search", "test"});
assert(complexResults.count(6));
```

## Задание 6: Кастомный хешер для структуры

**Описание:** Создай структуру Person и эффективный хешер для неё, учитывающий все поля.

**Требования:**
- Структура Person с полями: name, age, email
- Качественная хеш-функция без коллизий
- Реализация operator== для unordered_set

**Тесты:**
```cpp
// Тест 1: Основное хеширование
Person p1{"John", 25, "john@email.com"};
Person p2{"Jane", 30, "jane@email.com"};
PersonHasher hasher;
assert(hasher(p1) != hasher(p2));

// Тест 2: Одинаковые объекты
Person p3{"John", 25, "john@email.com"};
assert(hasher(p1) == hasher(p3));
assert(p1 == p3);

// Тест 3: Использование в unordered_set
unordered_set<Person, PersonHasher> people;
people.insert(p1);
people.insert(p2);
people.insert(p3); // дубликат p1
assert(people.size() == 2);

// Тест 4: Поиск в set
assert(people.find(p1) != people.end());
assert(people.count(p2) == 1);

// Тест 5: Разные хеши для разных полей
Person p4{"John", 26, "john@email.com"}; // другой возраст
assert(hasher(p1) != hasher(p4));

// Тест 6: Разные email
Person p5{"John", 25, "john2@email.com"};
assert(hasher(p1) != hasher(p5));

// Тест 7: Пустые поля
Person empty{"", 0, ""};
assert(hasher(empty) != hasher(p1));

// Тест 8: Использование в unordered_map
unordered_map<Person, string, PersonHasher> personData;
personData[p1] = "data1";
personData[p2] = "data2";
assert(personData.size() == 2);

// Тест 9: Качество хеш-функции (низкая коллизия)
set<size_t> hashes;
for(int i = 0; i < 1000; ++i) {
    Person p{"Person" + to_string(i), i, "email" + to_string(i)};
    hashes.insert(hasher(p));
}
// Должно быть мало коллизий
assert(hashes.size() > 990);

// Тест 10: Стабильность хеша
size_t hash1 = hasher(p1);
size_t hash2 = hasher(p1);
assert(hash1 == hash2);
```

## Задание 7: Многоуровневая группировка

**Описание:** Реализуй систему для многоуровневой группировки данных с использованием вложенных map.

**Требования:**
- Группировка по нескольким критериям одновременно
- map<Key1, map<Key2, vector<Value>>>
- Методы для добавления и извлечения на разных уровнях

**Тесты:**
```cpp
// Тест 1: Двухуровневая группировка
MultiLevelGrouper<string, int, string> grouper;
grouper.add("fruits", 1, "apple");
grouper.add("fruits", 1, "banana");
grouper.add("fruits", 2, "orange");
grouper.add("vegetables", 1, "carrot");

// Тест 2: Получение по первому уровню
auto fruits = grouper.getLevel1("fruits");
assert(fruits.size() == 2); // категории 1 и 2

// Тест 3: Получение по двум уровням
auto category1Fruits = grouper.getLevel2("fruits", 1);
assert(category1Fruits.size() == 2);

// Тест 4: Несуществующая категория
auto empty = grouper.getLevel1("nonexistent");
assert(empty.empty());

// Тест 5: Все первые ключи
auto allKeys = grouper.getAllLevel1Keys();
assert(allKeys.size() == 2);

// Тест 6: Количество элементов
assert(grouper.countLevel2("fruits", 1) == 2);
assert(grouper.countLevel1("vegetables") == 1);

// Тест 7: Удаление элемента
grouper.remove("fruits", 1, "apple");
assert(grouper.countLevel2("fruits", 1) == 1);

// Тест 8: Удаление всей подгруппы
grouper.removeLevel2("fruits", 2);
auto fruitsAfter = grouper.getLevel1("fruits");
assert(fruitsAfter.size() == 1);

// Тест 9: Проверка существования
assert(grouper.exists("vegetables", 1, "carrot"));
assert(!grouper.exists("fruits", 1, "apple"));

// Тест 10: Сложная структура
for(int i = 0; i < 10; ++i) {
    for(int j = 0; j < 5; ++j) {
        grouper.add("level" + to_string(i), j, "item" + to_string(j));
    }
}
assert(grouper.getAllLevel1Keys().size() == 12); // 2 + 10
```

## Задание 8: Конфигурационный менеджер

**Описание:** Создай систему управления конфигурацией с поддержкой вложенных секций и различных типов значений.

**Требования:**
- map<string, map<string, string>> для секций и параметров
- Методы для get/set с преобразованием типов
- Поддержка defaults и validation

**Тесты:**
```cpp
// Тест 1: Установка и получение строк
ConfigManager config;
config.setString("database", "host", "localhost");
assert(config.getString("database", "host") == "localhost");

// Тест 2: Работа с числами
config.setInt("database", "port", 5432);
assert(config.getInt("database", "port") == 5432);

// Тест 3: Булевы значения
config.setBool("features", "debug", true);
assert(config.getBool("features", "debug") == true);

// Тест 4: Значения по умолчанию
assert(config.getInt("missing", "value", 42) == 42);
assert(config.getString("missing", "str", "default") == "default");

// Тест 5: Проверка существования
assert(config.hasSection("database"));
assert(config.hasKey("database", "host"));
assert(!config.hasKey("database", "missing"));

// Тест 6: Получение всех ключей секции
auto dbKeys = config.getKeys("database");
assert(dbKeys.size() == 2);

// Тест 7: Удаление ключа
config.removeKey("database", "port");
assert(!config.hasKey("database", "port"));

// Тест 8: Удаление секции
config.removeSection("features");
assert(!config.hasSection("features"));

// Тест 9: Загрузка из строки
string configStr = "[server]\nport=8080\nhost=0.0.0.0\n[app]\ndebug=true";
config.loadFromString(configStr);
assert(config.getInt("server", "port") == 8080);

// Тест 10: Сохранение в строку
string saved = config.saveToString();
assert(!saved.empty());
ConfigManager loaded;
loaded.loadFromString(saved);
assert(loaded.getString("server", "host") == "0.0.0.0");
```

## Задание 9: Система счетчиков с агрегацией

**Описание:** Реализуй систему счетчиков, которая поддерживает инкремент, декремент и различные виды агрегации.

**Требования:**
- unordered_map<string, int64_t> для хранения счетчиков
- Методы для агрегации: sum, average, min, max
- Поддержка групп счетчиков

**Тесты:**
```cpp
// Тест 1: Базовые операции
CounterSystem counters;
counters.increment("requests");
counters.increment("requests", 5);
assert(counters.getValue("requests") == 6);

// Тест 2: Декремент
counters.decrement("requests", 2);
assert(counters.getValue("requests") == 4);

// Тест 3: Установка значения
counters.setValue("errors", 10);
assert(counters.getValue("errors") == 10);

// Тест 4: Группы счетчиков
counters.addToGroup("http", "requests");
counters.addToGroup("http", "errors");
counters.setValue("responses", 100);
counters.addToGroup("http", "responses");

// Тест 5: Сумма группы
int64_t httpSum = counters.groupSum("http");
assert(httpSum == 114); // 4 + 10 + 100

// Тест 6: Среднее значение группы
double httpAvg = counters.groupAverage("http");
assert(abs(httpAvg - 38.0) < 0.1);

// Тест 7: Минимум и максимум группы
assert(counters.groupMin("http") == 4);
assert(counters.groupMax("http") == 100);

// Тест 8: Счетчики с префиксом
counters.setValue("user.login", 50);
counters.setValue("user.logout", 45);
auto userCounters = counters.getByPrefix("user.");
assert(userCounters.size() == 2);

// Тест 9: Сброс счетчика
counters.reset("errors");
assert(counters.getValue("errors") == 0);

// Тест 10: Сброс группы
counters.resetGroup("http");
assert(counters.groupSum("http") == 0);
```

## Задание 10: Система кэширования с TTL

**Описание:** Создай кэш с поддержкой времени жизни (TTL) для элементов.

**Требования:**
- unordered_map для хранения значений и времени истечения
- Автоматическое удаление устаревших элементов
- Методы: put, get, cleanup, size

**Тесты:**
```cpp
// Тест 1: Базовое кэширование с TTL
TTLCache<string, int> cache;
auto now = chrono::steady_clock::now();
cache.put("key1", 100, chrono::seconds(1));
assert(cache.get("key1").has_value());
assert(cache.get("key1").value() == 100);

// Тест 2: Истечение TTL
this_thread::sleep_for(chrono::milliseconds(1100));
assert(!cache.get("key1").has_value());

// Тест 3: Разное время жизни
cache.put("short", 1, chrono::milliseconds(100));
cache.put("long", 2, chrono::seconds(10));
this_thread::sleep_for(chrono::milliseconds(200));
assert(!cache.get("short").has_value());
assert(cache.get("long").has_value());

// Тест 4: Обновление TTL
cache.put("update", 10, chrono::milliseconds(100));
cache.put("update", 20, chrono::seconds(1)); // обновляем TTL
this_thread::sleep_for(chrono::milliseconds(200));
assert(cache.get("update").has_value());
assert(cache.get("update").value() == 20);

// Тест 5: Размер кэша
cache.put("size1", 1, chrono::seconds(10));
cache.put("size2", 2, chrono::seconds(10));
assert(cache.size() >= 2);

// Тест 6: Ручная очистка
cache.put("cleanup1", 1, chrono::milliseconds(1));
this_thread::sleep_for(chrono::milliseconds(10));
size_t oldSize = cache.size();
cache.cleanup();
assert(cache.size() < oldSize);

// Тест 7: Множественные элементы
for(int i = 0; i < 100; ++i) {
    cache.put("item" + to_string(i), i, chrono::seconds(5));
}
assert(cache.size() >= 100);

// Тест 8: Проверка has_value
cache.put("check", 42, chrono::seconds(1));
assert(cache.contains("check"));
assert(!cache.contains("nonexistent"));

// Тест 9: Нулевое TTL
cache.put("zero", 0, chrono::seconds(0));
assert(!cache.get("zero").has_value());

// Тест 10: Большое TTL
cache.put("forever", 999, chrono::hours(24));
assert(cache.get("forever").has_value());
assert(cache.get("forever").value() == 999);
``` 