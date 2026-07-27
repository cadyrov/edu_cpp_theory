Упростите код с помощью std::initializer_list.

```cpp
std::unordered_map<int, std::string> players;
players.emplace(1, "John");
players.emplace(2, "Michael");
players.emplace(3, "Todd");
players.emplace(4, "Chris");

for (const auto& [id, name] : players) {
  std::println("id={}, name={}", id, name);
} 
```


- Помните, что фигурные скобки воспринимаются как std::initializer_list и могут заметно упростить восприятие кода, если использовать их в for-range.