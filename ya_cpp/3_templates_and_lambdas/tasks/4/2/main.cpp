#include <iostream>

template <typename T>
struct TypeName {
    static constexpr const char* value = "unknown";
};

template <>
struct TypeName<int> {
    static constexpr const char* value = "int";
};

    
int main() {
    static_assert(TypeName<char>::value == std::string_view("unknown"));
    static_assert(TypeName<int>::value == std::string_view("int"));

    return 0;
}