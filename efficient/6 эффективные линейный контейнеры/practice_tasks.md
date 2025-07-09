# Практические задания: Эффективные линейные контейнеры

## Задание 1: Эффективный буфер данных

**Описание:** Реализуйте класс `DataBuffer`, который может эффективно добавлять данные в конец и удалять данные из начала. Класс должен автоматически выбирать оптимальный контейнер на основе паттерна использования.

**Требования:**
- Методы: `push_back()`, `pop_front()`, `size()`, `empty()`
- Автоматическое переключение между vector и deque
- Отслеживание статистики операций

**Тесты:**
```cpp
void test_data_buffer() {
    DataBuffer<int> buffer;
    
    // Тест 1: Базовые операции
    assert(buffer.empty());
    buffer.push_back(1);
    buffer.push_back(2);
    assert(buffer.size() == 2);
    
    // Тест 2: Pop front
    buffer.pop_front();
    assert(buffer.size() == 1);
    
    // Тест 3: Смешанные операции
    for (int i = 0; i < 100; ++i) {
        buffer.push_back(i);
    }
    for (int i = 0; i < 50; ++i) {
        buffer.pop_front();
    }
    assert(buffer.size() == 51);
    
    // Тест 4: Очистка
    buffer.clear();
    assert(buffer.empty());
    
    // Тест 5: Большой объем данных
    for (int i = 0; i < 10000; ++i) {
        buffer.push_back(i);
        if (i % 2 == 0) buffer.pop_front();
    }
    
    // Тест 6: Проверка контейнера
    assert(buffer.get_container_type() == "deque"); // Должен выбрать deque
    
    // Тест 7: Только push_back
    DataBuffer<int> vector_buffer;
    for (int i = 0; i < 1000; ++i) {
        vector_buffer.push_back(i);
    }
    assert(vector_buffer.get_container_type() == "vector");
    
    // Тест 8: Статистика
    auto stats = buffer.get_statistics();
    assert(stats.push_back_count > 0);
    assert(stats.pop_front_count > 0);
    
    // Тест 9: Копирование
    DataBuffer<int> copy_buffer = buffer;
    assert(copy_buffer.size() == buffer.size());
    
    // Тест 10: Итераторы
    int sum = 0;
    for (const auto& value : buffer) {
        sum += value;
    }
    assert(sum > 0);
}
```

## Задание 2: Безопасный строковый парсер

**Описание:** Создайте класс `StringParser`, который использует `string_view` для эффективного разбора строк без копирования данных.

**Требования:**
- Методы: `split()`, `find_word()`, `extract_numbers()`, `validate_lifetime()`
- Безопасная работа с временными объектами
- Поддержка различных разделителей

**Тесты:**
```cpp
void test_string_parser() {
    const std::string text = "Hello,World;123:456 test";
    StringParser parser(text);
    
    // Тест 1: Разделение по запятой
    auto words = parser.split(',');
    assert(words.size() == 2);
    assert(words[0] == "Hello");
    assert(words[1] == "World;123:456 test");
    
    // Тест 2: Разделение по нескольким символам
    auto parts = parser.split(",;: ");
    assert(parts.size() == 5);
    assert(parts[0] == "Hello");
    assert(parts[1] == "World");
    assert(parts[2] == "123");
    assert(parts[3] == "456");
    assert(parts[4] == "test");
    
    // Тест 3: Поиск слова
    auto pos = parser.find_word("World");
    assert(pos != std::string_view::npos);
    
    // Тест 4: Извлечение чисел
    auto numbers = parser.extract_numbers();
    assert(numbers.size() == 2);
    assert(numbers[0] == 123);
    assert(numbers[1] == 456);
    
    // Тест 5: Валидация времени жизни
    assert(parser.validate_lifetime());
    
    // Тест 6: Пустая строка
    StringParser empty_parser("");
    assert(empty_parser.split(',').empty());
    
    // Тест 7: Строка без разделителей
    StringParser single_parser("NoDelimiters");
    auto single_result = single_parser.split(',');
    assert(single_result.size() == 1);
    assert(single_result[0] == "NoDelimiters");
    
    // Тест 8: Множественные разделители подряд
    StringParser multi_parser("a,,b;;c");
    auto multi_result = multi_parser.split(",;");
    assert(multi_result.size() == 3);
    
    // Тест 9: Начало и конец строки с разделителями
    StringParser edge_parser(",test,");
    auto edge_result = edge_parser.split(",");
    assert(edge_result.size() == 1);
    assert(edge_result[0] == "test");
    
    // Тест 10: Большая строка
    std::string big_text(10000, 'a');
    big_text += ",";
    big_text += std::string(10000, 'b');
    StringParser big_parser(big_text);
    auto big_result = big_parser.split(",");
    assert(big_result.size() == 2);
}
```

