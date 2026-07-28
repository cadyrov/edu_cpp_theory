//8. Напишите функцию, где decltype(auto) сохраняет ссылочный результат.

int main() {
    int a = 5;
    int& b = a;

    decltype(auto) x = b;


    return 0;
}
