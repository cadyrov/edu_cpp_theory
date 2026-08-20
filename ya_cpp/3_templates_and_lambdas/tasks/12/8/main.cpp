// Покажите, что при захвате по значению оригинальная переменная не меняется.

#include <algorithm>
#include <cassert>
#include <iostream>

int main() {
    int limit = 100;
    auto fn = [limit]() mutable { ++limit; };

    fn();
    fn();
    fn();
    fn();
    fn();

    assert(limit == 100);

    return 0;
}