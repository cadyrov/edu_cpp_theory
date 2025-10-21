#include <iostream>
#include <cassert>
#include <type_traits>
#include <utility>
#include <vector>

// Task 10: Продвинутый шаблон с SFINAE и семантикой перемещения
//
// Реализуйте шаблонный класс SmartStore, который:
// - Правильно обрабатывает L-value и R-value в store()
// - Использует SFINAE для выбора оптимального хранения
// - Перемещает данные когда это безопасно
// - Копирует когда нужно сохранить исходный объект

template<typename T>
class SmartStore {
    std::vector<T> data_;
public:
    // TODO: Реализуйте store(const T&) для копирования L-value
    
    // TODO: Реализуйте store(T&&) для перемещения R-value
    
    // TODO: Реализуйте get() для доступа к хранилищу
    
    // TODO: SFINAE специализация для std::is_move_constructible
};

// TODO: Специализация для move-only типов
template<typename T>
class SmartStore<T> {
    // Специально для move-only типов
};

void testSmartStore() {
    SmartStore<int> store_int;
    
    // TODO: store_int.store(42);
    // TODO: assert(store_int.get() == 42);
    
    SmartStore<std::string> store_string;
    
    std::string s = "hello";
    // TODO: store_string.store(s);  // копирование L-value
    // TODO: store_string.store("world");  // перемещение R-value
    
    std::cout << "SmartStore tests passed!\n";
}

int main() {
    testSmartStore();
    return 0;
}
