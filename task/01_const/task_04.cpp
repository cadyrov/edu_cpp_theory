#include <string>
#include <iostream>
#include <cstring>

// Task 4: Безопасное использование const_cast с legacy C API
//
// Реализуй обёртку вокруг legacy C API, которое требует non-const указатели,
// но обеспечивает const-correctness в C++ коде. Ты должен использовать const_cast
// правильно и понимать, когда это безопасно, а когда нет.
//
// Критично: const_cast безопасен ТОЛЬКО когда исходный объект НЕ был const.
// Снятие const с изначально const объекта - это undefined behavior.
//
// Требования:
// 1. print() должен работать с const объектами (API не модифицирует)
// 2. modify() НЕ должен работать с const объектами (API модифицирует)
// 3. Используй const_cast только когда безопасно (объект был изначально non-const)
// 4. Пойми разницу между const указателем и изначально const объектом

extern "C" {
    struct LegacyData {
        char buffer[256];
        int length;
    };
    
    // Legacy function that doesn't modify data but takes non-const pointer
    void legacy_print(LegacyData* data) {
        std::cout << "Buffer: " << data->buffer << ", Length: " << data->length << "\n";
    }
    
    // Legacy function that modifies data
    void legacy_modify(LegacyData* data, const char* text) {
        strncpy(data->buffer, text, sizeof(data->buffer) - 1);
        data->buffer[sizeof(data->buffer) - 1] = '\0';
        data->length = strlen(data->buffer);
    }
}

class SafeLegacyWrapper {
    LegacyData data_;

public:
    SafeLegacyWrapper(const char* text) {
        strncpy(data_.buffer, text, sizeof(data_.buffer) - 1);
        data_.buffer[sizeof(data_.buffer) - 1] = '\0';
        data_.length = strlen(data_.buffer);
    }
    
    // TODO: Implement const print() method
    // Should work with const objects because legacy_print doesn't modify
    // Use const_cast safely (data_ was originally non-const)
    void print() const {
        // TODO: implement using const_cast
    }
    
    // TODO: Implement non-const modify() method
    // Should NOT work with const objects
    void modify(const char* text) {
        // TODO: implement without const_cast (not needed here)
    }
    
    // TODO: Implement const getLength() method
    int getLength() const {
        // TODO: implement
        return 0;
    }
};

void testSafeLegacyWrapper() {
    SafeLegacyWrapper wrapper("test");
    const SafeLegacyWrapper& const_wrapper = wrapper;
    
    // These should compile:
    wrapper.print();                    // Non-const object
    const_wrapper.print();              // Const object (safe const_cast)
    wrapper.modify("new text");         // Non-const object
    int len = const_wrapper.getLength(); // Const object
    
    // This should NOT compile:
    // const_wrapper.modify("new");     // Error: cannot modify const object
    
    // Critical test: what happens with originally const object?
    const SafeLegacyWrapper originally_const("const");
    // originally_const.print();        // This should work (const_cast is safe here)
    // But if we had: const LegacyData orig_const; and tried to const_cast it - UB!
}

int main() {
    testSafeLegacyWrapper();
    return 0;
}

