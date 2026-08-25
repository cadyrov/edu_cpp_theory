# Фильтрация конфигураций устройств

Проект «Луна-5» получает устройства с разными версиями прошивки и наборами возможностей. Нужно отбирать конфигурации по требованиям миссии на этапе компиляции.

## Задание

1. Создайте `VersionAtLeast<MinVersion>` с шаблонным `static constexpr bool value`, проверяющим `Device::version >= MinVersion`.
2. Создайте `HasFeature<Feature>` с шаблонным `static constexpr bool value`, проверяющим наличие `Feature` в `Device::FeatureList`.
3. Реализуйте `value_or_empty<Idx, Pred>`: возвращайте одноэлементный кортеж, если тип удовлетворяет предикату, иначе пустой.
4. Реализуйте `filter_tuple<Pred>`, объединяющую результаты через `std::tuple_cat`.
5. Реализуйте `print_devices_tuple`, вызывающую `print_one_device` для каждого элемента.

## Прекод

```cpp
#include <iostream>
#include <print>
#include <tuple>
#include <type_traits>

struct USB {};
struct Bluetooth {};
struct WiFi {};
struct FrontCamera {};
struct LTE {};

template <int Version, typename... Features>
struct DeviceConfig {
    static constexpr int version = Version;
    using FeatureList = std::tuple<Features...>;
};

template <int MinVersion>
struct VersionAtLeast {
    template <typename Device>
    // Ваш код здесь.
};

template <typename Feature>
struct HasFeature {
    template <typename Device>
    // Ваш код здесь.
};

template <std::size_t Idx, typename Pred, typename Tuple>
constexpr auto value_or_empty(const Tuple& tuple) {
    // Ваш код здесь.
}

template <typename Pred, typename Tuple>
constexpr auto filter_tuple(const Tuple& tuple) {
    // Ваш код здесь.
}

template <std::size_t Idx, typename Tuple>
void print_one_device(const Tuple&) {
    using Device = std::tuple_element_t<Idx, Tuple>;
    constexpr auto version = Device::version;
    constexpr auto featureCount =
        std::tuple_size_v<typename Device::FeatureList>;

    std::println(" - Device v{} with {} features",
                 version, featureCount);
}

template <typename Tuple>
void print_devices_tuple(const Tuple& tuple) {
    // Ваш код здесь.
}

int main() {
    using D1 = DeviceConfig<1, USB, Bluetooth>;
    using D2 = DeviceConfig<2, USB, WiFi>;
    using D3 = DeviceConfig<5, USB, WiFi, LTE>;
    using D4 = DeviceConfig<4, USB, WiFi, FrontCamera, LTE>;

    constexpr auto allDevices = std::tuple{D1{}, D2{}, D3{}, D4{}};

    constexpr auto versionFiltered =
        filter_tuple<VersionAtLeast<3>>(allDevices);
    print_devices_tuple(versionFiltered);
    std::println();

    constexpr auto finalFiltered =
        filter_tuple<HasFeature<FrontCamera>>(versionFiltered);
    print_devices_tuple(finalFiltered);
}
```

## Подсказки

- Тип элемента: `std::tuple_element_t<Idx, Tuple>`.
- Для доступа к шаблонному члену зависимого типа используйте `Pred::template value<T>`.
- Наличие типа в `FeatureList` можно проверить через `std::is_same` и fold expression.
- Создайте индексы через `std::make_index_sequence<std::tuple_size_v<Tuple>>`.
- Объединяйте пустые и одноэлементные кортежи через `std::tuple_cat`.
- Для шаблонной лямбды с синтаксисом `[]<typename...>()` включите C++20.
