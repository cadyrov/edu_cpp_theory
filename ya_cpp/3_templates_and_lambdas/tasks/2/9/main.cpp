template<typename T, typename F>
auto apply_twice(T value, F& func) {
    return func(func(value));
}