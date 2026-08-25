// 10. Напишите `compose_many`, который применяет цепочку функций к значению.
template <typename T, typename... Func> auto compose_many(T value, Func... func) {
    ((value = functions(value)), ...);

    return value;
}