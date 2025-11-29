#include <string>
#include <map>
#include <mutex>
#include <memory>
#include <iostream>

// Task 7: Логическая константность со сложным использованием mutable
//
// Реализуй LazyInitializedCache, который использует mutable для ленивой инициализации
// и кэширования, сохраняя логическую константность. Кэш должен отслеживать паттерны
// доступа и выполнять дорогую инициализацию только когда необходимо.
//
// Требования:
// 1. get() должен быть const и выполнять ленивую инициализацию
// 2. Используй mutable для состояния кэша и флагов инициализации
// 3. Фактические кэшированные значения должны быть mutable (это кэш, не основные данные)
// 4. clearCache() НЕ должен быть const (меняет наблюдаемое состояние)
// 5. getStats() должен быть const (не меняет наблюдаемое состояние)

class LazyInitializedCache {
    // Core data - NOT mutable (this is the actual data we're caching)
    std::map<std::string, std::string> source_data_;
    
    // Cache and state - mutable (implementation detail, doesn't affect logical constness)
    mutable std::map<std::string, std::string> cache_;
    mutable std::map<std::string, bool> initialized_;
    mutable std::mutex mutex_;
    mutable size_t cache_hits_ = 0;
    mutable size_t cache_misses_ = 0;

public:
    LazyInitializedCache() {
        // Simulate expensive source data
        source_data_["key1"] = "expensive_value_1";
        source_data_["key2"] = "expensive_value_2";
        source_data_["key3"] = "expensive_value_3";
    }
    
    // TODO: Implement const get() method with lazy initialization
    // Should initialize cache entry on first access, then use cache
    const std::string& get(const std::string& key) const {
        // TODO: implement thread-safe lazy initialization
        // 1. Check if already initialized (use cache)
        // 2. If not, perform expensive initialization from source_data_
        // 3. Store in cache and mark as initialized
        // 4. Update statistics
        static const std::string empty;
        return empty;
    }
    
    // TODO: Implement non-const clearCache() method
    // Should clear cache but NOT source data
    // Why is this non-const? Because clearing cache changes observable behavior
    void clearCache() {
        // TODO: implement
    }
    
    // TODO: Implement const getStats() method
    struct Stats {
        size_t hits;
        size_t misses;
        size_t cached_items;
    };
    
    Stats getStats() const {
        // TODO: implement
        return {0, 0, 0};
    }
    
    // TODO: Implement non-const updateSource() method
    // Should update source data and invalidate cache
    void updateSource(const std::string& key, const std::string& value) {
        // TODO: implement
    }
};

void testLazyInitializedCache() {
    LazyInitializedCache cache;
    const LazyInitializedCache& const_cache = cache;
    
    // These should compile:
    const std::string& val1 = const_cache.get("key1");  // Lazy init + cache
    const std::string& val2 = const_cache.get("key1");  // Cache hit
    auto stats = const_cache.getStats();                // Get stats
    cache.clearCache();                                 // Clear cache
    cache.updateSource("key1", "new_value");           // Update source
    
    // These should NOT compile:
    // const_cache.clearCache();                         // Error: changes observable state
    // const_cache.updateSource("key1", "new");         // Error: modifies source data
    // const_cache.get("key1") = "modified";            // Error: cannot modify const reference
}

int main() {
    testLazyInitializedCache();
    return 0;
}

