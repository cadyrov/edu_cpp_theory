# C++ Core Concepts - От простого к сложному

## 1. Основы типов и значений
### 1.1 [Константность](q_concepts/01_const.md)
- Самая базовая концепция защиты данных
- Простые правила const
- Первый шаг к безопасности кода

### 1.2 [Битовые поля и упаковка данных](q_concepts/02_bitfields.md)
- Базовая работа с памятью
- Простые оптимизации хранения
- Основы выравнивания

### 1.3 [L-value и R-value](q_concepts/03_lvalue_rvalue.md)
- Категории выражений
- Основа для понимания ссылок
- Подготовка к move-семантике

## 2. Базовое управление памятью
### 2.1 [Работа с сырой памятью](q_concepts/04_raw_memory.md)
- new/delete
- Размещение объектов
- Базовые приёмы

### 2.2 [Uninitialized Memory](q_concepts/04_uninitialized_memory.md)
- std::uninitialized_*
- Оптимизация инициализации
- Placement new и POD типы

### 2.3 [RAII](q_concepts/05_raii.md)
- Автоматическое управление ресурсами
- Защита от утечек
- Основа современного C++

### 2.3 [Smart Pointers](q_concepts/06_smart_pointers.md)
- Практическое применение RAII
- Простые случаи использования
- Базовая работа с unique_ptr

## 3. Обработка ошибок и безопасность
### 3.1 [Exception Safety](q_concepts/07_exception_safety.md)
- Базовые гарантии
- Работа с исключениями
- RAII в действии

### 3.2 [Rule of Five](q_concepts/08_rule_of_five.md)
- Полный контроль ресурсов
- Расширение RAII
- Подготовка к move-семантике

## 4. Продвинутая работа с памятью
### 4.1 [Move Semantics](q_concepts/09_move_semantics.md)
- Оптимизация передачи ресурсов
- Применение R-value
- Эффективное управление памятью

### 4.2 [Forward Reference](q_concepts/10_forward_reference.md)
- Perfect forwarding
- Универсальные ссылки
- Продвинутое использование move

## 5. Базовые шаблоны
### 5.1 [Variadic Templates](q_concepts/11_variadic_templates.md)
- Простые вариативные шаблоны
- Базовая обработка параметров
- Основа для метапрограммирования

### 5.2 [Deduction Guides](q_concepts/12_deduction_guides.md)
- Помощь в выводе типов
- Улучшение читаемости
- Упрощение работы с шаблонами

## 6. Современный синтаксис
### 6.1 [Structured Bindings](q_concepts/13_structured_bindings.md)
- Удобная деструктуризация
- Работа с tuple/pair
- Улучшение читаемости

### 6.2 [if/switch с инициализацией](q_concepts/14_init_statements.md)
- Локальные переменные
- Улучшение области видимости
- Современный синтаксис

### 6.3 [Aggregate Initialization](q_concepts/15_aggregate_initialization.md)
- Инициализация структур
- Designated initializers
- Улучшение читаемости

### 6.4 [Inline Variables](q_concepts/16_inline_variables.md)
- Глобальные переменные
- Thread-safe инициализация
- Модульность

### 6.5 [Атрибуты](q_concepts/17_attributes.md)
- Подсказки компилятору
- Улучшение безопасности
- Оптимизации

## 7. Продвинутые шаблоны
### 7.1 [SFINAE и Type Traits](q_concepts/18_sfinae.md)
- Продвинутый выбор перегрузок
- Метапрограммирование
- Проверка типов

### 7.2 [Concepts](q_concepts/19_concepts.md)
- Ограничения шаблонов
- Улучшение ошибок
- Современная замена SFINAE

### 7.3 [Fold Expressions](q_concepts/20_fold_expressions.md)
- Продвинутая работа с паками
- Компактные выражения
- Метапрограммирование

## 8. Многопоточность
### 8.1 [Thread Safety](q_concepts/21_thread_safety.md)
- Базовая синхронизация
- Мьютексы и локи
- Потокобезопасность

### 8.2 [Atomic Operations](q_concepts/22_atomic_operations.md)
- Атомарные операции
- Memory ordering
- Lock-free программирование

## 9. Продвинутое проектирование
### 9.1 [Полиморфизм](q_concepts/23_polymorphism.md)
- Виртуальные функции
- Динамическое поведение
- Проектирование иерархий

### 9.2 [Оптимизации производительности](q_concepts/24_performance.md)
- Продвинутые техники
- Cache-friendly код
- Тонкая настройка