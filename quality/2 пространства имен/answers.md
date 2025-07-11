# Ответы на тест "Пространства имен"

## Правильные ответы:

1. **b** - Программа скомпилируется и вернет 15
   *Пространство имен может определяться несколько раз*

2. **b** - 100 42
   *Локальная переменная скрывает глобальную, ::test::value обращается к namespace*

3. **b** - using namespace std в заголовочном файле
   *Это загрязняет глобальное пространство имен для всех включающих файлов*

4. **a** - `double math::calculate(double x) { return x * 2; }`
   *Правильная квалификация имени функции и возвращаемого типа*

5. **b** - 20 10
   *using namespace outer делает доступным value = 20, inner::value = 10*

6. **a** - A::B::C::func
   *Квалификация разделяется двойными двоеточиями*

7. **b** - Ошибка: reference to 'Node' is ambiguous
   *Два using namespace создают конфликт имен*

8. **b** - Создает псевдоним для пространства имен
   *namespace alias - это псевдоним*

9. **b** - `::`
   *Префикс :: обращается к глобальному пространству имен*

10. **b** - Нет ошибок
    *Anonymous namespace делает символы видимыми в текущем файле*

11. **b** - test::print
    *ADL (Argument-Dependent Lookup) найдет функцию в namespace аргумента*

12. **b** - A импортирует только vector, B - все имена std
    *using declaration vs using directive*

13. **c** - Неопределенное поведение (нарушение стандарта)
    *Добавление в namespace std запрещено стандартом*

14. **b** - Только в больших проектах и библиотеках
    *Пространства имен решают проблему конфликтов в больших кодовых базах*

15. **d** - Ошибка компиляции
    *Конфликт using-деклараций*

16. **c** - `namespace my { class MyClass { }; }`
    *Правильный синтаксис объявления в namespace*

17. **b** - Делает v2 пространством по умолчанию для mylib
    *inline namespace делает содержимое доступным без квалификации*

18. **b** - abs может быть неправильной версией (int вместо double)
    *Разные компиляторы по-разному экспортируют abs в глобальное пространство*

19. **b** - Выведет: 2 1
    *Ближайшее имя x = 2, outer::x = 1*

20. **b** - В cpp-файлах
    *В заголовочных файлах using namespace std недопустимо*

21. **b** - processed
    *ADL найдет test::process для типа test::Data*

22. **b** - 2-3
    *Глубокая вложенность затрудняет чтение и использование*

23. **b** - Доступ к глобальному global_x
    *:: в начале означает глобальное пространство имен*

24. **b** - Нет ошибок
    *Namespace можно определять несколько раз*

25. **b** - Выведет 42
    *using namespace A::B корректный синтаксис*

26. **c** - Краткие, но понятные имена
    *Баланс между краткостью и понятностью*

27. **b** - 100
    *Anonymous namespace делает символы доступными в файле*

28. **a** - Да, правильно
    *Корректное определение метода с квалификацией*

29. **b** - Импортирует все имена child в parent
    *using namespace внутри namespace импортирует имена*

30. **b** - Только при вызове func()
    *Конфликт возникает при попытке использования неквалифицированного имени*

31. **b** - 1
    *using outer::x делает x доступным в inner*

32. **b** - Слишком длинные квалифицированные имена
    *Глубокая вложенность усложняет использование*

33. **b** - global namespace
    *func() без квалификации найдет глобальную, test::func() - в namespace*

34. **b** - Нет, namespace не нужен для одного класса
    *Namespace имеет смысл для группировки нескольких сущностей*

35. **b** - Несколько определений Vector в разных namespace
    *Ambiguous reference означает неоднозначность выбора*

36. **b** - Да, для внутренних деталей реализации
    *detail - принятое имя для внутренних компонентов*

37. **a** - 10
    *using A::x делает A::x доступным как x*

38. **b** - Нет разницы (начиная с C++17)
    *C++17 поддерживает nested namespace declaration*

39. **b** - Поиск в inner, затем в outer
    *Unqualified name lookup ищет в текущем namespace, затем в объемлющих*

40. **b** - Вариант B лучше для версионирования
    *inline namespace обеспечивает обратную совместимость при версионировании* 