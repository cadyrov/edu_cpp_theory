Скопируйте код себе и исправьте его так, чтобы при передаче значений содержимое контейнеров не копировалось:
```cpp
void log(std::string s) {
  std::println(s);
};

void main() {
  std::string s = "string";
  std::string_view sv = s;
  const std::string& cr = s;
  const char* cs = s.c_str();

  log(sv);
  log(s);
  log(cr);
  log(cs);
} 
```

- Используйте тот факт, что std::string_view легковесен при копировании.
- Используйте различные перегрузки конструкторов std::string_view.
