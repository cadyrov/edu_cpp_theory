/*
2. **`Widget`: только перемещение.**
В отдельном каталоге заново реализуйте весь класс из задачи 1,
разрешив move constructor и move assignment с `noexcept`. Определите их в `.cpp`. Задайте контракт
пустого объекта после перемещения: `empty()` возвращает `true`, чтение возвращает пустой заголовок,
печать сообщает о пустом состоянии, а `set_title` создаёт новую реализацию. Продемонстрируйте
перемещение при создании и присваивании уже непустому объекту, повторное использование источника и
хранение объектов в `std::vector`. Объясните, почему объявленный деструктор требует явно заняться
move-операциями.
*/

#include "widget.h"

#include <iostream>
#include <utility>
#include <vector>

int main() {
    Widget x{};
    x.SetTitle("f first");
    x.SetTitle("f second");
    x.SetTitle("f third");

    Widget f(std::move(x));
    Widget s{};

    s.SetTitle("s first");
    s.SetTitle("s second");
    s.SetTitle("s third");

    f.Print();
    s.Print();

    f = std::move(s);

    f.Print();
    s.Print();

    s.SetTitle("sx first");
    s.SetTitle("sx second");

    f.Print();
    s.Print();

    std::vector<Widget> wgs;
    wgs.push_back(std::move(f));
    wgs.push_back(std::move(s));

    for (const auto& widget : wgs) {
        widget.Print();
    }

    return 0;
}