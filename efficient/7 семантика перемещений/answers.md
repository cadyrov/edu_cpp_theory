# Ответы на тест по семантике перемещений

## Правильные ответы:

1. **B** - Выведет пустую строку (строка была перемещена)
2. **B** - MyClass(MyClass&& other) noexcept : data_(std::move(other.data_)) {}
3. **B** - Оптимизация компилятора, избегающая ненужных копирований
4. **C** - Ctor Dtor (благодаря copy elision)
5. **B** - Присваивает новое значение переменной и возвращает старое
6. **C** - Когда операция гарантированно не бросает исключения
7. **C** - Ошибка компиляции (unique_ptr не копируется)
8. **B** - rvalue (std::move приводит к rvalue-ссылке)
9. **A** - Named Return Value Optimization
10. **B** - void func(std::vector<int> v) { data_ = std::move(v); }
11. **B** - moved original (exchange заменяет значение)
12. **C** - push_back() (имеет перегрузку для rvalue)
13. **C** - Ошибка компиляции из-за отсутствия конструктора перемещения
14. **C** - O(n) (нужно переместить каждый элемент)
15. **A** - Создает итератор, который перемещает элементы при разыменовании
16. **C** - container.push_back(std::move(temporary_object));
17. **C** - 0 5 10 (первая строка перемещена полностью, вторая частично)
18. **C** - При возврате поля объекта
19. **B** - Ссылка на временный объект или объект, который можно переместить
20. **B** - Версия с noexcept и проверкой на самоприсваивание
21. **A** - 2 0 (два объекта созданы, затем уничтожены)
22. **D** - Зависит от контекста использования
23. **B** - 1 3 (v1 в валидном но неопределенном состоянии)
24. **D** - B и C (обе могут использовать RVO)
25. **B** - Идеально передает аргумент с сохранением его категории значения
26. **B** - Попытка копирования unique_ptr
27. **C** - Ничего не выведет (NRVO исключает копирование/перемещение)
28. **C** - std::array (линейная сложность)
29. **B** - (пусто) a (элементы были перемещены)
30. **D** - std::vector::at (только для доступа)
31. **B** - -1 42 (unique_ptr был перемещен)
32. **B** - vec.emplace_back("test") (конструирование на месте)
33. **B** - Успешная компиляция и выполнение (copy elision)
34. **B** - std::is_move_constructible_v
35. **A** - Hello World (std::move в return не мешает, но бесполезен)
36. **C** - std::ostream (копирование и перемещение запрещены)
37. **A** - 1344 (создание, перемещение в параметр, два деструктора)
38. **A** - MyClass(MyClass&& other) : data_(std::exchange(other.data_, nullptr)) {}
39. **A** - 5 5 (оптимизация не влияет на результат)
40. **C** - template<typename T> void func(T&& t) { process(std::forward<T>(t)); }

## Пояснения к сложным вопросам:

**Вопрос 4**: Copy elision позволяет компилятору исключить лишние копирования при возврате временного объекта.

**Вопрос 11**: std::exchange(other.name_, "moved") присваивает "moved" в other.name_ и возвращает старое значение.

**Вопрос 17**: При конкатенации строк первая строка полностью перемещается, вторая может быть перемещена частично.

**Вопрос 23**: После перемещения объект остается в валидном, но неопределенном состоянии. push_back может сработать.

**Вопрос 27**: NRVO (Named Return Value Optimization) исключает необходимость вызова конструктора копирования или перемещения.

**Вопрос 29**: make_move_iterator заставляет контейнер перемещать элементы вместо копирования.

**Вопрос 40**: Универсальные ссылки (T&&) с std::forward обеспечивают идеальную передачу параметров. 