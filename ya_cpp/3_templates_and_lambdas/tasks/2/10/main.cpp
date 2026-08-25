template<typename T>
void foo(T) {

}

void foo(double) {

}

int main() {
    foo(1);    // шаблон: foo<int>(T)
    foo(1.0);  // обычная перегрузка foo(double)
}