# Практические задания: Ассоциативные контейнеры C++

## Задание 1: Телефонная книга с расширенной функциональностью
**Описание:** Создайте продвинутую телефонную книгу используя std::map и std::multimap для хранения контактов с возможностью группировки и поиска.

**Требования:**
- Класс PhoneBook с методами добавления, удаления, поиска контактов
- Поддержка нескольких номеров для одного контакта (multimap)
- Группировка контактов по категориям
- Поиск по частичному совпадению имени
- Экспорт/импорт данных

**Тесты:**
1. Добавление контакта с одним номером телефона
2. Добавление нескольких номеров для одного контакта
3. Поиск контакта по точному имени
4. Поиск контактов по частичному совпадению имени
5. Удаление конкретного номера у контакта
6. Удаление всех номеров контакта
7. Группировка контактов (семья, работа, друзья)
8. Получение всех контактов определенной группы
9. Экспорт всех контактов в текстовый файл
10. Импорт контактов из файла с проверкой дубликатов

## Задание 2: Кэш-система с LRU политикой
**Описание:** Реализуйте LRU (Least Recently Used) кэш используя комбинацию std::unordered_map и std::list для эффективного хранения и доступа.

**Требования:**
- Фиксированный размер кэша
- O(1) время доступа к элементам
- Автоматическое вытеснение наименее используемых элементов
- Статистика попаданий и промахов
- Потокобезопасность (optional)

**Тесты:**
1. Создание кэша с заданным размером
2. Добавление элементов до заполнения кэша
3. Вытеснение старого элемента при добавлении нового
4. Обновление позиции элемента при доступе
5. Получение статистики hit/miss ratio
6. Очистка кэша
7. Изменение размера кэша с сохранением актуальных элементов
8. Проверка корректности LRU порядка
9. Работа с различными типами ключей и значений
10. Производительность O(1) для операций get/put

## Задание 3: Частотный анализатор текста
**Описание:** Создайте анализатор для подсчета частоты слов, символов и n-грамм в тексте используя различные ассоциативные контейнеры.

**Требования:**
- Подсчет частоты слов (std::map)
- Подсчет частоты символов (std::unordered_map)
- Анализ n-грамм (биграммы, триграммы)
- Фильтрация стоп-слов
- Вывод топ-N наиболее частых элементов

**Тесты:**
1. Подсчет частоты слов в простом тексте
2. Игнорирование регистра при подсчете
3. Обработка знаков препинания
4. Фильтрация стоп-слов (предлоги, союзы)
5. Анализ биграмм (пары соседних слов)
6. Анализ триграмм (тройки соседних слов)
7. Топ-10 наиболее частых слов
8. Статистика по длине слов
9. Анализ больших текстов (производительность)
10. Сравнение частот между разными текстами

## Задание 4: Граф и алгоритмы поиска пути
**Описание:** Реализуйте представление графа используя std::map и std::set, с алгоритмами поиска кратчайшего пути.

**Требования:**
- Класс Graph с методами добавления вершин и рёбер
- Представление с помощью списка смежности (map<vertex, set<vertex>>)
- Алгоритм поиска в ширину (BFS)
- Алгоритм поиска в глубину (DFS)
- Алгоритм Дейкстры для взвешенного графа

**Тесты:**
1. Создание графа и добавление вершин
2. Добавление рёбер между вершинами
3. Проверка существования пути между вершинами
4. BFS поиск кратчайшего пути (невзвешенный граф)
5. DFS обход всех достижимых вершин
6. Алгоритм Дейкстры для взвешенного графа
7. Обнаружение циклов в графе
8. Поиск компонент связности
9. Топологическая сортировка (для DAG)
10. Производительность алгоритмов на больших графах

## Задание 5: Индексированная база данных
**Описание:** Создайте простую in-memory базу данных с индексами используя std::map и std::multimap для быстрого поиска записей.

**Требования:**
- Структура Record с различными полями
- Первичный индекс по ID (std::map)
- Вторичные индексы по другим полям (std::multimap)
- SQL-подобные операции SELECT с условиями
- Поддержка составных индексов

**Тесты:**
1. Создание таблицы с первичным ключом
2. Вставка записей с автоматическим обновлением индексов
3. Поиск записи по первичному ключу
4. Поиск записей по вторичному индексу
5. Диапазонный поиск (между значениями)
6. UPDATE записи с обновлением индексов
7. DELETE записи с очисткой индексов
8. Составной индекс по нескольким полям
9. Агрегатные функции с использованием индексов
10. Производительность индексированного vs линейного поиска

## Задание 6: Система конфигурации с иерархией
**Описание:** Реализуйте систему управления конфигурацией с поддержкой иерархических настроек и наследования используя std::map.

**Требования:**
- Иерархическая структура конфигурации (разделы и подразделы)
- Наследование настроек от родительских разделов
- Разные типы значений (string, int, bool, double)
- Валидация значений
- Сохранение и загрузка из файла

**Тесты:**
1. Создание простой конфигурации с парами ключ-значение
2. Создание иерархической структуры разделов
3. Наследование значений от родительского раздела
4. Переопределение унаследованных значений
5. Валидация типов значений при установке
6. Поиск настройки по полному пути
7. Получение всех настроек из раздела
8. Сохранение конфигурации в файл (INI-формат)
9. Загрузка конфигурации из файла
10. Merge двух конфигураций с разрешением конфликтов

## Задание 7: Интерпретатор выражений с переменными
**Описание:** Создайте калькулятор математических выражений с поддержкой переменных используя std::map для хранения значений переменных.

**Требования:**
- Парсинг арифметических выражений
- Поддержка переменных (std::map<string, double>)
- Функции (sin, cos, sqrt, etc.)
- Присваивание значений переменным
- Вычисление выражений с приоритетом операций