## Задание 3: Оптимизированный стек с историей

**Описание:** Реализуйте класс `HistoryStack`, который поддерживает операции стека и позволяет откатывать операции назад.

**Требования:**
- Методы: `push()`, `pop()`, `top()`, `undo()`, `redo()`, `clear_history()`
- Ограничение на размер истории
- Эффективное использование памяти

**Тесты:**
```cpp
void test_history_stack() {
    HistoryStack<int> stack(5); // история на 5 операций
    
    // Тест 1: Базовые операции
    stack.push(1);
    stack.push(2);
    assert(stack.top() == 2);
    assert(stack.size() == 2);
    
    // Тест 2: Pop операция
    stack.pop();
    assert(stack.top() == 1);
    
    // Тест 3: Undo операция
    stack.undo();
    assert(stack.top() == 2);
    assert(stack.size() == 2);
    
    // Тест 4: Redo операция
    stack.redo();
    assert(stack.top() == 1);
    
    // Тест 5: Множественные undo/redo
    stack.push(3);
    stack.push(4);
    stack.undo();
    stack.undo();
    assert(stack.top() == 1);
    stack.redo();
    assert(stack.top() == 3);
    
    // Тест 6: Превышение лимита истории
    for (int i = 0; i < 10; ++i) {
        stack.push(i);
    }
    assert(stack.get_history_size() <= 5);
    
    // Тест 7: Очистка истории
    stack.clear_history();
    assert(!stack.can_undo());
    assert(!stack.can_redo());
    
    // Тест 8: Пустой стек
    HistoryStack<int> empty_stack;
    assert(empty_stack.empty());
    assert(!empty_stack.can_undo());
    
    // Тест 9: Исключения
    try {
        empty_stack.top();
        assert(false); // Не должно дойти сюда
    } catch (const std::exception&) {
        // Ожидаемое исключение
    }
    
    // Тест 10: Состояние после операций
    stack.push(100);
    auto state = stack.get_state();
    assert(state.size > 0);
    assert(state.can_undo);
}
```

## Задание 4: Эффективный кольцевой буфер

**Описание:** Создайте класс `CircularBuffer` с фиксированным размером, который эффективно работает с данными в кольцевом порядке.

**Требования:**
- Методы: `push()`, `pop()`, `full()`, `empty()`, `capacity()`
- Автоматическая перезапись старых данных
- Итераторы для обхода

**Тесты:**
```cpp
void test_circular_buffer() {
    CircularBuffer<int> buffer(5);
    
    // Тест 1: Базовые операции
    assert(buffer.empty());
    assert(buffer.capacity() == 5);
    
    // Тест 2: Заполнение буфера
    for (int i = 1; i <= 5; ++i) {
        buffer.push(i);
    }
    assert(buffer.full());
    assert(buffer.size() == 5);
    
    // Тест 3: Перезапись данных
    buffer.push(6);
    assert(buffer.front() == 2); // Первый элемент перезаписан
    
    // Тест 4: Pop операция
    int value = buffer.pop();
    assert(value == 2);
    assert(buffer.size() == 4);
    
    // Тест 5: Итераторы
    std::vector<int> values;
    for (const auto& val : buffer) {
        values.push_back(val);
    }
    assert(values.size() == 4);
    
    // Тест 6: Очистка
    buffer.clear();
    assert(buffer.empty());
    
    // Тест 7: Частичное заполнение
    buffer.push(10);
    buffer.push(20);
    assert(buffer.size() == 2);
    assert(buffer.front() == 10);
    assert(buffer.back() == 20);
    
    // Тест 8: Множественные циклы
    for (int i = 0; i < 20; ++i) {
        buffer.push(i);
    }
    assert(buffer.size() == 5);
    
    // Тест 9: Доступ по индексу
    assert(buffer[0] == buffer.front());
    assert(buffer[buffer.size()-1] == buffer.back());
    
    // Тест 10: Производительность
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; ++i) {
        buffer.push(i);
        if (i % 2 == 0) buffer.pop();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    assert(duration.count() < 10000); // Должно быть быстро
}
```

## Задание 5: Адаптивный контейнер

**Описание:** Реализуйте класс `AdaptiveContainer`, который автоматически выбирает оптимальный контейнер (vector, deque, list) на основе паттерна использования.

