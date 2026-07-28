//9. Напишите обертку над функцией, которая возвращает результат через `decltype(auto)`.
#include <cassert>

int val = 10;
int& foo() {
    return val;
}

decltype(auto) wrapper(){
    return foo();
}

int main() {
    decltype(auto) n = wrapper();
    
    return 0;
}
