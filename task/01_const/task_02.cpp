#include <string>
#include <map>
#include <mutex>
#include <memory>
#include <iostream>

// Task 2: Потокобезопасный const-correct кэш с ленивой инициализацией
//
// Реализуй ThreadSafeCache, который обеспечивает const-correct доступ к кэшированным
// данным при сохранении потокобезопасности. Кэш должен использовать mutable для
// примитивов синхронизации и состояния кэша, но сохранять фактические данные логически константными.
//
// Требования:
// 1. Метод get() должен быть const и потокобезопасным
// 2. Используй mutable для mutex и состояния кэша (hits/misses)
// 3. Фактические кэшированные данные НЕ должны быть mutable
// 4. Метод put() НЕ должен быть const
// 5. Отслеживание статистики должно работать в const контексте

class ThreadSafeCache {
    // TODO: Design member variables:
    // - Cache storage (non-mutable)
    // - Mutex for synchronization (mutable)
    // - Statistics counters (mutable)
    
    std::map<std::string, std::string> cache_;
    mutable std::mutex mutex_;
    mutable size_t hits_ = 0;
    mutable size_t misses_ = 0;

public:
    // TODO: Implement const get() method
    // Should be thread-safe, update statistics, return const reference
    const std::string& get(const std::string& key) const {
        // TODO: implement thread-safe lookup with statistics
        static const std::string empty;
        return empty;
    }
    
    // TODO: Implement non-const put() method
    // Should be thread-safe, update cache
    void put(const std::string& key, const std::string& value) {
        // TODO: implement thread-safe insertion
    }
    
    // TODO: Implement const getStats() method
    // Should return statistics without modifying cache
    struct Stats {
        size_t hits;
        size_t misses;
    };
    
    Stats getStats() const {
        // TODO: implement
        return {0, 0};
    }
    
    // TODO: Implement const clear() method - wait, should this be const?
    // Think about logical constness: does clearing cache change observable state?
    // Answer: NO, clear() should NOT be const because it modifies cache contents
};

void testThreadSafeCache() {
    ThreadSafeCache cache;
    const ThreadSafeCache& const_cache = cache;
    
    cache.put("key1", "value1");
    cache.put("key2", "value2");
    
    // These should compile:
    const std::string& val1 = const_cache.get("key1");  // Const access
    auto stats = const_cache.getStats();                // Const access to stats
    
    // These should NOT compile:
    // const_cache.put("key3", "value3");                // Error: cannot modify through const
    // const_cache.get("key1") = "modified";              // Error: cannot modify const reference
}

int main() {
    testThreadSafeCache();
    return 0;
}