**Требования:**
- Методы: `insert()`, `erase()`, `find()`, `optimize()`
- Автоматическое переключение между контейнерами
- Сбор статистики использования

**Тесты:**
```cpp
void test_adaptive_container() {
    AdaptiveContainer<int> container;
    
    // Тест 1: Начальное состояние
    assert(container.empty());
    assert(container.get_container_type() == "vector"); // По умолчанию
    
    // Тест 2: Множественные вставки в конец
    for (int i = 0; i < 100; ++i) {
        container.insert(container.end(), i);
    }
    assert(container.get_container_type() == "vector");
    
    // Тест 3: Вставки в начало
    for (int i = 0; i < 50; ++i) {
        container.insert(container.begin(), i);
    }
    container.optimize();
    assert(container.get_container_type() == "deque");
    
    // Тест 4: Вставки в середину
    auto mid = container.begin();
    std::advance(mid, container.size() / 2);
    for (int i = 0; i < 30; ++i) {
        container.insert(mid, i);
    }
    container.optimize();
    assert(container.get_container_type() == "list");
    
    // Тест 5: Поиск элементов
    auto it = container.find(42);
    assert(it != container.end() || it == container.end());
    
    // Тест 6: Удаление элементов
    container.erase(container.begin());
    assert(container.size() > 0);
    
    // Тест 7: Статистика
    auto stats = container.get_statistics();
    assert(stats.insert_count > 0);
    assert(stats.erase_count > 0);
    
    // Тест 8: Копирование
    AdaptiveContainer<int> copy = container;
    assert(copy.size() == container.size());
    
    // Тест 9: Очистка
    container.clear();
    assert(container.empty());
    
    // Тест 10: Производительность разных операций
    container.benchmark_operations();
    auto benchmark = container.get_benchmark_results();
    assert(benchmark.vector_time >= 0);
    assert(benchmark.deque_time >= 0);
    assert(benchmark.list_time >= 0);
}
```

## Задание 6: Менеджер памяти для массивов

**Описание:** Создайте класс `ArrayManager`, который эффективно управляет множеством массивов фиксированного размера.

**Требования:**
- Методы: `allocate()`, `deallocate()`, `get_array()`, `get_statistics()`
- Пулинг памяти для производительности
- Поддержка разных размеров массивов

**Тесты:**
```cpp
void test_array_manager() {
    ArrayManager<int> manager;
    
    // Тест 1: Выделение массива
    auto arr1 = manager.allocate<10>();
    assert(arr1 != nullptr);
    assert(arr1->size() == 10);
    
    // Тест 2: Заполнение массива
    for (size_t i = 0; i < arr1->size(); ++i) {
        (*arr1)[i] = static_cast<int>(i);
    }
    assert((*arr1)[0] == 0);
    assert((*arr1)[9] == 9);
    
    // Тест 3: Освобождение массива
    manager.deallocate(arr1);
    
    // Тест 4: Повторное использование памяти
    auto arr2 = manager.allocate<10>();
    assert(arr2 != nullptr);
    
    // Тест 5: Разные размеры
    auto arr3 = manager.allocate<5>();
    auto arr4 = manager.allocate<20>();
    assert(arr3->size() == 5);
    assert(arr4->size() == 20);
    
    // Тест 6: Статистика
    auto stats = manager.get_statistics();
    assert(stats.allocated_count > 0);
    assert(stats.deallocated_count > 0);
    
    // Тест 7: Множественные выделения
    std::vector<decltype(arr1)> arrays;
    for (int i = 0; i < 100; ++i) {
        arrays.push_back(manager.allocate<10>());
    }
    assert(arrays.size() == 100);
    
    // Тест 8: Освобождение всех массивов
    for (auto& arr : arrays) {
        manager.deallocate(arr);
    }
    
    // Тест 9: Фрагментация памяти
    auto frag_stats = manager.get_fragmentation_stats();
    assert(frag_stats.fragmentation_level >= 0.0);
    
    // Тест 10: Очистка всей памяти
    manager.clear_all();
    auto final_stats = manager.get_statistics();
    assert(final_stats.active_arrays == 0);
}
```

## Задание 7: Эффективная очередь с приоритетами

**Описание:** Реализуйте класс `EfficientPriorityQueue`, который использует разные контейнеры в зависимости от размера данных.

**Требования:**
- Методы: `push()`, `pop()`, `top()`, `change_priority()`
- Автоматическое переключение между heap и sorted vector
- Поддержка изменения приоритета

