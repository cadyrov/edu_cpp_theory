template <typename T>
bool is_equal(const T& a, const T& b) {
    return a == b;
}

template <typename T>
bool is_equal(const T* a, const T* b) {
    if (a == nullptr || b == nullptr) {
        return a == b;
    }

    return *a == *b;
}