# Ответы к тесту по наследованию и полиморфизму в C++

## Правильные ответы:

**Вопрос 1:** **a) Выведет "Base::func"**
Поскольку метод `func()` не объявлен как виртуальный в базовом классе, будет вызван метод базового класса независимо от реального типа объекта.

**Вопрос 2:** **c) public virtual**
Деструктор базового класса должен быть публичным и виртуальным для корректного полиморфного удаления объектов.

**Вопрос 3:** **c) "Yip"**
Виртуальные методы обеспечивают полиморфизм - будет вызван метод `Puppy::speak()`.

**Вопрос 4:** **d) Больше 8 байт**
Класс B содержит виртуальный деструктор, что добавляет указатель на vtable (~8 байт) плюс int (4 байта) плюс выравнивание.

**Вопрос 5:** **b) Гарантирует, что метод переопределяет виртуальный метод базового класса**
`override` проверяет во время компиляции, что метод действительно переопределяет виртуальный метод предка.

**Вопрос 6:** **b) Ошибка компиляции - нельзя создать объект абстрактного класса**
Класс `Shape` содержит чисто виртуальную функцию, поэтому является абстрактным.

**Вопрос 7:** **b) "Является" (is-a)**
Публичное наследование выражает отношение "является" между классами.

**Вопрос 8:** **a) "Caught Exception1"**
Первый подходящий обработчик перехватит исключение. `Exception2` является `Exception1`.

**Вопрос 9:** **b) Для выражения отношения "реализован посредством"**
Приватное наследование используется для наследования реализации без наследования интерфейса.

**Вопрос 10:** **a) "Base ctor Derived ctor Derived dtor Base dtor"**
Конструкторы вызываются от базового к производному, деструкторы - в обратном порядке.

**Вопрос 11:** **a) public members становятся protected, protected остаются protected**
При protected наследовании публичные члены базового класса становятся защищенными.

**Вопрос 12:** **b) "B::f"**
Виртуальная функция `f()` вызывается полиморфно, даже из метода `g()` базового класса.

**Вопрос 13:** **b) Для решения проблемы ромбовидного наследования**
Виртуальное наследование обеспечивает единственную копию общего базового класса.

**Вопрос 14:** **b) Ошибка компиляции - несовпадение сигнатур методов**
Метод в `Derived` имеет квалификатор `const`, что делает его сигнатуру отличной от базового.

**Вопрос 15:** **c) nullptr**
`dynamic_cast` возвращает `nullptr` для указателей при неудачном приведении типа.

**Вопрос 16:** **a) "Rex barks"**
Защищенный член `name_` доступен в производном классе.

**Вопрос 17:** **b) Потеря данных производного класса при копировании в базовый класс**
Срезка происходит при передаче объекта производного класса по значению как объект базового класса.

**Вопрос 18:** **b) Ошибка компиляции на строке X**
Приватное наследование делает невозможным преобразование к базовому классу вне класса-наследника.

**Вопрос 19:** **b) Template Method**
Паттерн "Шаблонный метод" определяет скелет алгоритма в базовом классе, оставляя детали подклассам.

**Вопрос 20:** **b) "ABC"**
Виртуальный вызов приведет к выполнению `C::func()`, который вызывает цепочку методов.

**Вопрос 21:** **a) final**
Ключевое слово `final` запрещает дальнейшее наследование от класса или переопределение метода.

**Вопрос 22:** **b) Ошибка компиляции на строке X - нет конструктора по умолчанию в Base**
Конструктор производного класса должен явно вызвать конструктор базового класса.

**Вопрос 23:** **b) От производного к базовому**
Деструкторы вызываются в порядке, обратном вызову конструкторов.

**Вопрос 24:** **a) "Base"**
Передача по значению приводит к срезке объекта - создается копия базового класса.

**Вопрос 25:** **b) Шаблон, где класс наследуется от шаблона, параметризованного самим классом**
CRTP: `class Derived : public Base<Derived>`.

**Вопрос 26:** **a) "A::func"**
Во время выполнения конструктора базового класса объект еще имеет тип базового класса.

**Вопрос 27:** **a) std::bad_cast**
`dynamic_cast` для ссылок выбрасывает `std::bad_cast` при неудачном приведении.

**Вопрос 28:** **a) "Woof"**
Код корректен - `static_cast` безопасен, так как мы знаем реальный тип объекта.

**Вопрос 29:** **b) std::variant не требует виртуальных функций и наследования**
`std::variant` обеспечивает полиморфизм времени компиляции без использования наследования.

**Вопрос 30:** **b) "B::f"**
Класс C наследует реализацию `f()` от класса B, поэтому не является абстрактным.

**Вопрос 31:** **c) Liskov Substitution Principle**
Объекты базового класса должны быть заменяемы объектами производного класса без изменения корректности программы.

**Вопрос 32:** **b) Ошибка компиляции на строке X - нельзя переопределить final метод**
Спецификатор `final` запрещает дальнейшее переопределение виртуального метода.

**Вопрос 33:** **a) Структура данных для хранения виртуальных функций объекта**
Vtable содержит указатели на виртуальные функции для обеспечения полиморфизма.

**Вопрос 34:** **a) "10"**
Виртуальное наследование обеспечивает единственную копию `Base`, устраняя неоднозначность.

**Вопрос 35:** **c) Метод, возвращающий важный статус операции**
`[[nodiscard]]` предупреждает, если возвращаемое значение игнорируется.

**Вопрос 36:** **c) Ошибка компиляции на строке X - неоднозначность**
Компилятор не может определить, какой из методов `func()` вызывать.

**Вопрос 37:** **c) Когда есть отношение "содержит" или "использует"**
Композиция предпочтительна для отношений "has-a" и "uses-a".

**Вопрос 38:** **b) Ошибка компиляции - нельзя создать объект абстрактного класса**
Нельзя передать абстрактный класс по значению.

**Вопрос 39:** **b) Ситуация, когда класс наследуется от двух классов с общим предком**
"Алмазная проблема" - неоднозначность при множественном наследовании с общим предком.

**Вопрос 40:** **a) "Acquire Manager ~Manager Release"**
Член-объект конструируется перед телом конструктора и разрушается после тела деструктора.

---

## Объяснения ключевых концепций:

### Виртуальные функции и полиморфизм
- Виртуальные функции обеспечивают позднее связывание (late binding)
- `override` помогает избежать ошибок при переопределении
- `final` запрещает дальнейшее переопределение

### Конструкторы и деструкторы
- Порядок вызова: базовый → производный (конструкторы), производный → базовый (деструкторы)
- Виртуальный деструктор необходим для полиморфного удаления

### Типы наследования
- **Public**: "is-a" отношение, сохраняет интерфейс
- **Private**: "implemented-in-terms-of", наследование реализации
- **Protected**: редко используется, для иерархий классов

### Приведение типов
- `static_cast`: быстрое, но небезопасное приведение
- `dynamic_cast`: безопасное приведение с проверкой типа во время выполнения

### Принципы проектирования
- Предпочитайте композицию наследованию
- Следуйте принципам SOLID
- Используйте современные возможности C++ (auto, smart pointers, etc.)

Общий результат: __/40 