**Тесты:**
```cpp
void test_efficient_priority_queue() {
    EfficientPriorityQueue<int> pq;
    
    // Тест 1: Базовые операции
    assert(pq.empty());
    pq.push(3, 3);
    pq.push(1, 1);
    pq.push(2, 2);
    assert(pq.top() == 3); // Наивысший приоритет
    
    // Тест 2: Pop операция
    pq.pop();
    assert(pq.top() == 2);
    
    // Тест 3: Изменение приоритета
    pq.change_priority(1, 5);
    assert(pq.top() == 1); // Теперь наивысший приоритет
    
    // Тест 4: Большой объем данных
    for (int i = 0; i < 1000; ++i) {
        pq.push(i, i % 100);
    }
    assert(pq.size() > 100);
    
    // Тест 5: Проверка типа контейнера
    assert(pq.get_container_type() == "heap" || 
           pq.get_container_type() == "sorted_vector");
    
    // Тест 6: Производительность
    auto start = std::chrono::high_resolution_clock::now();
    while (!pq.empty()) {
        pq.pop();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    assert(duration.count() < 100000);
    
    // Тест 7: Дублирующие приоритеты
    pq.push(1, 5);
    pq.push(2, 5);
    pq.push(3, 5);
    assert(pq.size() == 3);
    
    // Тест 8: Очистка
    pq.clear();
    assert(pq.empty());
    
    // Тест 9: Итераторы (по убыванию приоритета)
    pq.push(1, 1);
    pq.push(2, 2);
    pq.push(3, 3);
    std::vector<int> values;
    for (const auto& item : pq) {
        values.push_back(item);
    }
    assert(values[0] == 3);
    assert(values[1] == 2);
    assert(values[2] == 1);
    
    // Тест 10: Статистика переключений
    auto stats = pq.get_switch_statistics();
    assert(stats.heap_to_vector_switches >= 0);
    assert(stats.vector_to_heap_switches >= 0);
}
```

## Задание 8: Строковый интерн-пул

**Описание:** Создайте класс `StringInternPool`, который эффективно управляет уникальными строками, используя string_view для избежания дублирования.

**Требования:**
- Методы: `intern()`, `find()`, `size()`, `clear()`
- Автоматическое удаление неиспользуемых строк
- Статистика использования памяти

**Тесты:**
```cpp
void test_string_intern_pool() {
    StringInternPool pool;
    
    // Тест 1: Базовое интернирование
    auto str1 = pool.intern("Hello");
    auto str2 = pool.intern("Hello");
    assert(str1.data() == str2.data()); // Один и тот же указатель
    
    // Тест 2: Разные строки
    auto str3 = pool.intern("World");
    assert(str1.data() != str3.data());
    assert(pool.size() == 2);
    
    // Тест 3: Поиск строки
    auto found = pool.find("Hello");
    assert(found != pool.end());
    assert(*found == "Hello");
    
    // Тест 4: Несуществующая строка
    auto not_found = pool.find("NotExists");
    assert(not_found == pool.end());
    
    // Тест 5: Большое количество строк
    for (int i = 0; i < 1000; ++i) {
        pool.intern("String" + std::to_string(i));
    }
    assert(pool.size() > 1000);
    
    // Тест 6: Статистика памяти
    auto stats = pool.get_memory_stats();
    assert(stats.total_memory > 0);
    assert(stats.unique_strings > 0);
    
    // Тест 7: Очистка неиспользуемых строк
    pool.cleanup_unused();
    auto new_size = pool.size();
    assert(new_size <= pool.size());
    
    // Тест 8: Итераторы
    size_t count = 0;
    for (const auto& str : pool) {
        assert(!str.empty());
        ++count;
    }
    assert(count == pool.size());
    
    // Тест 9: Очистка всего пула
    pool.clear();
    assert(pool.empty());
    
    // Тест 10: Производительность
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        pool.intern("Test" + std::to_string(i % 100));
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    assert(duration.count() < 50000);
    assert(pool.size() == 100); // Только уникальные строки
}
```

## Задание 9: Многоуровневый кэш

**Описание:** Реализуйте класс `MultiLevelCache`, который использует разные контейнеры для разных уровней кэширования.

**Требования:**
- Методы: `get()`, `put()`, `evict()`, `get_stats()`
- L1 кэш на основе array, L2 на основе vector, L3 на основе list
- LRU политика вытеснения