**Тесты:**
1. Вычисление простых арифметических выражений
2. Использование переменных в выражениях
3. Присваивание значений переменным
4. Приоритет арифметических операций
5. Поддержка скобок для изменения приоритета
6. Математические функции (sin, cos, sqrt)
7. Обработка ошибок (деление на ноль, неизвестная переменная)
8. Сложные выражения с множественными переменными
9. Обновление значений переменных и пересчет
10. Производительность парсинга и вычислений

## Задание 8: Bloom Filter с подсчетом коллизий
**Описание:** Реализуйте Bloom Filter для быстрой проверки принадлежности элементов множеству, с анализом коллизий используя std::set для проверки.

**Требования:**
- Класс BloomFilter с настраиваемым размером и количеством хеш-функций
- Методы add, contains, clear
- Различные хеш-функции для минимизации коллизий
- Статистика ложных срабатываний
- Оптимальный выбор параметров

**Тесты:**
1. Создание Bloom Filter с заданными параметрами
2. Добавление элементов в фильтр
3. Проверка принадлежности добавленных элементов
4. Проверка отсутствующих элементов (могут быть ложные срабатывания)
5. Статистика ложных срабатываний
6. Влияние количества хеш-функций на точность
7. Влияние размера фильтра на точность
8. Оптимальные параметры для заданного количества элементов
9. Сравнение с обычным std::set по памяти и скорости
10. Тестирование на больших объемах данных

## Задание 9: Система событий с подписчиками
**Описание:** Создайте event-driven систему где компоненты могут подписываться на события, используя std::multimap для хранения подписок.

**Требования:**
- Регистрация слушателей событий по типам
- Публикация событий всем подписчикам
- Приоритеты обработчиков
- Фильтрация событий по условиям
- Асинхронная обработка событий (optional)

**Тесты:**
1. Регистрация простого обработчика события
2. Публикация события и вызов всех подписчиков
3. Несколько обработчиков для одного типа события
4. Приоритеты обработчиков (порядок вызова)
5. Отписка конкретного обработчика
6. Фильтрация событий по условиям
7. Каскадная публикация событий
8. Обработка исключений в обработчиках
9. Статистика обработанных событий
10. Производительность при большом количестве подписчиков

## Задание 10: Распределенная хеш-таблица (DHT)
**Описание:** Реализуйте упрощенную версию распределенной хеш-таблицы с консистентным хешированием для равномерного распределения данных.

**Требования:**
- Несколько виртуальных узлов (std::map<hash, node_id>)
- Консистентное хеширование для распределения ключей
- Операции get, put, remove с маршрутизацией к правильному узлу
- Балансировка при добавлении/удалении узлов
- Репликация данных для надежности

**Тесты:**
1. Создание DHT с несколькими узлами
2. Добавление ключей с равномерным распределением
3. Поиск ключей на правильных узлах
4. Добавление нового узла с перебалансировкой
5. Удаление узла с перераспределением данных
6. Репликация данных на соседних узлах
7. Обработка отказа узла
8. Консистентность данных при изменении топологии
9. Статистика распределения нагрузки
10. Производительность операций в большой сети

---

## Критерии оценки

**Отлично (5):**
- Все тесты проходят
- Эффективное использование подходящих контейнеров
- Правильная работа с итераторами
- Оптимальная временная сложность операций
- Обработка граничных случаев

**Хорошо (4):**
- 8-9 тестов проходят
- Корректный выбор контейнеров для задач
- Основная функциональность работает
- Минимальные проблемы с производительностью

**Удовлетворительно (3):**
- 6-7 тестов проходят
- Использование контейнеров не всегда оптимально
- Основные операции работают
- Неэффективные алгоритмы

**Неудовлетворительно (2):**
- Менее 6 тестов проходят
- Неправильный выбор контейнеров
- Серьезные ошибки в логике
- Неработающая функциональность

## Полезные советы

### Выбор контейнера:
```cpp
// std::map - сортированные ключи, O(log n) операции
std::map<std::string, int> sorted_data;

// std::unordered_map - быстрый доступ O(1) в среднем
std::unordered_map<std::string, int> fast_lookup;

// std::multimap - несколько значений для одного ключа
std::multimap<std::string, int> multiple_values;

// std::set - уникальные отсортированные элементы
std::set<int> unique_sorted;
```

### Эффективный поиск:
```cpp
// Используйте find() вместо count() + operator[]
auto it = map.find(key);
if (it != map.end()) {
    // элемент найден, используем it->second
}

// equal_range для multimap
auto range = multimap.equal_range(key);
for (auto it = range.first; it != range.second; ++it) {
    // обработка всех значений для ключа
}
```

### Кастомные компараторы:
```cpp
// Для std::map с кастомной сортировкой
struct CustomCompare {
    bool operator()(const std::string& a, const std::string& b) const {
        return a.length() < b.length(); // сортировка по длине
    }
};
std::map<std::string, int, CustomCompare> length_sorted_map;

// Для std::unordered_map с кастомным хешем
struct CustomHash {
    std::size_t operator()(const std::string& s) const {
        return std::hash<std::string>{}(s) ^ 0xAAAAAAAA;
    }
};
std::unordered_map<std::string, int, CustomHash> custom_hash_map;
```

### Оптимизация производительности:
```cpp
// Используйте emplace вместо insert для конструирования на месте
map.emplace(key, value);

// reserve для unordered_map при известном размере
unordered_map.reserve(expected_size);

// Используйте const auto& в range-based for
for (const auto& [key, value] : map) {
    // обработка без копирования
}
``` 