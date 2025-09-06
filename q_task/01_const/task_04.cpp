#include <string>
#include <vector>
#include <memory>

// Task 5: Логическая константность
// 
// Реализуйте класс LazyString, который:
// 1. Хранит строку в разных представлениях (normal и uppercase)
// 2. Ленивое преобразование в uppercase при первом запросе
// 3. Кеширование результата для последующих запросов
// 4. Поддержка константной корректности

class LazyString {
    std::string original_;
    mutable std::string uppercase_cache_;
    mutable bool cache_valid_ = false;

public:
    // TODO: Реализуйте:
    // 1. Конструктор из string
    // 2. Метод получения оригинальной строки (не константный)
    // 3. Метод получения UPPERCASE версии (константный)
    // 4. Метод изменения строки (сбрасывает кеш)
    // 5. Метод size() (константный)
};

// Код для проверки
void testLazyString() {
    LazyString str("Hello, World!");
    
    // Проверка базовой функциональности
    std::cout << "Original: " << str.get() << "\n";
    std::cout << "Upper: " << str.getUpperCase() << "\n";
    
    // Проверка константности
    const LazyString const_str("Test String");
    std::cout << "Const Upper: " << const_str.getUpperCase() << "\n";
    
    // Проверка изменения и сброса кеша
    str.set("New String");
    std::cout << "New Upper: " << str.getUpperCase() << "\n";
    
    // Эти строки НЕ должны компилироваться:
    // const_str.set("test");          // Нельзя модифицировать const объект
    // const_str.get() = "test";       // Нельзя модифицировать через результат
    // str.getUpperCase() = "TEST";    // Нельзя модифицировать результат uppercase
}

