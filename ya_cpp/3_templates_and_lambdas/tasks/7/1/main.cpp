//Напишите функцию `pass`, принимающую `T&&`.
#include <cassert>
#include <cmath>

template <typename T>
void pass(T&&) {

}

int main() {
    pass(4);

    return 0;
}