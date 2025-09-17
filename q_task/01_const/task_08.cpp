#include <map>
#include <string>
#include <mutex>

// Task 8: Логическая vs битовая константность
// 
// Реализуйте класс DataCache, который:
// 1. Предоставляет потокобезопасный доступ к данным
// 2. Использует ленивую инициализацию
// 3. Правильно применяет mutable
// 4. Различает логическую и битовую константность


struct CacheStats {
    size_t hits;
    size_t misses;
    std::string last_access;

    void Clear() {
        hits = 0;
        misses = 0;
        last_access = "";
    }
};

class DataCache {
    // Кэшируемые данные
    mutable std::map<std::string, std::string> cache_;
    mutable std::mutex m;
    mutable CacheStats stat;
    // TODO: Добавьте необходимые поля для:
    // 1. Защиты многопоточного доступа
    // 2. Подсчета кэш-хитов/промахов
    // 3. Отслеживания последнего обращения
    
public:
    // TODO: Реализуйте:
    
    // 1. Метод получения данных из кэша
    // - Должен работать с константными объектами
    // - Должен быть потокобезопасным
    // - Должен поддерживать статистику
    const std::string getData(const std::string& key) const {
        std::lock_guard<std::mutex> lock(m);

        auto it = cache_.find(key);
        
        if (it == cache_.end()) {
            stat.misses +=1;

            return "";
        } else {
            stat.hits +=1;
            stat.last_access = it->second;
            return it->second;
        }
    }
    
    // 2. Метод очистки кэша
    // - Не должен работать с константными объектами
    // - Должен быть потокобезопасным
    void clear(){
        std::lock_guard<std::mutex> lock(m);

        cache_.clear();

        stat.Clear();
    }
    
    // 3. Метод получения статистики
    // - Должен работать с константными объектами
    // - Не должен учитываться в статистике обращений
    CacheStats getStats() const {
        return stat;
    }
    
    // 4. Метод добавления данных в кэш
    // - Не должен работать с константными объектами
    // - Должен быть потокобезопасным
    void putData(const std::string& key, const std::string& value) {
        std::lock_guard<std::mutex> lock(m);

        cache_[key] = value;
    }
};

// Код для проверки
void testLogicalConstness() {
    DataCache cache;
    const DataCache& const_cache = cache;
    
    // Эти строки должны компилироваться:
    cache.putData("key1", "value1");        // Модификация через неконстантный объект
    auto value = const_cache.getData("key1"); // Получение через константный объект (возможна модификация кэша)
    auto stats = const_cache.getStats();      // Получение статистики через константный объект
    cache.clear();                           // Очистка через неконстантный объект
    
    // Эти строки НЕ должны компилироваться:
    // const_cache.putData("key2", "value2"); // Нельзя модифицировать через константный объект
    // const_cache.clear();                    // Нельзя очищать через константный объект
    // cache.getStats().hits = 0;              // Нельзя модифицировать статистику напрямую
}
