#include <cmath>
template <typename T1, typename T2>
bool is_equal(const T1& a, const T2& b) {
    return a == b;
}

template <typename T1, typename T2>
bool is_equal(T1* a, T2* b) {
    return *a == *b;    
}

bool is_equal(double a, double b, double epsilon) { return std::abs(a - b) < epsilon; }

bool is_equal(double a, double b) {
    return std::abs(a - b) < 1e-7;
}

bool is_equal(float a, double b) {
    return std::abs(static_cast<double>(a) - b) < 1e-5;
}

bool is_equal(double a, float b) {
    return std::abs(a - static_cast<double>(b)) < 1e-5;
}
bool is_equal(float a, float b) {
    return std::abs(static_cast<double>(a) - static_cast<double>(b)) < 1e-5;
}