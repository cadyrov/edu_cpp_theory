# Самая крупная транзакция

Крупные компании анализируют пользовательские данные, чтобы улучшать взаимодействие клиентов со своей экосистемой.

Допустим, аналитическая система банка обрабатывает транзакции вида:

```cpp
struct Transaction {
    double amount;
    std::string category;
};
```

Каждая транзакция содержит сумму оплаты и категорию платежа.

Реализуйте функцию `get_top_transactions`, которая:

- принимает непустой вектор транзакций;
- возвращает транзакцию с самой большой суммой платежа независимо от категории.

## Прекод

```cpp
#include <algorithm>
#include <ranges>
#include <string>
#include <vector>

struct Transaction {
    double amount;
    std::string category;
};

Transaction get_top_transactions(
    const std::vector<Transaction>& transactions
) {
    // Ваш код здесь.
}
```

## Подсказка

Используйте [`std::ranges::max_element`](https://en.cppreference.com/w/cpp/algorithm/ranges/max_element) и проекцию по полю `amount`.
