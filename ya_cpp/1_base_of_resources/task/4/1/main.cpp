/*
1. **`Widget`: без копирования и перемещения.** Реализуйте хранение заголовка и истории его
изменений, методы `set_title`, `title() const` и `print() const`. Спрячьте данные и работу с
историей в `Widget::Impl`, которым единолично владеет `std::unique_ptr`. В `.h` оставьте публичный
интерфейс и предварительное объявление `Impl`; конструктор и деструктор определите в `.cpp` после
полного определения `Impl`. Явно запретите копирование и перемещение. В `main.cpp` создайте
несколько независимых объектов и измените их состояние. Объясните, какие заголовки нужны интерфейсу,
а какие удалось скрыть.
*/

#include "widget.h"

#include <iostream>

int main() {
    Widget f{};
    Widget s{};

    f.SetTitle("f first");
    f.SetTitle("f second");
    f.SetTitle("f third");

    s.SetTitle("s first");
    s.SetTitle("s second");
    s.SetTitle("s third");

    f.Print();
    s.Print();

    return 0;
}