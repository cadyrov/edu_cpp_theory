# Монадические операции с `std::optional`

Для заданий 1 и 2 нужен C++23. Задание 3 требует реализации `std::optional` как диапазона из C++26.

## Задание 1. Подпись получателя

Для каждого письма:

- вызовите `GetRecipientName()`;
- через `transform` добавьте к имени префикс `"To: "`;
- через `or_else` подставьте `"To: [unknown]"`;
- добавьте готовую строку в `labeledRecipients`.

```cpp
struct Letter {
    std::optional<std::string> GetRecipientName() const;
};

std::vector<Letter> letters;
std::vector<std::string> labeledRecipients;

for (const Letter& letter : letters) {
    // Ваш код здесь.
    labeledRecipients.push_back(label);
}
```

## Задание 2. Уникальные имена

Получите уникальные имена отправителей из `std::vector<Letter>`:

1. Вызовите `GetSenderName()` через `views::transform`.
2. Удалите пустые `optional` через `views::filter`.
3. Извлеките значения через второй `views::transform`.
4. Материализуйте сначала `std::set`, затем `std::vector` через `ranges::to`.

```cpp
struct Letter {
    std::optional<std::string> GetSenderName() const;
};

std::vector<Letter> letters;

auto uniqueNames = /* Ваш код здесь */;
```

## Задание 3. `optional` как диапазон

Перепишите решение задания 2 для C++26 без явных `filter` и второго `transform`. Используйте тот факт, что `optional<T>` является диапазоном из нуля или одного элемента.

```cpp
auto uniqueNames = letters
    | std::views::transform(&Letter::GetSenderName)
    // Ваш код здесь.
    | std::ranges::to<std::set>()
    | std::ranges::to<std::vector>();
```

## Подсказки

- `transform` автоматически оборачивает обычный результат в `optional`.
- Функция внутри `or_else` не принимает аргументов и возвращает `optional` того же типа.
- Проверку значения можно передать как `&std::optional<std::string>::has_value`.
- Для C++26 объедините диапазон диапазонов через `std::views::join`.
