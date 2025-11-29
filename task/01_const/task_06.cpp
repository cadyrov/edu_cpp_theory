#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>

// Task 6: Const-correctness возвращаемых значений и защита внутренних данных
//
// Реализуй класс ConfigManager, который возвращает ссылки на внутренние данные.
// Пойми, когда возвращать const vs non-const ссылки, и когда const возвращаемые
// значения полезны vs избыточны.
//
// Требования:
// 1. getValue() должен возвращать const ссылку (защищает внутренние данные)
// 2. getMutableValue() должен возвращать non-const ссылку (позволяет модификацию)
// 3. getValueCopy() должен возвращать по значению (const избыточен, но безвреден)
// 4. Пойми разницу между возвратом const ссылки и const значения

class ConfigManager {
    std::unordered_map<std::string, std::string> config_;

public:
    void setValue(const std::string& key, const std::string& value) {
        config_[key] = value;
    }
    
    // TODO: Implement getValue() returning const reference
    // Should protect internal data from modification
    const std::string& getValue(const std::string& key) const {
        // TODO: implement (may need to handle missing key)
        static const std::string empty;
        return empty;
    }
    
    // TODO: Implement getMutableValue() returning non-const reference
    // Should allow modification of internal data
    std::string& getMutableValue(const std::string& key) {
        // TODO: implement
        static std::string dummy;
        return dummy;
    }
    
    // TODO: Implement getValueCopy() returning by value
    // Const qualifier is redundant here (value is copied anyway)
    // but it's harmless and shows intent
    std::string getValueCopy(const std::string& key) const {
        // TODO: implement
        return "";
    }
    
    // TODO: Think about: should this return const std::string or std::string?
    // Answer: std::string (const is redundant for return by value)
};

void testConfigManager() {
    ConfigManager config;
    const ConfigManager& const_config = config;
    
    config.setValue("key1", "value1");
    
    // These should compile:
    const std::string& val1 = const_config.getValue("key1");  // Const reference
    std::string& val2 = config.getMutableValue("key1");       // Non-const reference
    std::string val3 = const_config.getValueCopy("key1");     // By value
    
    val2 = "modified";  // OK: modifying through non-const reference
    
    // These should NOT compile:
    // const_config.getValue("key1") = "modified";             // Error: cannot modify const reference
    // std::string& ref = const_config.getValue("key1");       // Error: cannot bind const to non-const
    // const_config.getMutableValue("key1");                   // Error: cannot call non-const method on const object
}

int main() {
    testConfigManager();
    return 0;
}

