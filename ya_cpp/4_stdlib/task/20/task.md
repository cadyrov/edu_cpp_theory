Представьте, что вас попросили ускорить работу программы-поисковика книг для центральной библиотеки города. Вы замерили скорость работы и обнаружили функцию, которая, с одной стороны, вызывается практически каждый раз при выполнении поиска книг по заданным параметрам, а с другой — работает заметно дольше остальных. 

Скопируйте код ниже к себе, разберитесь, что он делает, и примените функции из стандартной библиотеки алгоритмов C++, чтобы максимально ускорить программу.

```cpp
struct Book {
    std::string name;
    int idx = 0;
    bool operator<=>(const Book &rhd) { return idx <=> rhd.idx; }
}

void Process(std::vector<Book>& books) {
    if (books.empty())
        return;

    bool flag = false;
    for (auto [cur, next] = std::make_pair(books.begin(), std::next(books.begin())); next != books.end();
         ++cur, ++next) {
        if (*cur > *next) {
            flag = true;
            break;
        }
    }

    if (!flag) {
        int n = books.size();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (books[j] > books[j + 1]) {
                    std::swap(books[j], books[j + 1]);
                }
            }
        }

        auto medianVal = *std::next(books.begin(), books.size() / 2);
        for (auto it = books.begin(); it != books.end();) {
            if (*it < medianVal) {
                it = books.erase(it);
            } else {
                ++it;
            }
        }
    } else {

        auto medianVal = *std::next(books.begin(), books.size() / 2);
        for (auto it = books.begin(); it != books.end();) {
            if (*it < medianVal) {
                it = books.erase(it);
            } else {
                ++it;
            }
        }
    }
} 
```

- Подумайте, что даёт сравнение cur != books.end().
- Определите, какие элементы удаляются из массива.
- Вспомните, какой метод можно использовать, чтобы элементы в левой части вектора были меньше элементов в правой части вектора.
- Вспомните, как правильно удалить диапазон элементов из вектора.

## Задание 2

Вспомните метод RepositionExpandedPanels из старой версии браузера Chrome, которую мы рассматривали в этом уроке. Давайте проведём рефакторинг этой функции с помощью изученных алгоритмов.
Скопируйте код ниже к себе и выполните задания:
Разберитесь, что делает приведённый фрагмент кода.
Оптимизируйте код, применив одну из изученных функций библиотеки алгоритмов C++ и концепцию no raw for loops.

Важно: большинство стандартных функций из алгоритмической библиотеки принимают несколько итераторов и работают до тех пор, пока один из итераторов меньше другого. Обязательно учтите это при применении алгоритма, чтобы в вашем коде не было избыточных проверок.
```cpp
void PanelBar::RepositionExpandedPanels(Panel *fixed_panel, int fixed_index) {

    // Находим панель, находящуюся правее зафиксированной панели
    const int center_x = fixed_panel->cur_panel_center();
    auto panel_it = std::find_if(expanded_panels_.begin(), expanded_panels_.end(),
                                 [center_x](const auto &p) { return center_x < p->cur_panel_center(); });

    //
    // Если панель найдена - перегруппируем все панели
    //
    // До:    [           fixed_index,     new_panel_index         ]
    // После: [           new_panel_index, fixed_index             ]
    //
    if (panel_it != expanded_panels_.end()) {
        int new_panel_index = std::distance(expanded_panels_.begin(), panel_it);
        ref_ptr<Panel> ref = expanded_panels_[fixed_index];

        expanded_panels_.erase(expanded_panels_.begin() + fixed_index);
        expanded_panels_.insert(expanded_panels_.begin() + new_panel_index, ref);
    }
} 
```

- Обратите внимание, что panel_it сравнивается с концом диапазона.
- Подумайте, как располагаются элементы на позициях fixed_index, fixed_index + 1 и где они могут находиться относительно panel_it и expanded_panels_.end().