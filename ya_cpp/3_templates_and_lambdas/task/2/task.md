Последовательный блок данных в С++ можно представить с помощью С-style-массивов, std::array, std::vector и std::initializer_list

Но в силу разности этих объектов сложно передавать их в функции единообразно

Решить эту проблему поможет span — легковесный объект шаблонного класса, который хранит указатель на первый элемент и количество элементов в последовательности

Можно сказать, что span ― это view на объект последовательности. C ним можно не беспокоиться за переход границ доступной памяти при передаче объекта в функции, потому что указатель и размер будут согласованы

В стандартной библиотеке эта абстракция реализуется с помощью std::span, а вы попробуйте написать свою

Вот описание класса Span без реализации методов и декларация функции as_bytes, которая на основе существующего span создаёт view, позволяющий смотреть отдельные байты исходного объекта

```cpp
template <typename T>
class Span {
public:
    /* зависимые типы здесь */

    template<typename It>
    Span(It first, ? count);

    template <typename It1, typename It2>
    Span(It1 first, It2 last);

    ? operator[](? idx);
    ? operator[](? idx) const;

    bool empty() const;

    ? data();
    const T *data() const;

    ? size() const;

    Span subspan(? offset, ? count) {
        return Span{data_ + offset, count};
    }

private:
    ? data_;
    ? size_;
};

template <typename T>
Span<const std::byte> as_bytes(Span<T> span); 
```

- Скопируйте код ниже себе и выполните задания:
- Реализуйте все методы Span вне описания класса.
- Реализуйте шаблон функции as_bytes.
- Предоставьте в публичной области класса зависимые типы и заполните типы со знаком вопроса.

```cpp
template <typename T>
class Span {
public:
    /* определите зависимые типы reference, const_reference, pointer, const_pointer, size_type здесь */

    template<typename It>
    Span(It first, ? count);

    template <typename It1, typename It2>
    Span(It1 first, It2 last);

    ? operator[](? idx);
    ? operator[](? idx) const;

    bool empty() const;

    ? data();
    const T *data() const;

    ? size() const;

    Span subspan(? offset, ? count) {
        return Span{data_ + offset, count};
    }

private:
    ? data_;
    ? size_;
};

template <typename T>
Span<const std::byte> as_bytes(Span<T> span); 
```

- Чтобы определить зависимые типы, используйте using для алиасов типов.
- Чтобы найти расстояние между двумя итераторами, используйте std::distance.
- Чтобы получить указатель по итератору, используйте std::to_address.
- Чтобы получить указатель на std::byte, используйте reinterpret_cast.
- Чтобы при определении методов вне класса в качестве возвращаемых значений использовать зависимые типы, применяйте оператор разрешения имён operator::.