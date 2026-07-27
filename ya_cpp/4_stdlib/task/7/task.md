Представьте, что вы пишете программу-клиент для СУБД.

Скопируйте код ниже к себе и реализуйте функцию Serialize, которая преобразует в строку условия SQL-запроса, чтобы передать её клиенту СУБД.

```cpp
#include <string>
#include <optional>
#include <cassert>

struct User {
    std::string name;
};

enum class OrderBy {
    Age = 1,
    Weight = 2,
};

std::string to_string(OrderBy orderBy) {
    switch(orderBy) {
        case OrderBy::Age:
            return "Age";
        case OrderBy::Weight:
            return "Weight";
    }
}

struct Query {
    User user;
    std::optional<OrderBy> orderBy;
};

std::string Serialize(const Query& query) {
    // ваш код здесь
    return {};
}

int main() {
    assert(Serialize({{"Mary"}, {}}) == "SELECT * FROM Users WHERE Name == \"Mary\";");
    assert(Serialize({{"John"}, {OrderBy::Age}}) == "SELECT * FROM Users WHERE Name == \"John\" ORDER BY Age;");
    return 0;
} 
```

Подсказка:
- Используйте конкатенацию строк через operator+=()

## Задание 2

Представьте, что вы пишете программу, которая использует для логирования функцию c_log из библиотеки на языке C. 

Скопируйте код ниже себе и залогируйте каждое слова из входного потока с помощью функции c_log.

```cpp
#include <iostream>
#include <string>

extern "C" void c_log(const char* c_str) {
  printf("%lld | %5d: %s\n", (long long)time(NULL), strlen(c_str), c_str);
}

int main() {
  // ваш код здесь
  return 0;
} 
```

- Используйте std::cin для чтения слова из входного потока.
- Используйте метод c_str, чтобы получить указатель на C-строку.