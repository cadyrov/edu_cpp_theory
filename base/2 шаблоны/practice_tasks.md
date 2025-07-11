# Практические задания: Шаблоны C++

## Задание 1: Generic Container
**Описание:** Реализуйте шаблонный контейнер `SafeArray<T, N>` для хранения N элементов типа T с проверкой границ.

**Требования:**
- Шаблонные параметры: тип элемента T и размер N
- Методы: at(), size(), fill(), operator[]
- Исключение при выходе за границы
- Поддержка итераторов begin()/end()

**Тесты:**
1. Создание SafeArray<int, 5> и заполнение значениями
2. Проверка исключения при обращении к элементу с индексом >= N
3. Использование fill() для заполнения всех элементов одним значением
4. Итерирование через весь контейнер с помощью range-based for
5. Создание SafeArray<std::string, 3> и работа со строками
6. Проверка operator[] для чтения и записи
7. Тест с SafeArray<double, 1> (граничный случай)
8. Проверка const-корректности методов
9. Копирование SafeArray в другой SafeArray того же типа
10. Работа с пользовательским типом (структура Point)

## Задание 2: Template Function Overloading
**Описание:** Создайте набор шаблонных функций `convert()` для преобразования между различными типами с использованием специализаций и SFINAE.

**Требования:**
- Общий шаблон convert<To, From>(from)
- Специализации для string ↔ число
- SFINAE для ограничения типов
- Обработка ошибок преобразования
- Поддержка пользовательских типов

**Тесты:**
1. Преобразование int в string
2. Преобразование string в double
3. Преобразование float в int с потерей точности
4. Обработка некорректной строки при преобразовании в число
5. Конвертация между пользовательскими типами через operator
6. Проверка SFINAE - функция недоступна для несовместимых типов
7. Преобразование char в int
8. Конвертация bool в string ("true"/"false")
9. Преобразование string в bool
10. Тест производительности для массовых преобразований

## Задание 3: Template Metaprogramming Calculator
**Описание:** Реализуйте compile-time калькулятор с использованием template metaprogramming для вычисления математических функций.

**Требования:**
- Вычисление факториала на этапе компиляции
- Вычисление чисел Фибоначчи
- Проверка простых чисел
- Вычисление степени числа
- Все вычисления должны быть constexpr

**Тесты:**
1. Вычисление factorial<5>() должно дать 120
2. Вычисление fibonacci<10>() должно дать 55
3. is_prime<17>() должно быть true
4. is_prime<16>() должно быть false
5. power<2, 8>() должно дать 256
6. factorial<0>() должно дать 1 (граничный случай)
7. fibonacci<0>() и fibonacci<1>() должны дать 0 и 1
8. Большие значения - factorial<12>()
9. Проверка что результат вычисляется во время компиляции (constexpr)
10. Комбинированные вычисления: power<fibonacci<5>(), 2>()

## Задание 4: Smart Pointer Template
**Описание:** Создайте упрощенный smart pointer `UniquePtr<T>` с move semantics и custom deleter.

**Требования:**
- Управление временем жизни объекта
- Move constructor и move assignment
- Запрет копирования
- Custom deleter как шаблонный параметр
- Методы get(), release(), reset()

**Тесты:**
1. Создание UniquePtr<int> и проверка владения ресурсом
2. Move constructor - передача владения
3. Move assignment между различными UniquePtr
4. Автоматическое освобождение ресурса при выходе из области видимости
5. Использование custom deleter для массивов
6. Метод release() должен отдать владение без удаления
7. Метод reset() с новым ресурсом
8. Работа с пользовательскими классами
9. Проверка что копирование запрещено (не компилируется)
10. UniquePtr<void> с custom deleter

## Задание 5: Type Traits Implementation
**Описание:** Реализуйте собственные type traits для анализа типов во время компиляции.

**Требования:**
- is_pointer<T>, is_array<T>, is_const<T>
- remove_pointer<T>, remove_const<T>, add_pointer<T>
- is_same<T1, T2>, conditional<bool, T1, T2>
- Поддержка CV-qualifiers
- Работа с составными типами

**Тесты:**
1. is_pointer<int*>::value должно быть true
2. is_pointer<int>::value должно быть false
3. remove_pointer<int*>::type должно быть int
4. is_const<const int>::value должно быть true
5. remove_const<const int>::type должно быть int
6. is_same<int, int>::value должно быть true
7. conditional<true, int, double>::type должно быть int
8. is_array<int[5]>::value должно быть true
9. Работа с указателями на функции
10. Сложные составные типы: const int* const

## Задание 6: Variadic Template Logger
**Описание:** Создайте логгер с поддержкой variadic templates для форматированного вывода различных типов данных.

