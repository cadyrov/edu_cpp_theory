// 9. Напишите шаблон `MaxValue<auto...>`, вычисляющий максимум значений на этапе компиляции.
template <auto First, auto... Rest> struct MaxVal {
  private:
    static constexpr auto rest_max = MaxVal<Rest...>::value;

  public:
    static constexpr auto value = (First > rest_max) ? First : rest_max;
};

template <auto Val> struct MaxVal<Val> {
    static constexpr auto value = Val;
};

template <auto... Values> inline constexpr auto max_value = MaxVal<Values...>::value;

int main() {
    static_assert(max_value<1, 2, 3, 4> == 4);

    return 0;
}