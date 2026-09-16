/*
3. **`Widget`: независимое копирование.** Ещё раз реализуйте класс полностью, теперь с глубоким
копированием `Impl` и перемещением. Копия должна получать собственные заголовок и историю; изменение
копии не меняет оригинал. При ошибке выделения памяти copy assignment должен оставлять получателя
неизменным. Сохраните контракт пустого состояния из задачи 2. В `main.cpp` покажите копирование при
создании и присваивании, самоприсваивание, копирование пустого объекта и перемещение. Объясните,
почему замена `unique_ptr` на `shared_ptr` сама по себе не обеспечивает требуемую семантику копии.
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

    Widget xx(wgs[0]);

    Widget xy{};
    xy = wgs[1];

    xx.SetTitle("xx 2222");
    xy.SetTitle("xy 2222");

    xy.Print();
    xx.Print();

    for (const auto& widget : wgs) {
        widget.Print();
    }

    return 0;
}