**Требования:**
- Функция log(level, format, args...)
- Perfect forwarding для аргументов
- Различные уровни логирования
- Форматирование с типобезопасностью
- Поддержка пользовательских типов

**Тесты:**
1. Логирование простых типов: log(INFO, "Value: %", 42)
2. Логирование нескольких аргументов разных типов
3. Perfect forwarding - rvalue и lvalue аргументы
4. Различные уровни логирования (DEBUG, INFO, ERROR)
5. Логирование пользовательских объектов с operator<<
6. Вложенные вызовы с другими variadic функциями
7. Пустой список аргументов
8. Очень большое количество аргументов (>10)
9. Форматирование строк с escape-последовательностями
10. Thread-safety при одновременном логировании

## Задание 7: Template-based State Machine
**Описание:** Реализуйте compile-time state machine используя template metaprogramming.

**Требования:**
- Состояния как типы
- Переходы между состояниями на compile-time
- Валидация корректных переходов
- Хранение текущего состояния
- Type-safe операции

**Тесты:**
1. Создание state machine с начальным состоянием
2. Валидный переход из одного состояния в другое
3. Попытка невалидного перехода (ошибка компиляции)
4. Цепочка переходов: A → B → C
5. Проверка текущего состояния
6. State machine с циклическими переходами
7. Разные state machines с одинаковыми состояниями
8. Сохранение истории переходов
9. Условные переходы в зависимости от параметров
10. Финальные состояния без исходящих переходов

## Задание 8: Generic Algorithm Library
**Описание:** Создайте библиотеку алгоритмов работающих с любыми контейнерами через итераторы.

**Требования:**
- find_if, for_each, transform, accumulate
- Работа с любыми итераторами
- Поддержка лямбда-функций и function objects
- Type deduction для результатов
- Exception safety

**Тесты:**
1. find_if в std::vector<int> с лямбда-предикатом
2. for_each для печати элементов любого контейнера
3. transform из vector<int> в vector<string>
4. accumulate для подсчета суммы/произведения
5. Работа с пользовательскими итераторами
6. Алгоритм на пустом контейнере
7. find_if не находит элемент (возврат end iterator)
8. transform с разными типами входа и выхода
9. accumulate с пользовательской функцией объединения
10. Композиция алгоритмов: transform → accumulate

## Задание 9: Template Expression Templates
**Описание:** Реализуйте expression templates для ленивых вычислений арифметических выражений с векторами.

**Требования:**
- Класс Vector<T> с арифметическими операциями
- Отложенные вычисления до присваивания
- Элиминация временных объектов
- Поддержка сложных выражений
- Оптимизация производительности

**Тесты:**
1. Простое сложение двух векторов
2. Сложное выражение: a + b * c - d
3. Скалярные операции: vector * scalar
4. Проверка что временные объекты не создаются
5. Вычисления с векторами разных размеров (ошибка)
6. Присваивание результата тому же вектору
7. Цепочка операций присваивания
8. Производительность vs обычные вычисления
9. Работа с различными арифметическими типами
10. Memory efficiency - no extra allocations

## Задание 10: Policy-Based Design
**Описание:** Создайте гибкий класс `SmartContainer` использующий policy-based design для настройки поведения.

**Требования:**
- Storage policy (vector, deque, list)
- Allocation policy (standard, pool, custom)
- Thread safety policy (single-thread, multi-thread)
- Error handling policy (exceptions, error codes)
- Композиция политик через шаблоны

**Тесты:**
1. SmartContainer с vector storage и standard allocator
2. SmartContainer с deque storage и pool allocator  
3. Thread-safe версия с mutex protection
4. Error handling через exceptions vs error codes
5. Смешивание различных политик
6. Производительность разных storage policies
7. Memory usage с различными allocation policies
8. Concurrent access в multi-threaded режиме
9. Кастомные политики определенные пользователем
10. Совместимость политик - некоторые комбинации невозможны

---

## Критерии оценки

**Отлично (5):**
- Все тесты проходят
- Код следует лучшим практикам
- Эффективное использование шаблонов
- Правильная обработка ошибок
- Отличная производительность

**Хорошо (4):**
- 8-9 тестов проходят
- Код в основном корректен
- Небольшие недочеты в дизайне
- Базовая обработка ошибок

**Удовлетворительно (3):**
- 6-7 тестов проходят
- Код работает но есть проблемы
- Неэффективное использование шаблонов
- Минимальная обработка ошибок

**Неудовлетворительно (2):**
- Менее 6 тестов проходят
- Серьезные ошибки в коде
- Неправильное понимание шаблонов 