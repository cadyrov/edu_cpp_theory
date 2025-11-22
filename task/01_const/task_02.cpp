#include <string>
#include <vector>
#include <iostream>
#include <map>

// Task 2: Константность в методах класса
// 
// Реализуйте класс CacheManager, который:
// 1. Хранит пары ключ-значение
// 2. Ведёт статистику обращений к каждому ключу
// 3. Позволяет получать данные и статистику не изменяя их
// 4. Имеет методы для модификации данных
//
// Примените константность правильно, чтобы:
// - Защитить данные от случайной модификации
// - Разрешить модификацию только через специальные методы
// - Обеспечить максимальную производительность

class CacheManager {
    std::map<std::string, std::string> data_;
    mutable std::map<std::string, size_t> access_count_;
    static const std::string def_result;
public:
    // TODO: Реализуйте методы:
    
    // 1. Метод для получения значения по ключу
    // - Должен увеличивать счётчик обращений
    // - Не должен позволять модифицировать полученное значение
    const std::string& getValue(const std::string& key) const {
        // TODO: реализуйте
        return def_result;
    } 

    // 2. Метод для получения количества обращений к ключу
    // - Не должен позволять модифицировать счётчик
    // - Не должен учитываться как обращение к значению
    size_t getAccessCount(const std::string& key) const {
        // TODO: реализуйте
        return 0;
    }

    // 3. Метод для установки значения
    // - Должен позволять изменять данные
    // - Должен сбрасывать счётчик обращений
    void setValue(const std::string& key, const std::string& value){
        // TODO: реализуйте
    }

    // 4. Метод для проверки наличия ключа
    // - Не должен учитываться как обращение
    // - Не должен менять состояние объекта
    bool hasKey(const std::string& key) const {
        // TODO: реализуйте
        return false;
    }
};

const std::string CacheManager::def_result = "";

// Код для проверки решения
void testCacheManager() {
    CacheManager cache;
    
    // Базовые операции
    cache.setValue("key1", "value1");
    cache.setValue("key2", "value2");
    
    // Проверка const-correctness
    const CacheManager& const_cache = cache;
    
    std::cout << "key1 exists: " << const_cache.hasKey("key1") << "\n";
    std::cout << "key1 value: " << const_cache.getValue("key1") << "\n";
    std::cout << "key1 access count: " << const_cache.getAccessCount("key1") << "\n";
    
    // Эти строки НЕ должны компилироваться:
    // const_cache.setValue("key1", "new_value");        // Ошибка: нельзя модифицировать через const объект
    // const_cache.getValue("key1").clear();             // Ошибка: нельзя модифицировать полученное значение
    // const_cache.getAccessCount("key1")++;             // Ошибка: нельзя модифицировать счётчик
}

int main() {
    testCacheManager();
    return 0;
}