**Тесты:**
```cpp
void test_multi_level_cache() {
    MultiLevelCache<int, std::string> cache(4, 8, 16); // Размеры уровней
    
    // Тест 1: Базовые операции
    cache.put(1, "Value1");
    auto value = cache.get(1);
    assert(value.has_value());
    assert(value.value() == "Value1");
    
    // Тест 2: Отсутствующий ключ
    auto missing = cache.get(999);
    assert(!missing.has_value());
    
    // Тест 3: Заполнение L1 кэша
    for (int i = 1; i <= 4; ++i) {
        cache.put(i, "Value" + std::to_string(i));
    }
    auto stats = cache.get_stats();
    assert(stats.l1_size == 4);
    
    // Тест 4: Переполнение в L2
    cache.put(5, "Value5");
    stats = cache.get_stats();
    assert(stats.l2_size > 0);
    
    // Тест 5: LRU вытеснение
    cache.get(1); // Делаем 1 недавно использованным
    cache.put(6, "Value6");
    auto evicted = cache.get(2); // 2 должен быть вытеснен первым
    
    // Тест 6: Статистика попаданий
    cache.get(1);
    cache.get(1);
    stats = cache.get_stats();
    assert(stats.l1_hits > 0);
    
    // Тест 7: Заполнение всех уровней
    for (int i = 10; i < 50; ++i) {
        cache.put(i, "Value" + std::to_string(i));
    }
    stats = cache.get_stats();
    assert(stats.l1_size <= 4);
    assert(stats.l2_size <= 8);
    assert(stats.l3_size <= 16);
    
    // Тест 8: Принудительное вытеснение
    cache.evict(1);
    assert(!cache.get(1).has_value());
    
    // Тест 9: Очистка уровня
    cache.clear_level(1);
    stats = cache.get_stats();
    assert(stats.l1_size == 0);
    
    // Тест 10: Производительность
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        cache.put(i, "Value" + std::to_string(i));
        if (i % 2 == 0) {
            cache.get(i / 2);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    assert(duration.count() < 100000);
}
```

## Задание 10: Умный контейнер с профилированием

**Описание:** Создайте класс `ProfilingContainer`, который собирает детальную статистику о производительности операций и автоматически оптимизирует свою работу.

**Требования:**
- Методы: `insert()`, `erase()`, `find()`, `get_profile()`, `optimize()`
- Автоматическое переключение между контейнерами
- Детальная статистика производительности

**Тесты:**
```cpp
void test_profiling_container() {
    ProfilingContainer<int> container;
    
    // Тест 1: Начальное профилирование
    auto initial_profile = container.get_profile();
    assert(initial_profile.operation_count == 0);
    
    // Тест 2: Вставка элементов
    for (int i = 0; i < 100; ++i) {
        container.insert(i);
    }
    auto profile = container.get_profile();
    assert(profile.insert_operations == 100);
    assert(profile.average_insert_time > 0);
    
    // Тест 3: Поиск элементов
    for (int i = 0; i < 50; ++i) {
        container.find(i);
    }
    profile = container.get_profile();
    assert(profile.find_operations == 50);
    
    // Тест 4: Удаление элементов
    for (int i = 0; i < 25; ++i) {
        container.erase(i);
    }
    profile = container.get_profile();
    assert(profile.erase_operations == 25);
    
    // Тест 5: Автоматическая оптимизация
    container.set_auto_optimize(true);
    for (int i = 100; i < 1000; ++i) {
        container.insert(i);
        if (i % 10 == 0) {
            container.find(i - 5);
        }
    }
    profile = container.get_profile();
    assert(profile.optimization_count > 0);
    
    // Тест 6: Ручная оптимизация
    container.optimize();
    auto optimized_profile = container.get_profile();
    assert(optimized_profile.optimization_count > profile.optimization_count);
    
    // Тест 7: Сравнение производительности
    auto comparison = container.compare_containers();
    assert(comparison.vector_score >= 0);
    assert(comparison.deque_score >= 0);
    assert(comparison.list_score >= 0);
    
    // Тест 8: Экспорт статистики
    auto detailed_stats = container.export_detailed_stats();
    assert(!detailed_stats.empty());
    
    // Тест 9: Сброс профилирования
    container.reset_profiling();
    profile = container.get_profile();
    assert(profile.operation_count == 0);
    
    // Тест 10: Производительность с профилированием
    container.set_profiling(false);
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        container.insert(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto without_profiling = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    container.clear();
    container.set_profiling(true);
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; ++i) {
        container.insert(i);
    }
    end = std::chrono::high_resolution_clock::now();
    auto with_profiling = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Профилирование не должно сильно замедлять работу
    assert(with_profiling.count() < without_profiling.count() * 2);
}
``` 