Вернёмся к реализации рекурсивной лямбды (до С++23) с помощью шаблонной лямбды с аргументом self:

```cpp
auto fib_impl = [](auto &self, int n) -> int { return (n <= 1) ? n : self(self, n - 1) + self(self, n - 2); };

auto fib = [fib_impl](int n) { return fib_impl(fib_impl, n); }; 
```

- Это решение простое и понятное, но требует аж двух лямбд и передачи self при вызове self.
- Напишем более изящное решение, которое сможет озадачить и развлечь ваших коллег. Реализуем универсальную функцию make_recursive, возвращающую функциональный объект, который можно вызывать с одним аргументом:

```cpp
template <typename Func>
auto make_recursive(Func &&func);

auto fib = make_recursive([](auto &self, int n) -> int { return (n <= 1) ? n : self(n - 1) + self(n - 2); });

auto x = fib(7); 
```

- Заметьте, что лямбда, передаваемая в make_recursive, теперь вызывает self с одним аргументом.
- Скопируйте код ниже к себе и реализуйте оператор вызова функции во вспомогательном классе RecursionHelper.

```cpp
template <typename Func>
class RecursionHelper {
    Func func_;

public:
    explicit RecursionHelper(Func func) : func_(std::move(func)) {}
    template <typename... Args>
    decltype(auto) operator()(Args &&...args) {
        return /* ваш код */;
    }
};

template <typename Func>
auto make_recursive(Func &&func) {
    return RecursionHelper{std::forward<Func>(func)};
} 
```

- В операторе вызова функции вызовите func_.
- Первым аргументом у func_ идёт self. Поразмышляйте, что передать в этот аргумент. Cаму func_ передать нельзя, ведь она затем вызывает self, не передавая self в качестве первого аргумента, как мы видим в примере с fib. Значит, вам нужно передать другой объект, который умеет вызывать func_, передавая ей полученные аргументы.
- Не забудьте передать в func_ ещё и аргументы оператора вызова функции.
- Раскройте пакет аргументов при вызове func_ и используйте идеальную передачу.