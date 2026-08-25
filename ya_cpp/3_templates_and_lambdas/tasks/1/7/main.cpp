template <typename T>
T clamp_value(T value, T low, T high) {
    if (value < low) return low;
    
    if (value > high) return high;
    
    return value;
}