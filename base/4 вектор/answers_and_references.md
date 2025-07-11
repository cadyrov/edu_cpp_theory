# Ответы на тест "Вектор в C++" с указанием номеров строк в теории

## Вопрос 1: **A** - Model-View-Controller: Модель, Представление, Контроллер
*Объяснение:* MVC - это паттерн "Модель-Представление-Контроллер", который делит задачи на три части.

## Вопрос 2: **B** - `#include <vector>`
*Объяснение:* Для использования вектора необходимо подключить заголовочный файл `<vector>`.

## Вопрос 3: **C** - 5 10
*Объяснение:* Конструктор `vector(10)` создает вектор из 10 элементов со значением 10.

## Вопрос 4: **D** - `std::vector<int> v4[3] = {1, 2, 3};`
*Объяснение:* Это объявление массива векторов, а не инициализация одного вектора.

## Вопрос 5: **C** - Добавляет элемент в конец вектора
*Объяснение:* Метод `push_back` добавляет новый элемент в конец вектора.

## Вопрос 6: **B** - Неопределенное поведение
*Объяснение:* Нельзя вызывать `pop_back()` на пустом векторе - это приводит к неопределенному поведению.

## Вопрос 7: **A** - apple orange
*Объяснение:* `front()` возвращает первый элемент, `back()` - последний.

## Вопрос 8: **B** - `std::vector<std::string>::iterator`
*Объяснение:* Итератор вектора имеет тип `std::vector<T>::iterator`.

## Вопрос 9: **C** - Возвращает значение элемента, на который указывает итератор
*Объяснение:* Операция разыменования (*) возвращает значение элемента по итератору.

## Вопрос 10: **B** - 20
*Объяснение:* Итератор указывает на первый элемент (10), после `++` указывает на второй (20).

## Вопрос 11: **B** - end()
*Объяснение:* Метод `end()` возвращает итератор на фиктивный элемент после последнего.

## Вопрос 12: **B** - Выводит: 5 4 3 2 1
*Объяснение:* Реверсивные итераторы проходят контейнер в обратном порядке.

## Вопрос 13: **C** - size() - количество элементов, capacity() - выделенная память
*Объяснение:* `size()` показывает количество элементов, `capacity()` - выделенную память.

## Вопрос 14: **B** - Все элементы копируются в новую область памяти
*Объяснение:* При реаллокации вектор переносит все элементы в новую область памяти.

## Вопрос 15: **C** - Все итераторы (при реаллокации)
*Объяснение:* При реаллокации все итераторы становятся невалидными.

## Вопрос 16: **B** - Резервирует память без изменения размера
*Объяснение:* `reserve()` изменяет вместимость, но не размер вектора.

## Вопрос 17: **B** - 1 10
*Объяснение:* `reserve(10)` устанавливает capacity=10, `push_back(1)` устанавливает size=1.

## Вопрос 18: **C** - at()
*Объяснение:* Метод `at()` не изменяет размер вектора и не инвалидирует итераторы.

## Вопрос 19: **B** - Возвращает итератор на найденный элемент или end()
*Объяснение:* `std::find` возвращает итератор на найденный элемент или `end()` если не найден.

## Вопрос 20: **B** - 2
*Объяснение:* `std::count` подсчитывает количество элементов равных заданному значению.

## Вопрос 21: **B** - Суммирует элементы в диапазоне
*Объяснение:* `std::accumulate` суммирует элементы в заданном диапазоне.

## Вопрос 22: **C** - 15
*Объяснение:* Сумма элементов 1+2+3+4+5 = 15.

## Вопрос 23: **B** - Итератор на максимальный элемент
*Объяснение:* `std::max_element` возвращает итератор на максимальный элемент.

## Вопрос 24: **B** - Поэлементно слева направо до первого различия
*Объяснение:* Лексикографическое сравнение идет поэлементно до первого различия.

## Вопрос 25: **B** - Меняет порядок элементов на противоположный
*Объяснение:* `std::reverse` меняет порядок элементов на противоположный.

## Вопрос 26: **B** - Перемещает идущие подряд дубликаты в конец
*Объяснение:* `std::unique` перемещает дубликаты в конец, не удаляя их.

## Вопрос 27: **A** - 3
*Объяснение:* После `unique` остается 3 уникальных элемента: 1, 2, 3.

## Вопрос 28: **B** - Для генерации псевдослучайных чисел
*Объяснение:* `std::mt19937` - генератор псевдослучайных чисел (вихрь Мерсенна).

## Вопрос 29: **B** - Перемешивает элементы в случайном порядке
*Объяснение:* `std::shuffle` перемешивает элементы в случайном порядке.

## Вопрос 30: **A** - Заполняет диапазон указанным значением
*Объяснение:* `std::fill` заполняет диапазон указанным значением.

## Вопрос 31: **C** - 7
*Объяснение:* `fill` заполняет весь вектор значением 7.

## Вопрос 32: **B** - Создает итератор для добавления элементов в конец
*Объяснение:* `std::back_inserter` создает итератор для добавления элементов в конец.

## Вопрос 33: **B** - Конструирует объект на месте без создания временного
*Объяснение:* `emplace_back` конструирует объект на месте, избегая создания временного объекта.

## Вопрос 34: **B** - Применяет функцию к каждому элементу диапазона
*Объяснение:* `std::transform` применяет функцию к каждому элементу диапазона.

## Вопрос 35: **D** - 4
*Объяснение:* Лямбда умножает каждый элемент на 2: v[1] = 2 * 2 = 4.

## Вопрос 36: **A** - Автоматический вывод типов шаблонов
*Объяснение:* CTAD позволяет компилятору автоматически выводить типы шаблонов.

## Вопрос 37: **A** - `std::vector numbers = {1, 2, 3};`
*Объяснение:* В C++17 можно опустить тип в угловых скобках благодаря CTAD.

## Вопрос 38: **B** - Освобождает неиспользуемую память
*Объяснение:* `shrink_to_fit` освобождает неиспользуемую память.

## Вопрос 39: **B** - Неопределенное поведение
*Объяснение:* Обращение к `vec[vec.size()]` выходит за границы и приводит к неопределенному поведению.

## Вопрос 40: **B** - Перемещает содержимое v1 в v2
*Объяснение:* `std::move` перемещает содержимое одного вектора в другой без копирования.

---

## Сводка правильных ответов:
1. A  2. B  3. C  4. D  5. C  6. B  7. A  8. B  9. C  10. B
11. B  12. B  13. C  14. B  15. C  16. B  17. B  18. C  19. B  20. B
21. B  22. C  23. B  24. B  25. B  26. B  27. A  28. B  29. B  30. A
31. C  32. B  33. B  34. B  35. D  36. A  37. A  38. B  39. B  40. B

**Итого:** 40 вопросов, 26 с примерами кода (65%) 