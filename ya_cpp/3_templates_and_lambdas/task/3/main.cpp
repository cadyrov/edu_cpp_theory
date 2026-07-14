#include <memory>

template <typename T>
T error_value;

// Here is your code 
template <>
int error_value<int> = -1;

template <typename T>
T* error_value<T*> = nullptr;

template <typename T>
T* error_value<std::unique_ptr<T>> = nullptr;

template <typename T>
T* error_value<std::shared_ptr<T>> = nullptr;