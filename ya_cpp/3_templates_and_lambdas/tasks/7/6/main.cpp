//6. Напишите функцию, где `auto` теряет ссылку.

int main() {
    int a = 5;
    int& b = a;

    auto x = b;


    return 0;
}
