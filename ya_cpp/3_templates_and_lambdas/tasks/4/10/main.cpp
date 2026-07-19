// Перепишите простую специализацию функции через перегрузку и сравните читаемость.

template<typename T>
void foo(T) {

}

void foo(double) {

}

int main() {
    foo(1);
    foo(1.0);
    return 0;
}
