# if/switch с инициализацией

## Определение
Инициализирующие операторы if и switch (C++17) позволяют объявлять переменные в условном выражении, ограничивая их область видимости блоком условия.

## Зачем это нужно
- Локализация области видимости переменных
- Уменьшение вложенности кода
- Предотвращение случайного использования временных переменных
- Более чистый и понятный код
- Объединение инициализации и проверки

## Примеры

### ✅ Хорошо
```cpp
// if с инициализацией
if (auto it = map.find(key); it != map.end()) {
    use(it->second);
}  // it не доступен здесь

// switch с инициализацией
switch (auto value = getValue(); value) {
    case 1: handle1(); break;
    case 2: handle2(); break;
    default: handleDefault();
}  // value не доступен здесь

// Проверка результата операции
if (auto [iter, inserted] = map.insert(value); inserted) {
    // Используем iter только при успешной вставке
}

// Обработка опционального значения
if (auto opt = tryGetValue(); opt.has_value()) {
    process(opt.value());
}

// Проверка с освобождением ресурса
if (auto lock = tryLock(); lock.owns_lock()) {
    // Работаем с защищённым ресурсом
}  // Автоматическое освобождение
```

### ❌ Плохо
```cpp
// Утечка области видимости
auto it = map.find(key);  // it доступен везде
if (it != map.end()) {
    use(it->second);
}  // it всё ещё доступен

// Повторное использование переменной
auto value = getValue();
switch (value) {  // value может быть случайно изменено
    case 1: value = 42;  // Опасно
    // ...
}

// Избыточная вложенность
auto result = operation();
if (result.isValid()) {
    if (result.hasData()) {
        // Слишком много уровней
    }
}
```

## Нюансы использования

### 1. Область видимости
```cpp
// Переменная доступна во всех ветках
if (auto val = compute(); val > 0) {
    usePositive(val);
} else {
    useNonPositive(val);
}

// В else-if цепочках
if (auto x = f(); x == 1) {
    // ...
} else if (x == 2) {  // x доступен
    // ...
}
```

### 2. Множественные переменные
```cpp
// Структурированное связывание
if (auto [iter, ok] = map.insert(value); ok) {
    // ...
}

// Несколько переменных
if (auto ptr = create(), count = size(); ptr && count > 0) {
    // ...
}
```

### 3. Типы инициализации
```cpp
// Ссылки
if (auto& item = getRef(); item.isValid()) {
    // Работаем по ссылке
}

// Константы
if (const auto value = compute(); value > 0) {
    // value нельзя изменить
}
```

### 4. Использование с RAII
```cpp
// Автоматическое освобождение ресурсов
if (std::lock_guard lock(mutex); needProcess()) {
    // Защищённый код
}  // Автоматическая разблокировка

// С умными указателями
if (auto ptr = std::make_unique<Resource>(); ptr) {
    ptr->process();
}  // Автоматическое освобождение
```

### 5. В switch
```cpp
switch (std::string s = getString(); s.length()) {
    case 0: handleEmpty(); break;
    case 1: handleSingle(s[0]); break;
    default: handleMultiple(s);
}
```

### 6. Комбинация с другими фичами
```cpp
// С optional
if (auto opt = std::optional<int>{42}; opt) {
    use(*opt);
}

// С итераторами
if (auto it = std::find(begin, end, value); it != end) {
    // ...
}
```

### 7. Best practices
```cpp
// Предпочитайте инициализацию когда:
// 1. Переменная нужна только в if/switch
if (auto temp = heavyComputation(); temp > threshold) {
    // ...
}

// 2. Проверка результата операции
if (auto result = tryOperation(); result.isSuccess()) {
    // ...
}

// 3. RAII ресурсы
if (std::unique_lock lock(mutex, std::try_to_lock); lock) {
    // ...
}
```
