#include <string>
#include <map>
#include <mutex>
#include <iostream>

// Task 10: Сложный сценарий const-correctness - объединение всех концепций
//
// Реализуй класс Database, который объединяет все концепции const-correctness:
// - Const и non-const operator[]
// - Const и non-const итераторы
// - Mutable для кэширования и статистики
// - Потокобезопасность с mutable mutex
// - Const-correct перегрузка методов
// - Правильная const-correctness возвращаемых значений
//
// Это комплексная задача, проверяющая понимание всех нюансов const.

class Database {
    // Core data - NOT mutable
    std::map<std::string, std::string> records_;
    
    // Implementation details - mutable (don't affect logical constness)
    mutable std::map<std::string, std::string> query_cache_;
    mutable std::mutex mutex_;
    mutable size_t query_count_ = 0;
    mutable size_t cache_hits_ = 0;

public:
    using iterator = std::map<std::string, std::string>::iterator;
    using const_iterator = std::map<std::string, std::string>::const_iterator;
    
    // TODO: Implement non-const operator[]
    // Should allow modification, create entry if doesn't exist
    std::string& operator[](const std::string& key) {
        // TODO: implement
        static std::string dummy;
        return dummy;
    }
    
    // TODO: Implement const operator[]
    // Should NOT create entry if doesn't exist, return const reference
    // Should use cache for read operations
    const std::string& operator[](const std::string& key) const {
        // TODO: implement with caching logic
        static const std::string empty;
        return empty;
    }
    
    // TODO: Implement const find() method
    // Should use cache, update statistics
    const_iterator find(const std::string& key) const {
        // TODO: implement with caching
        return records_.end();
    }
    
    // TODO: Implement non-const find() method
    iterator find(const std::string& key) {
        // TODO: implement (no caching needed for non-const)
        return records_.end();
    }
    
    // TODO: Implement const begin() and end()
    const_iterator begin() const {
        // TODO: implement
        return records_.begin();
    }
    
    const_iterator end() const {
        // TODO: implement
        return records_.end();
    }
    
    // TODO: Implement non-const begin() and end()
    iterator begin() {
        // TODO: implement
        return records_.begin();
    }
    
    iterator end() {
        // TODO: implement
        return records_.end();
    }
    
    // TODO: Implement const size() method
    size_t size() const {
        // TODO: implement
        return 0;
    }
    
    // TODO: Implement const getStats() method
    struct Stats {
        size_t query_count;
        size_t cache_hits;
        size_t record_count;
    };
    
    Stats getStats() const {
        // TODO: implement
        return {0, 0, 0};
    }
    
    // TODO: Implement non-const clearCache() method
    // Why non-const? Because it changes observable behavior (cache affects performance)
    void clearCache() {
        // TODO: implement
    }
    
    // TODO: Implement non-const insert() method
    void insert(const std::string& key, const std::string& value) {
        // TODO: implement
    }
};

void testDatabase() {
    Database db;
    const Database& const_db = db;
    
    db.insert("key1", "value1");
    db.insert("key2", "value2");
    
    // These should compile:
    db["key3"] = "value3";                    // Non-const operator[]
    const std::string& val1 = const_db["key1"]; // Const operator[] with caching
    const std::string& val2 = const_db["key1"]; // Should use cache
    
    auto it1 = db.find("key1");              // Non-const find
    auto it2 = const_db.find("key1");        // Const find with caching
    
    for (const auto& pair : const_db) {      // Const iteration
        std::cout << pair.first << ": " << pair.second << "\n";
    }
    
    for (auto& pair : db) {                  // Non-const iteration
        pair.second += "_modified";
    }
    
    auto stats = const_db.getStats();        // Get statistics
    db.clearCache();                         // Clear cache
    
    // These should NOT compile:
    // const_db["key4"] = "value4";          // Error: cannot modify through const operator[]
    // const_db.insert("key5", "value5");    // Error: cannot call non-const method
    // const_db.clearCache();                // Error: cannot clear cache through const object
    // const_db.find("key1")->second = "x";  // Error: cannot modify through const iterator
}

int main() {
    testDatabase();
    return 0;
}

