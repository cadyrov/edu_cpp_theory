template <typename T>
 T max_value(T a, T b) {
    if (a > b) {
        return a;
    }

    return b;
 }

 int main() {
    max_value(1, 1.0);


    return 0;
 }